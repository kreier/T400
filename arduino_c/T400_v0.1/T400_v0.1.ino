/**
  @file    wifi_car_esp8266_AP.ino
  @brief   Simple example of Wifi Car controlled by a web server in AP Mode. See also :
           http://www.instructables.com/id/A-very-cheap-ESP8266-WiFi-smart-car-controlled-by-/

           Example of commands to control the car :
           
           MOVE:
           - http://<YourIP>:<YourPort>/move?dir=F (Forward)
           - http://<YourIP>:<YourPort>/move?dir=B (Bacward)
           
           ACTION:
           - http://<YourIP>:<YourPort>/action?type=1 (Action 1)
           - http://<YourIP>:<YourPort>/action?type=1 (Action 2)


  @author  LACOUR Vincent
  @date    2019-10
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

const char *ssid = "T401";
const char *password = "12345678";

IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);
const int port = 8080; // Port
ESP8266WebServer server(port);

U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 14);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 14, /* reset=*/ U8X8_PIN_NONE);
String inputstring = "";
unsigned char* terminal[150]; // 8 lines with 25 characters
int input = 0;
int line = 0;
String direction_old;

static const uint8_t pwm_A = 5 ;
static const uint8_t pwm_B = 4;
static const uint8_t dir_A = 0;
static const uint8_t dir_B = 2;

// Motor speed = [0-1024]
int motor_speed = 1024;

void setup() {
  u8g2.begin();
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_tf);
    u8g2.drawStr(0, 8,"T400 robot at AISVN ASA 3");
    u8g2.drawStr(0,16,"Creating WiFi network ...");
  } while (u8g2.nextPage() );
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_tf);
    u8g2.drawStr(0, 8,"T400 robot at AISVN ASA 3");
    u8g2.drawStr(0,16,"Creating WiFi network ...");
    u8g2.drawStr(0,24,"Please join: 'T401'");
    u8g2.drawStr(0,32,"Password: 12345678");
  } while (u8g2.nextPage() );

  pinMode(pwm_A, OUTPUT); // PMW A
  pinMode(pwm_B, OUTPUT); // PMW B
  pinMode(dir_A, OUTPUT); // DIR A
  pinMode(dir_B, OUTPUT); // DIR B

  server.on("/move", HTTP_GET, handleMoveRequest);
  server.on("/action", HTTP_GET, handleActionRequest);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleMoveRequest() {
  if (!server.hasArg("dir")) {
    server.send(404, "text / plain", "Move: undefined");
    return;
  }
  String direction = server.arg("dir");
  //if( direction != direction_old) {
  //  direction_old = direction;
  //  inputline(direction);
  //}
  if (direction.equals("F")) {
    forward();
    server.send(200, "text / plain", "Move: forward");
  }
  else if (direction.equals("B")) {
    backward();
    server.send(200, "text / plain", "Move: backward");
  }
  else  if (direction.equals("S")) {
    stop_motors();
    server.send(200, "text / plain", "Move: stop");
  }
  else  if (direction.equals("L")) {
    turn_left();
    server.send(200, "text / plain", "Turn: Left");
  }
  else  if (direction.equals("R")) {
    turn_right();
    server.send(200, "text / plain", "Turn: Right");
  }
  else {
    server.send(404, "text / plain", "Move: undefined");
  }
}


void handleActionRequest() {
  if (!server.hasArg("type")) {
    server.send(404, "text / plain", "Action: undefined");
    return;
  }
  String type = server.arg("type");
  if (type.equals("1")) {
    // TODO : Action 1
    server.send(200, "text / plain", "Action 1"); // robot arm servo over i2c comes here ...
  }
  else if (type.equals("2")) {
    // TODO : Action 2
    server.send(200, "text / plain", "Action 2");
  }
  else if (type.equals("3")) {
    // TODO : Action 3
    server.send(200, "text / plain", "Action 3");
  }
  else if (type.equals("4")) {
    // TODO : Action 4
    server.send(200, "text / plain", "Action 4");
  }
  else if (type.equals("5")) {
    // TODO : Action 5
    server.send(200, "text / plain", "Action 5");
  }
  else if (type.equals("6")) {
    // TODO : Action 6
    server.send(200, "text / plain", "Action 6");
  }
  else if (type.equals("7")) {
    // TODO : Action 7
    server.send(200, "text / plain", "Action 7");
  }
  else if (type.equals("8")) {
    // TODO : Action 8
    server.send(200, "text / plain", "Action 8");
  }
  else {
    server.send(404, "text / plain", "Action: undefined");
  }
}

void handleNotFound() {
  server.send(404, "text / plain", "404: Not found");
}


void stop_motors() {
  analogWrite(pwm_A, 0);
  analogWrite(pwm_B, 0);
}

void backward() {
  analogWrite(pwm_A, motor_speed);
  analogWrite(pwm_B, motor_speed);
  digitalWrite(dir_A, LOW);
  digitalWrite(dir_B, HIGH);
}

void forward() {
  analogWrite(pwm_A, motor_speed);
  analogWrite(pwm_B, motor_speed);
  digitalWrite(dir_A, HIGH);
  digitalWrite(dir_B, LOW);
}

void turn_left() {
  analogWrite(pwm_A, motor_speed);
  analogWrite(pwm_B, motor_speed);
  digitalWrite(dir_A, HIGH);
  digitalWrite(dir_B, HIGH);
}

void turn_right() {
  analogWrite(pwm_A, motor_speed);
  analogWrite(pwm_B, motor_speed);
  digitalWrite(dir_A, LOW);
  digitalWrite(dir_B, LOW);
}

void inputline(const char* inputstring) {
  u8g2.firstPage();
  input++;
  if( line * 25 + 25 > input) {         // we need a new line
    if( input > 150 ) {                 // end of screen
      memcpy(terminal, terminal + 25, 125);
    }
    for(int i = 125; i < 150; i++) {
      *terminal[i] = '\n';
    }
    //strncpy(*terminal, inputstring, 150);
  } else {
    //*terminal[line] = (unsigned char*)inputstring;
  }
  do {
    u8g2.setFont(u8g2_font_5x7_tf);
    for(int i = 0; i < 8; i++) {
      const char* whatever = (const char *)*terminal[34];
      u8g2.drawStr(0, 8+8*i, whatever);
    }
  } while (u8g2.nextPage() );
}
