#include <SetUp.h>
static int rpms180_xr = 100;
static int rpms180_xl = 100;

void setup(void) {
  Set_9D();
  Motor_init();
  isr_setup();

  //MsTimer2::set(100, timerFire); // 1000msごとにオンオフ
  //MsTimer2::start();
  
  motor_xl.High(),motor_xr.Low();

  pinMode(ledpin, OUTPUT);
  pinMode(swpin, INPUT);
}

void loop(){
  sei();
  delay(5000);
    while(1){
      //潜水・バランス用モータ制御部  
      if(digitalRead(swpin) == 0){
        rps_turn();
        otor_xl.Pwm(m_xl),motor_xr.Pwm(m_xr);
        motor_zl.Pwm(0),motor_zr.Pwm(0);
        motor_l.Pwm(0),motor_r.Pwm(0);
        LED_ON();
      }else{
        Stop();
        LED_OFF();
      }
    }
}

void rps_turn(){
  if(Rps[4] < rpms180_xr) m_xr = 30;
  else m_xr = 0;
  if(Rps[4] < rpms180_xl) m_xl = 30;
  else m_xl = 0;
}

