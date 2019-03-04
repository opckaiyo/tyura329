
#ifndef ntc_h
#define ntc_h
#include <Arduino.h>

class ntc
{
  public:
    ntc(char SETUP);
    int get(int AnalogPin);               
  private:
	const	float e = 2.7182818284;
	float exponent;
	float voltage;
	float resistance;
	float rtLsit[100];
	int i;
};

#endif
