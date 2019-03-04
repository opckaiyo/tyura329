#include <SetUp.h>
          
void setup(void) {
  Set_9D();
  Motor_init();
  
  MsTimer2::set(100, timerFire);
  MsTimer2::start();

  pinMode(ledpin, OUTPUT);
  pinMode(swpin, INPUT);
}

//100ms毎にここが呼び出される
void timerFire() {
  time100ms++;
  Serial.print("time : ");
  Serial.println(time100ms);
  if(time100ms <= 50){
    motor_init_pwm = 30;
  }else if(time100ms <= 10){
    motor_init_pwm = 70;
  }else time100ms = 0;
}

//推進モータ制御部
void motor(){
  if(!Turning){
    m_l = motor_init_pwm;
    m_r = motor_init_pwm;
  }
}

void loop(void) {
  Get_9D();
  //モータ制御部  
  if(digitalRead(swpin) == 0){  
    motor();
    LED_ON();
    Pwm_Output();
  }else{
    Stop();
    LED_OFF();
  }
}
