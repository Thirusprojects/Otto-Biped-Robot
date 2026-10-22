# Otto obstacle-response firmware

This is newly written reference code, not the original project firmware. The original Nano/four-servo robot demonstrated forward and backward movement. Obstacle response and the turning gait below have not been tested on that robot.

## Selected reference configuration

Use a classic 5 V Arduino Nano (ATmega328P), four appropriately powered servos and a **front HC-SR04**, shown in the supplied circuit reference. Confirm the robot's geometry is compatible with OttoDIY's two-leg/two-foot arrangement.

| Connection | Reference Nano pin |
|---|---|
| Left leg servo signal | D2 |
| Right leg servo signal | D3 |
| Left foot servo signal | D4 |
| Right foot servo signal | D5 |
| HC-SR04 trigger / echo | D8 / D9 |
| Optional buzzer, reserved | D13 |

Power the servos from a regulated supply suitable for their voltage and combined stall current; share ground with the Nano and sensor. Do not power four servos from a Nano GPIO or assume USB can supply them. Check horn positions and mechanical travel before enabling outputs.

## Supplied code versus circuit drawing

The [supplied legacy example](reference/README.md) uses servo pins D2–D5, matching the selected servo map above. Its ultrasonic pins depend on an unspecified legacy library. The [supplied diagram](../media/images/otto-circuit-reference.jpg) instead shows an **Uno**, servo signals D8–D11, HC-SR04 trigger D2 and echo D3. The physical project was reported as **Nano-based**. The maintained sketch uses the Nano servo map and assigns trigger D8 / echo D9, avoiding the servo pins. This is a selected implementation configuration, not a recovered historical sensor connection. Follow the table above rather than mixing it with the Uno drawing. The drawing also connects servo power to the board's 5 V rail; use an appropriately rated servo supply for the actual build.

## Setup

1. Install **OttoDIYLib** and **Servo** using Arduino Library Manager. Open `OttoObstacleAvoidance/OttoObstacleAvoidance.ino` with its adjacent `Config.h`.
2. Select Arduino Nano / ATmega328P. Some older Nano boards require the old bootloader upload option.
3. Verify the proposed pins, servo order and neutral alignment. Adjust the four trim values in `Config.h`; the sketch intentionally does not load unknown EEPROM trims.
4. Set `WIRING_CONFIRMED = true` only after checking the hardware. The distributed default leaves servo outputs unattached.
5. Support the robot for the initial neutral-position test, then test individual steps on a clear, level surface. Confirm balance and turning before trying automatic mode.
6. Open Serial Monitor at **9600 baud**.

| Command | Behavior |
|---|---|
| `f` | One forward gait cycle if the front reading is at least 35 cm |
| `b` | One backward gait cycle; operator must check behind the robot |
| `a` | Start automatic forward/obstacle-response mode |
| `x` or `s` | Stop and return to the home pose after the current blocking operation |
| `d` | Print distance; -1 means no valid echo |

Automatic mode requires two clear readings before a forward step. At 30 cm or closer it starts left-turn cycles, continuing until clearance reaches 35 cm. After six unsuccessful turn cycles it stops. Invalid readings or objects closer than 8 cm cause a fault stop; inspect the robot before retrying with `a`. These distances, gait periods and limits are configurable.

**Timing limitation:** OttoDIY walk/turn calls block for approximately one configured 1,200 ms gait cycle. Commands and distance are checked between cycles; `x` is not an immediate emergency stop. Home positioning may add delay. There is no rear sensing or drop-off detection. Test away from edges and keep a physical power disconnect accessible.

## Verification and sources

Compiled for `arduino:avr:nano:cpu=atmega328` using Arduino AVR Boards 1.8.8, OttoDIYLib 13.0.0 and Servo 1.3.0. Both the distributed configuration and an enabled-output configuration were compiled. Compilation does not verify wiring, gait balance, servo direction or obstacle performance; physical testing remains outstanding.

- [Official OttoDIY library](https://github.com/OttoDIY/OttoDIYLib)
- [Official Arduino Servo library](https://github.com/arduino-libraries/Servo)
