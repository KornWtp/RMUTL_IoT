/*
  IoT => motion sensor, vibration sensor, turbidity sensor, ldr sensor

  version 1 - 2 Feb  2020
  author : KornWtp

*/



#include <Ticker.h>
#include <ESP8266WiFi.h>          
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         
#include <ESP8266HTTPClient.h>

Ticker secondTick;

#define debug 1

volatile int watchdogCount = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting");
  secondTick.attach(1, watchdog);

  WiFiManager wifiManager;
  //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  wifiManager.autoConnect("IoT_KornWtp");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected...OK :)");
  Serial.flush();
}

void loop() {
  watchdogCount = 0;

  HTTPClient http;
  int temp = random(25, 35);
  String url = "http://192.168.43.183/getdata.php?motion_sensor=" + String(temp);
  Serial.println(url);
  http.begin(url); //HTTP
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

  Serial.print("Watchdog counter = ");
  Serial.println(watchdogCount);

  delay_time(5);
}


void watchdog() {
  watchdogCount++;
  if ( watchdogCount == 5 ) {
    // Only print to serial when debugging
    (debug) && Serial.println("The dog bites!");
    ESP.reset();
  }
}

void delay_time(int t) {
  for (int i = 0; i < t; i++) {
    delay(1000);
  }
}
