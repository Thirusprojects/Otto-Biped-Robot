# Otto Biped Robot

A small two-legged robot built with an **Arduino Nano and four servo motors**. The physical robot successfully moved **forward and backward**, demonstrating basic biped locomotion through coordinated leg and foot motion.

![Otto biped robot](media/images/img-0624.jpg)

## My contribution — Semester 5

I worked on coding and connecting the four servo motors. The physical robot demonstrated forward and backward movement.

## Hardware and operation

Two servo-driven legs and two servo-driven feet form the walking mechanism. The Arduino Nano controls the four servos to create the movement sequence.

| Item | Details |
| --- | --- |
| Controller | Arduino Nano |
| Actuation | Four servo motors |
| Demonstrated movements | Forward and backward |
| Original obstacle response | Not implemented |

## New obstacle-response firmware

An Otto all-moves example has now been supplied as a project reference; see [the source-code notes](firmware/reference/README.md). It includes an obstacle-check routine, but obstacle response on the physical robot remains unverified. A **new reference implementation** has been added in [firmware/OttoObstacleAvoidance](firmware/OttoObstacleAvoidance). It uses the official OttoDIY library and uses an HC-SR04 ultrasonic sensor for obstacle response, as shown in the supplied circuit reference.

The new code provides one-step forward/backward commands and an automatic mode that checks distance between gait cycles, turns when blocked, and stops on invalid readings. This is newly written code; obstacle avoidance and turning have **not been validated on this robot**.

Read the [wiring, calibration and upload guide](firmware/README.md) before using it. The pin assignments are proposed, and the configuration starts locked until the wiring is checked.

## Robot gallery

![Project view 1](media/images/img-0624.jpg)

![Project view 2](media/images/img-0625.jpg)

![Project view 3](media/images/img-5570.jpg)

![Project view 4](media/images/img-5576.jpg)

![Project view 5](media/images/img-5577.jpg)

![Project view 6](media/images/img-5578.jpg)

## Circuit reference

![Supplied Otto circuit reference](media/images/otto-circuit-reference.jpg)

This reference drawing shows an Uno with servo signals on D8–D11 and ultrasonic connections on D2/D3. The reported project used a Nano, and the supplied code assigns servos to D2–D5. These are different wiring arrangements; the firmware guide keeps them separate.
