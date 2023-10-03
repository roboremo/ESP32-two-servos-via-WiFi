# ESP32-two-servos-via-WiFi
Control 2 servomotors over WiFi TCP with ESP32-WROVER-B and RoboRemo Joystick

We used an ESP32-WROVER-B board, but other boards should work as well.
Make sure to configure the PWM output pins according to your circuit.
<code>const int servoPin[chCount] = {13, 12};</code>
