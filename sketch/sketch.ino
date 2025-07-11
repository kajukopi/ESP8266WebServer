#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoOTA.h>
#include <Servo.h>
#include "webpage.h" // <-- HTML dipisahkan di sini

const char* ssid = "karimroy";
const char* password = "09871234";

// IP Static
IPAddress local_IP(192, 168, 248, 182);
IPAddress gateway(192, 168, 248, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

Servo myServo;
const int servoPin = D5;
const int ledPin = LED_BUILTIN;

String getSignalStrength() {
  int32_t rssi = WiFi.RSSI();
  String strength;
  if (rssi > -50) strength = "Excellent";
  else if (rssi > -60) strength = "Very Good";
  else if (rssi > -70) strength = "Good";
  else if (rssi > -80) strength = "Fair";
  else strength = "Weak";
  return String(rssi) + " dBm (" + strength + ")";
}

void handleRoot() {
  String html = MAIN_HTML;
  html.replace("%IP%", WiFi.localIP().toString());
  html.replace("%SIGNAL%", getSignalStrength());
  server.send(200, "text/html", html);
}

void handleSetServo() {
  if (server.hasArg("percent")) {
    int percent = server.arg("percent").toInt();
    int micro = map(percent, 0, 100, 500, 2500);
    myServo.writeMicroseconds(micro);
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Missing 'percent'");
  }
}

void handleToggleLED() {
  if (server.hasArg("state")) {
    String state = server.arg("state");
    digitalWrite(ledPin, (state == "on") ? LOW : HIGH);
    server.send(200, "text/plain", "LED " + state);
  } else {
    server.send(400, "text/plain", "Missing 'state'");
  }
}

void handleUpdatePage() {
  server.send(200, "text/html", UPDATE_HTML);
}

void setup() {
  Serial.begin(115200);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  myServo.attach(servoPin);
  myServo.writeMicroseconds(500);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  server.on("/", handleRoot);
  server.on("/setServo", handleSetServo);
  server.on("/toggleLED", handleToggleLED);
  server.on("/update", HTTP_GET, handleUpdatePage);

  httpUpdater.setup(&server, "/update");

  server.begin();
  ArduinoOTA.begin();
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();
}