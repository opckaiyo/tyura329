
#ifndef motor_h
#define motor_h
#include <Arduino.h>

class motor
{
  public:
    motor(int dc, int pwm);
    void High();       
    void Low();
    void Pwm(int pwm);        
  private:
    int SetPinDc;
    int SetPinPwm;
    int m_zr = 0;
    int m_zl = 0; 
};

#endif
