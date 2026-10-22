#pragma once
#include <Arduino.h>

// Proposed wiring, NOT recovered from the original robot. Verify before enabling.
constexpr bool WIRING_CONFIRMED = false;
constexpr uint8_t LEFT_LEG_PIN = 2;
constexpr uint8_t RIGHT_LEG_PIN = 3;
constexpr uint8_t LEFT_FOOT_PIN = 4;
constexpr uint8_t RIGHT_FOOT_PIN = 5;
constexpr uint8_t TRIGGER_PIN = 8;
constexpr uint8_t ECHO_PIN = 9;
constexpr uint8_t BUZZER_PIN = 13; // Reserved; buzzer optional, no sounds used.
constexpr int LEFT_LEG_TRIM = 0;
constexpr int RIGHT_LEG_TRIM = 0;
constexpr int LEFT_FOOT_TRIM = 0;
constexpr int RIGHT_FOOT_TRIM = 0;
constexpr int WALK_PERIOD_MS = 1200;
constexpr int TURN_PERIOD_MS = 1200;
constexpr uint16_t OBSTACLE_CM = 30;
constexpr uint16_t CLEAR_CM = 35;
constexpr uint16_t TOO_CLOSE_CM = 8;
constexpr uint8_t MAX_TURN_STEPS = 6;
constexpr unsigned long ECHO_TIMEOUT_US = 25000UL;
