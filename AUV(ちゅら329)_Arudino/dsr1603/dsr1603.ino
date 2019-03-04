 #include <SetUp.h>

void setup(void) {
  Set_9D();
}

void loop(void) {
  //delay(250);
  Get_9D();
  Serial.print("X: ");
  Serial.println(X);
}
