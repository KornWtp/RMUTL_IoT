/*
  read sensor:
    adc0 => turbidity sensor
    adc1 => vibration sensor
    adc2 => ldr sensor

  version 1 - 9 Feb  2020
  author : KornWtp
*/

#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;
float scalefactor = 0.1875F;

float turbidity = 0.0;
float vibration = 0.0;
float ldr_sensor = 0.0;
float voltage = 0.0;
 
void setup(void) 
{
  Serial.begin(9600);
 
  // ads.setGain(GAIN_TWOTHIRDS);  // +/- 6.144V  1 bit = 0.1875mV (default)
   ads.setGain(GAIN_ONE);        // +/- 4.096V  1 bit = 0.125mV
//   ads.setGain(GAIN_TWO);        // +/- 2.048V  1 bit = 0.0625mV
  // ads.setGain(GAIN_FOUR);       // +/- 1.024V  1 bit = 0.03125mV
  // ads.setGain(GAIN_EIGHT);      // +/- 0.512V  1 bit = 0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // +/- 0.256V  1 bit = 0.0078125mV 
  ads.begin();
}
 
void loop(void) 
{
  int16_t adc0, adc1, adc2, adc3;
 
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

//  turbidity = (adc0 * scalefactor)/1000;
//  vibration = (adc1 * scalefactor)/1000;
//  ldr_sensor = (adc2 * scalefactor)/1000;
//  voltage = (adc3 * scalefactor)/1000;
  
//  Serial.print("turbidity: "); Serial.print(turbidity); Serial.println(" V");
//  Serial.print("vibration: "); Serial.print(vibration); Serial.println(" V");
//  Serial.print("ldr_sensor: "); Serial.print(ldr_sensor); Serial.println(" V");
//  Serial.print("voltage: "); Serial.print(voltage); Serial.println(" V");
//  Serial.println(" ");

  turbidity = map(adc0, 0, 32768, 0, 100);
  vibration = map(adc1, 0, 32768, 0, 100);
  ldr_sensor = map(adc2, 0, 32768, 0, 100);
  voltage = (adc3 * scalefactor)/1000;
  
  Serial.print("turbidity: "); Serial.print(turbidity); Serial.println(" %");
  Serial.print("vibration: "); Serial.print(vibration); Serial.println(" %");
  Serial.print("ldr_sensor: "); Serial.print(ldr_sensor); Serial.println(" %");
  Serial.print("voltage: "); Serial.print(voltage); Serial.println(" V");
  Serial.println(" ");
  
  delay(1000);
}
