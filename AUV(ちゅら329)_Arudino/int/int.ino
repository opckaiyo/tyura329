#include <pcint_int.h>

void setup() {
  isr_setup();
}

void loop() {
  digitalWrite(pin, state);
}
