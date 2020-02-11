/*
  Read motion sensor esp8266

  version 1 - 9 Feb  2020
  author : KornWtp

*/

int motionPin = 13;
int motionState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motionPin, INPUT);

}

void loop() {
  motionState = digitalRead(motionPin);
  //  Serial.println(motionState);
  if (motionState == 1) {
    Serial.println("Someone Walking");
  } else {
    Serial.println("No People!");
  }

  delay(1000);
}
