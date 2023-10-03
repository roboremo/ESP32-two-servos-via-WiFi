// ESP32-WROVER-B Controlling 2 servomotors with Joystick in RoboRemo
// by RoboRemo
// https://roboremo.app
//
// The Software is provided to You "AS IS" and "AS AVAILABLE"
// and with all faults and defects without warranty of any kind. 
// Don't use RoboRemo for life support systems
// or any other situations where system failure may affect
// user or environmental safety.

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP32Servo.h>

// config: ////////////////////////////////////////////////////////////////////////

// ESP will create WiFi Access Point named "mywifi", you will connect your phone to it
const char *ssid = "mywifi";    
const char *pass = "qwerty123";

const IPAddress netmask(255, 255, 255, 0);
const IPAddress ip(192, 168, 0, 1); // In RoboRemo app -> menu -> connect
const int port = 8080;              //                    192.168.0.1:8080

const int chCount = 2;
const int usMin = 1000;
const int usMax = 2000;
const int servoPin[chCount] = {13, 12};

///////////////////////////////////////////////////////////////////////////////////

WiFiServer server;
WiFiClient client;
Servo servo[chCount];

void execute(String cmd) { // example command: "ch0 1500"
  if(cmd.startsWith("ch")) {
    int channel = cmd.substring(2, 3).toInt();
    bool space = cmd.substring(3, 4).equals(" ");
    if(channel>=0 && channel<=9 && space) {
      servo[channel].writeMicroseconds(cmd.substring(4).toInt());
    }
  }
}

void processIncomingChar(char c) {
  static String cmd = "";
  if(c=='\r' || c=='\n') {
    execute(cmd);
    cmd = "";
  } else {      
    cmd += c;
  }
}

void setup() {
  delay(500);

  for(int i=0; i<chCount; i++) {
    servo[i].attach(servoPin[i], usMin, usMax); // attach servos to pins
    servo[i].writeMicroseconds((usMin + usMax)/2); // initial value = middle
  }

  // Access Point mode -> phone connects directly to ESP (no router)
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask); 
  WiFi.softAP(ssid, pass);

  server.begin(port); // start TCP Server 
}

void loop() {
  if(!client.connected()) {
    client = server.available();
  } else if(client.available()) {
    processIncomingChar((char)client.read());
  }
}
