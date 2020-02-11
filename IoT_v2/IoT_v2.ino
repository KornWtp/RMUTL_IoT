/*
  IoT => motion sensor, vibration sensor, turbidity sensor, ldr sensor

  version 1 - 9 Feb  2020
  author : KornWtp

*/



#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_ADS1015.h>

Ticker secondTick;

#define debug 1

volatile int watchdogCount = 0;

//////// motion sensor ////////////
int motionPin = 13;
int motionState = 0;

//////// read sensor analog ////////
Adafruit_ADS1115 ads;
float scalefactor = 0.1875F;

float turbidity = 0.0;
float vibration = 0.0;
float ldr_sensor = 0.0;
float voltage = 0.0;

float temp_turbidity[100];
float temp_vibration[100];
float temp_ldr[100];
float temp_voltage[100];

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");

  pinMode(motionPin, INPUT);
  ads.setGain(GAIN_ONE);        // +/- 4.096V  1 bit = 0.125mV
  ads.begin();

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
  read_sensor();
  watchdogCount = 0;
  HTTPClient http;

  String url = "http://192.168.43.183/getdata.php?turbidity=" + String(turbidity) + "&vibration=" + String(vibration) +
               "&ldr_sensor=" + String(ldr_sensor) + "&voltage=" + String(voltage);
  Serial.println(url);
  http.begin(url); //HTTP
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);

      turbidity = 0.0;
      vibration = 0.0;
      ldr_sensor = 0.0;
      voltage = 0.0;
    }
  }
  else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());

  }
  http.end();

  Serial.print("Watchdog counter = ");
  Serial.println(watchdogCount);
  delay_time(60);
}


void watchdog() {
  watchdogCount++;
  if ( watchdogCount == 10 ) {
    // Only print to serial when debugging
    Serial.println("The dog bites!");
    ESP.reset();
  }
}

void read_sensor() {
  float get_turbidity[10];
  float get_vibration[10];
  float get_ldr[10];
  float get_voltage[10];

  int16_t adc0, adc1, adc2, adc3;

  motionState = digitalRead(motionPin);

  //  for (int i = 0; i < 10; i++) {
  //    adc0 = ads.readADC_SingleEnded(0);
  //    adc1 = ads.readADC_SingleEnded(1);
  //    adc2 = ads.readADC_SingleEnded(2);
  //    adc3 = ads.readADC_SingleEnded(3);
  //
  //    get_turbidity[i] = (adc0 * scalefactor) / 1000;
  //    get_vibration[i] = (adc1 * scalefactor) / 1000;
  //    get_ldr[i] = (adc2 * scalefactor) / 1000;
  //    get_voltage[i] = (adc3 * scalefactor) / 1000;
  //
  //    turbidity += get_turbidity[i];
  //    vibration += get_vibration[i];
  //    ldr_sensor = get_ldr[i];
  //    voltage = get_voltage[i];
  //  }
  //
  //  turbidity /= 10;
  //  vibration /= 10;
  //  ldr_sensor /= 10;
  //  voltage /= 10;

  //  Serial.print("turbidity: "); Serial.print(turbidity); Serial.println(" V");
  //  Serial.print("vibration: "); Serial.print(vibration); Serial.println(" V");
  //  Serial.print("ldr_sensor: "); Serial.print(ldr_sensor); Serial.println(" V");
  //  Serial.print("voltage: "); Serial.print(voltage); Serial.println(" V");
  //  Serial.println(" ");

  for (int i = 0; i < 10; i++) {
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    adc2 = ads.readADC_SingleEnded(2);
    adc3 = ads.readADC_SingleEnded(3);

    get_turbidity[i] = map(adc0, 0, 32768, 0, 100);
    get_vibration[i] = map(adc1, 0, 32768, 0, 100);
    get_ldr[i] = map(adc2, 0, 32768, 0, 100);
    get_voltage[i] = (adc3 * scalefactor) / 1000;

    turbidity += get_turbidity[i];
    vibration += get_vibration[i];
    ldr_sensor = get_ldr[i];
    voltage = get_voltage[i];
  }

  turbidity /= 10;
  vibration /= 10;
  ldr_sensor /= 10;
  voltage /= 10;

  Serial.print("turbidity: "); Serial.print(turbidity); Serial.println(" %");
  Serial.print("vibration: "); Serial.print(vibration); Serial.println(" %");
  Serial.print("ldr_sensor: "); Serial.print(ldr_sensor); Serial.println(" %");
  Serial.print("voltage: "); Serial.print(voltage); Serial.println(" V");
  Serial.println(" ");

}

void delay_time(int t) {
  for (int i = 0; i < t; i++) {
    watchdogCount = 0;
    delay(1000);
  }
}
