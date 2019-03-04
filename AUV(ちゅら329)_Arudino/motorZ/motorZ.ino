#include <SetUp.h>

int cnt = 0;

void setup(void) {
  Set_9D();
  Motor_init();

  MsTimer2::set(100, timerFire); // 1000msごとにオンオフ
  MsTimer2::start();

  pinMode(ledpin, OUTPUT);
  pinMode(swpin, INPUT);
  pinMode(A14, INPUT);
}

//100ms毎にここが呼び出される
void timerFire() {
  time100ms++;
  if(time100ms <= 100) {
    Diving = true;
  }else if(time100ms <= 200){
    Diving = false;
  }else if(time100ms >= 200){
    time100ms = 0;
  }
}

//moguru
long Dive = 340;
//huzyou
long Emerge = 475;

void motorZ(){
  aturyoku = analogRead(A14);
  if(Diving){
    DivingPlus = Dive-aturyoku;
    motorZ_init_pwm = 0;
    if(DivingPlus >= 0) motor_zl.High(),motor_zr.High();
    else motor_zl.Low(),motor_zr.Low(),DivingPlus *= -1;
  }else if(!Diving){
    motorZ_init_pwm = aturyoku - Emerge;
    DivingPlus = 0;
    if(motorZ_init_pwm >= 0)  motor_zl.Low(),motor_zr.Low();
    else motor_zl.High(),motor_zr.High(),motorZ_init_pwm *= -1 ;
  }
  m_zr = motorZ_init_pwm + DivingPlus;
  m_zl = motorZ_init_pwm + DivingPlus;

  if(m_zr >= 30)  m_zr = 30;
  else if(m_zr <= 0)   m_zr = 0;
  if(m_zl >= 30)  m_zl = 30;
  else if(m_zl <= 0)   m_zl = 0;
}

void loop(void) {
  if(digitalRead(swpin) == 1){
      if(cnt == 0){
        Set_9D();
        MsTimer2::start();
        cnt = 1;
      }
  }
  while(cnt){
    if(digitalRead(swpin) == 1){
      Get_9D();
      if(!Turning){
        motorZ();
      }
      Pwm_Output();
    }else{
      Stop();
    }
    //delay(250);
    Serial.print("aturyoku : ");
    Serial.println(analogRead(A14));
  }
}
