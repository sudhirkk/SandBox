void setup() {
  int motorPin = 11;
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 0);
}

void loop() {
  //analogWrite(11, 0);
  for (int i=0; i< 255; i++) {
    analogWrite(11, i);
    delay(5);
  }
}
