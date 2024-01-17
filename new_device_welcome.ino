const int teamNumber = 1;

const char* message = "Norse IoT and the INTERalliance "
  "welcomes "
  "TechOlympics Team %03d!\n";

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.printf(message, teamNumber);
  delay(2000);
}
