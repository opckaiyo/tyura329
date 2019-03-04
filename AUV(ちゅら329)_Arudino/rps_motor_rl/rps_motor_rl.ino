#include <SetUp.h>
static int rpms_pwm_r = 10;
static int rpms_pwm_l = 10;
static int rpms_sitei_r = 30;
static int rpms_sitei_l = 30;

void setup(void) {
  Set_9D();
  Motor_init();
  isr_setup();

  MsTimer2::set(100, timerFire); // 1000msごとにオンオフ
  MsTimer2::start();
  
  pinMode(ledpin, OUTPUT);
  pinMode(swpin, INPUT);
}

void loop(){
  sei();
    while(1){
      //潜水・バランス用モータ制御部  
      if(digitalRead(swpin) == 1){
        //motor_xl.Pwm(rpms_pwm_l),motor_xr.Pwm(rpms_pwm_r);
        //motor_zl.Pwm(rpms_pwm_l),motor_zr.Pwm(rpms_pwm_r);
        motor_l.Pwm(rpms_pwm_l),motor_r.Pwm(rpms_pwm_r);
        LED_ON();
      }else{
        Stop();
        LED_OFF();
      }
    }
}

void timerFire(){
  if(digitalRead(swpin) == 1){
  time100ms++;
  
  Rpms_save[1] = Rpms[1];//r
  Rpms_save[3] = Rpms[3];//l
  //Rpms_save[1] = Rpms[0];//zr
  //Rpms_save[3] = Rpms[2];//zl
  //Rpms_save[1] = Rpms[5];//xr
  //Rpms_save[3] = Rpms[4];//xl
  
  if(Rpms_save[1] ==  rpms_sitei_r)  rpms_pwm_r;
  else if(Rpms_save[1] + 5 < rpms_sitei_r)  rpms_pwm_r += 5;
  else if(Rpms_save[1] + 3 < rpms_sitei_r)  rpms_pwm_r += 3;
  else if(Rpms_save[1] < rpms_sitei_r)  rpms_pwm_r += 1;
  else if(Rpms_save[1] - 5 > rpms_sitei_r) rpms_pwm_r -= 5;
  else if(Rpms_save[1] - 3 > rpms_sitei_r) rpms_pwm_r -= 3;
  else if(Rpms_save[1] > rpms_sitei_r) rpms_pwm_r -= 1;
  
  if(Rpms_save[3] ==  rpms_sitei_l)  rpms_pwm_l;
  else if(Rpms_save[3] + 5 < rpms_sitei_l)  rpms_pwm_l += 5;
  else if(Rpms_save[3] + 3 < rpms_sitei_l)  rpms_pwm_l += 3;
  else if(Rpms_save[3] < rpms_sitei_l)  rpms_pwm_l += 1;
  else if(Rpms_save[3] - 5 > rpms_sitei_l) rpms_pwm_l -= 5;
  else if(Rpms_save[3] - 3 > rpms_sitei_l) rpms_pwm_l -= 3;
  else if(Rpms_save[3] > rpms_sitei_l) rpms_pwm_l -= 1;
  
  rpmszero_set();
  
  if(time100ms % 10 == 0){
    
    //rl
    Serial.print("R : ");
    Serial.print(Rps[1]);
    Serial.print("  PWM : ");
    Serial.println(rpms_pwm_r);
    Serial.print("R : ");
    Serial.print(Rps[3]);
    Serial.print("  PWM : ");
    Serial.println(rpms_pwm_l);
    /*
    //z
    Serial.print("ZR : ");
    Serial.print(Rps[0]);
    Serial.print("  PWM : ");
    Serial.println(rpms_pwm_r);
    Serial.print("ZR : ");
    Serial.print(Rps[2]);
    Serial.print("  PWM : ");
    Serial.println(rpms_pwm_l);
    */
    /*
    //x
    Serial.print("XR : ");
    Serial.print(Rps[5]);
    Serial.print("  PWM : ");
    Serial.println(rpms_pwm_r);
    Serial.print("XL : ");
    Serial.print(Rps[4]);
    Serial.print("  PWM : ");
    Serial.println(rpms_pwm_l);
    */
    Serial.println("");
    
    zero_set();
  }
  }
}
