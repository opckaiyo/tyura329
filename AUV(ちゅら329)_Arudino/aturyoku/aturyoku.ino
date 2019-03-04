void setup() {
  Serial.begin(115200);
  pinMode(A14, INPUT);
}

void loop() {
  delay(500);
  Serial.print("aturyoku : ");
  Serial.println(analogRead(A14));
}
