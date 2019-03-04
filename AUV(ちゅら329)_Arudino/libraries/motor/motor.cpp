
#include <Arduino.h>
#include <motor.h>

motor::motor(int dc, int pwm){
  pinMode(dc,OUTPUT);
  SetPinDc = dc;
  pinMode(pwm,OUTPUT);
  SetPinPwm = pwm;
}

void motor::High(){
  digitalWrite(SetPinDc,HIGH);
}

void motor::Low(){
  digitalWrite(SetPinDc,LOW);
}

void motor::Pwm(int pwm){
  pwm = map(pwm, 0, 60, 0, 255);
  analogWrite(SetPinPwm,pwm);
}
