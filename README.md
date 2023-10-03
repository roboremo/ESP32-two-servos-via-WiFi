# ESP32-two-servos-via-WiFi
Control 2 servomotors over WiFi TCP with ESP32-WROVER-B and RoboRemo Joystick

We used an ESP32-WROVER-B board, but other boards should work as well.<br/>
Make sure to configure the PWM output pins according to your circuit. <br/>
<code>const int servoPin[chCount] = {13, 12};</code><br/>

The ESP creates tis own WiFi Access Point named "mywifi" with password "qwerty123".<br/>
Then it starts TCP Server on IP 192.168.0.1 port 8080.<br/>

## Building the RoboRemo interface
menu -> edit UI<br/>
click on blank space -> add joystick, drag to move, resize<br/>
click on joystick, configure:<br/>
X axis ID <code>ch0</code>, output int, min. <code>1000</code>, max. <code>2000</code>, auto return to <code>mid</code>.<br/>
Y axis ID <code>ch1</code>, output int, min. <code>1000</code>, max. <code>2000</code>, auto return to <code>mid</code>.<br/>
send space after ID <code>checked</code>

## connecting
Android WiFi sttings -> connect to AP <code>mywifi</code><br/>
Open RoboRemo app -> menu -> connect -> Internet (TCP) -> <code>192.168.0.1:8080</code>

## operating
Move the joystick in RoboRemo -> see the servomotors move.

## power supply
Make sure you have a decent power supply. Weak power supply may result in ESP restarting.<br/>
For our tests we used our lab power supply set to 5V for the servomotors and USB cable for the ESP.
