#include "config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define pump 5
#define light 16

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println(WiFi.localIP());
  pinMode(pump, OUTPUT);
  pinMode(light, OUTPUT);
  digitalWrite(light, LOW);
  digitalWrite(pump, LOW);

  //Wifi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(NETID);

  WiFi.begin(NETID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
}

void sendWaterMessage() {
  delay(1000);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(URL);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
    }
    http.end();
  }
  else {
    Serial.println("WiFi not connected");
  }
}
    
void loop() {
  Serial.println("in the loop");
  delay(10000);
  digitalWrite(pump, HIGH);
  digitalWrite(light, HIGH);
  sendWaterMessage();
  delay(2000);
  digitalWrite(pump, LOW);
  digitalWrite(light, LOW);
}
