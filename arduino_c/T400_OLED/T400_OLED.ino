/**
  @brief   Control ESP8266 Wifi Car with a smartphone in AP mode
  @author  Matthias Kreier
  @date    2024-03-13
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <U8g2lib.h>

const char *ssid = "Wificar24";
const char *password = "12345678";

IPAddress ip(192, 168, 42, 17);
IPAddress netmask(255, 255, 255, 0);
const int port = 8080; // Port
ESP8266WebServer server(port);

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 12, 14);
const char *dir = "X";

static const uint8_t pwm_A = 5 ;
static const uint8_t pwm_B = 4;
static const uint8_t dir_A = 0;
static const uint8_t dir_B = 2;

// Motor speed = [0-1024]
int motor_speed = 1024;

void setup() {
  Serial.begin(74880);
  Serial.println("\nWificar24");
  u8g2.begin();
  u8g2.setFont(u8g2_font_helvR10_tf);
  u8g2.drawStr(0,16,"SSID: T400_OLED");
  u8g2.drawStr(0,32,"PW: 12345678");
  u8g2.sendBuffer();  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);

  pinMode(pwm_A, OUTPUT); // PMW A
  pinMode(pwm_B, OUTPUT); // PMW B
  pinMode(dir_A, OUTPUT); // DIR A
  pinMode(dir_B, OUTPUT); // DIR B

  server.on("/move", HTTP_GET, handleMoveRequest);
  server.onNotFound(handleNotFound);
  server.begin();
  u8g2.drawStr(0,48,"IP: 192.168.18.1");
  u8g2.drawStr(0,64,"Port: 8080");
  u8g2.sendBuffer();  
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
  if (direction.equals("F")) {
    forward();
    server.send(200, "text / plain", "Move: forward");
    dir = "F";
  }
  else if (direction.equals("B")) {
    backward();
    server.send(200, "text / plain", "Move: backward");
    dir = "B";
  }
  else  if (direction.equals("S")) {
    stop_motors();
    server.send(200, "text / plain", "Move: stop");
    dir = "S";
  }
  else  if (direction.equals("L")) {
    turn_left();
    server.send(200, "text / plain", "Turn: Left");
    dir = "L";
  }
  else  if (direction.equals("R")) {
    turn_right();
    server.send(200, "text / plain", "Turn: Right");
    dir = "R";
  }
  else {
    server.send(404, "text / plain", "Move: undefined");
  }
  u8g2.setFont(u8g2_font_profont17_mf);
  u8g2.drawStr(110,64,dir);
  u8g2.sendBuffer();    
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
