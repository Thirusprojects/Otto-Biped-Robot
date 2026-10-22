/*
 * Newly written reference firmware, October 2026. Not the original project code.
 * Arduino Nano ATmega328P + 4 servos + proposed HC-SR04 obstacle sensor.
 * Requires official OttoDIYLib and Servo. See firmware/README.md before use.
 * The original robot demonstrated forward/backward movement; obstacle response
 * and turning in THIS firmware still require physical testing and calibration.
 */
#include <Arduino.h>
#include <Otto.h>
#include "Config.h"

Otto robot;
enum class Mode : uint8_t { STOPPED, AUTO, FAULT };
Mode mode = Mode::STOPPED;
bool ready = false;
uint8_t turnSteps = 0;
uint8_t clearSamples = 0;
bool avoiding = false;

// HC-SR04: -1 means invalid/no echo, never an unobstructed path.
int readDistanceCm() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  const unsigned long echo = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
  if (echo == 0) return -1;
  const int cm = static_cast<int>(echo / 58UL);
  return (cm >= 2 && cm <= 400) ? cm : -1;
}

void stopRobot(bool fault) {
  mode = fault ? Mode::FAULT : Mode::STOPPED;
  turnSteps = 0;
  clearSamples = 0;
  avoiding = false;
  if (ready) robot.home();
  Serial.println(fault ? F("FAULT: stopped. Check clearance/sensor; send a to retry.")
                       : F("Stopped."));
}

void handleCommand(char command) {
  if (command == '\n' || command == '\r' || command == ' ') return;
  if (!ready) {
    Serial.println(F("Verify Config.h and set WIRING_CONFIRMED=true first."));
    return;
  }
  switch (command) {
    case 'x': case 's': stopRobot(false); break;
    case 'a':
      mode = Mode::AUTO;
      turnSteps = 0;
      clearSamples = 0;
      avoiding = false;
      Serial.println(F("Auto obstacle response enabled."));
      break;
    case 'f': {
      stopRobot(false);
      const int cm = readDistanceCm();
      if (cm < CLEAR_CM) { stopRobot(true); break; }
      robot.walk(1, WALK_PERIOD_MS, FORWARD);
      robot.home();
      break;
    }
    case 'b':
      stopRobot(false);
      // Manual one-step test only: there is no rear-facing range sensor.
      robot.walk(1, WALK_PERIOD_MS, BACKWARD);
      robot.home();
      break;
    case 'd':
      Serial.print(F("Distance cm (-1 invalid): "));
      Serial.println(readDistanceCm());
      break;
    default: Serial.println(F("Commands: f one step forward, b back, a auto, x stop, d distance."));
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  if (!WIRING_CONFIRMED) {
    Serial.println(F("Configuration lock active: servo outputs remain unattached."));
    return;
  }
  robot.init(LEFT_LEG_PIN, RIGHT_LEG_PIN, LEFT_FOOT_PIN, RIGHT_FOOT_PIN,
             false, BUZZER_PIN); // Do not load unknown EEPROM calibration.
  robot.setTrims(LEFT_LEG_TRIM, RIGHT_LEG_TRIM, LEFT_FOOT_TRIM, RIGHT_FOOT_TRIM);
  ready = true;
  robot.home();
  Serial.println(F("Ready, stopped. Commands: f b a x d"));
}

void loop() {
  while (Serial.available()) handleCommand(static_cast<char>(Serial.read()));
  if (!ready || mode != Mode::AUTO) return;

  const int cm = readDistanceCm();
  if (cm < TOO_CLOSE_CM) { stopRobot(true); return; } // Includes -1 timeout.
  if (cm >= CLEAR_CM) {
    if (++clearSamples < 2) { delay(70); return; }
    clearSamples = 0;
    avoiding = false;
    turnSteps = 0;
    robot.walk(1, WALK_PERIOD_MS, FORWARD);
  } else if (avoiding || cm <= OBSTACLE_CM) {
    clearSamples = 0;
    avoiding = true;
    if (turnSteps >= MAX_TURN_STEPS) { stopRobot(true); return; }
    ++turnSteps;
    robot.turn(1, TURN_PERIOD_MS, LEFT);
  } else {
    clearSamples = 0;
    robot.home(); // Hysteresis band: wait for a clear path or a closer obstacle.
  }
  // Library gait calls block for one cycle. Recheck range and serial between
  // cycles; this is not continuous collision monitoring or an emergency stop.
  delay(70);
}
