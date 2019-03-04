#include <MsTimer2.h>

int time100ms = 0;

void flash() {
  time100ms++;
  Serial.print("time : ");
  Serial.println(time100ms);
}

void setup() {
  Serial.begin(9600);

  MsTimer2::set(100, flash); // 1000msごとにオンオフ
  MsTimer2::start();
}

void loop() {

}

