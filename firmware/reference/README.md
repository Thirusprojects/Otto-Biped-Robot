# Supplied Otto example

[OttoAllMoves.ino.txt](OttoAllMoves.ino.txt) preserves the executable statements of the example supplied by the project contributor. Chat escaping and decorative comments were removed; the original OttoDIY / CC BY SA credit and date are retained. This is an attributed OttoDIY example, not a claim that its library routines were authored for this project. The supplied header does not specify a Creative Commons license version.

The example uses legacy `US.h`, a five-argument `Otto.init(...)` and `Otto.getDistance()`. The currently tested OttoDIYLib 13.0.0 has a different interface, so this file is stored as a text reference and was **not compiled**. The separate `../OttoObstacleAvoidance` sketch uses the current library API and explicit ultrasonic reads.

The example calls `obstacleMode()` once per long all-moves sequence. The remaining gestures and movements execute regardless of new obstacles. It therefore does not continuously monitor clearance. Its presence does not establish that obstacle avoidance, gestures or turns worked on the historical robot: only forward and backward movement were confirmed. The unused `obstacleDetected` variable is retained from the supplied code.

The supplied code sets leg servos to D2/D3 and foot servos to D4/D5. The supplied circuit drawing instead shows an Uno with servo signals on D8–D11 and HC-SR04 trigger/echo on D2/D3. Neither drawing nor example alone establishes the actual Nano's sensor pins.
