
#include <Arduino.h>
#include <ntc.h>

ntc::ntc(char SETUP){
	for (int i =0; i < 100; i++){
		exponent = 3435 * ((1.0 / (i + 273.15)) - (1.0 / (25 + 273.15)));
		rtLsit[i] = (10000 * pow(e,exponent));
	}
}

int ntc::get(int AnalogPin){
  voltage = (analogRead(AnalogPin) / 1024.0) * 5.0;
  resistance = voltage / (5.0 - voltage) * 10000;       
  for (i =0; i < 100; i++){
    if (resistance > rtLsit[i]){
      break;
    }
  }
  return (i-1);  
}

