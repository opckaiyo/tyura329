#include <SetUp.h>
    
void setup(void) {
  Set_9D();
  Motor_init();
  isr_setup();
  
  MsTimer2::set(1000, flash); // 1000msごとにオンオフ
  MsTimer2::start();

  pinMode(ledpin, OUTPUT);
  pinMode(swpin, INPUT);
}

void loop(){
  //sei();
    while(1){
      //潜水・バランス用モータ制御部  
      if(digitalRead(swpin) == 0){
        motor_zl.Pwm(30),motor_zr.Pwm(30);
        motor_xl.Pwm(30),motor_xr.Pwm(30);
        motor_l.Pwm(100),motor_r.Pwm(70);
        LED_ON();
      }else{
        Stop();
        LED_OFF();
      }
    }
}

void flash(){
  RM1=Rps[0],RM2=Rps[2],RM3=Rps[1],RM4=Rps[3],RM5=Rps[5],RM6=Rps[4];
  Serial.println("ロータリーエンコーダー");
  Serial.print("ZR_RPS[0] : "),Serial.print(RM1);
  Serial.print("  ZL_RPS[1] : "),Serial.print(RM2);
  Serial.print("  R_RPS[2] : "),Serial.print(RM3);
  Serial.print("  L_RPS[3] : "),Serial.print(RM4);
  Serial.print("  XR_RPS[4] : "),Serial.print(RM5);
  Serial.print("  XL_RPS[5] : "),Serial.println(RM6);
  Serial.println("");

  FM1=Rps[6],FM2=Rps[7],FM3=Rps[8],FM4=Rps[9];
  //FM1 = 0,FM2 = 0,FM3 = 0,FM4 = 0;
  S_FM = String(FM1)+","+String(FM2)+","+String(FM3)+","+String(FM4)+",";
  Serial.println("流速計");
  Serial.print("ZR_RPS[6] : "),Serial.print(FM1);
  Serial.print("  ZL_RPS[7] : "),Serial.print(FM2);
  Serial.print("  XR_RPS[8]  : "),Serial.print(FM3);
  Serial.print("  XL_RPS[9]  : "),Serial.println(FM4);
  Serial.println("");

  NTC1=ntc.get(0),NTC2=ntc.get(1),NTC3=ntc.get(2),NTC4=ntc.get(3),NTC5=ntc.get(4),NTC6=ntc.get(5),NTC7=ntc.get(6);
  Serial.println("温度センサ");
  Serial.print("ZR_NTC[0] : "),Serial.print(NTC1);  //A0
  Serial.print("  ZL_NTC[1] : "),Serial.print(NTC2);  //A1
  Serial.print("  R_NTC[2]  : "),Serial.print(NTC3);  //A2
  Serial.print("  L_NTC[3]  : "),Serial.println(NTC4);//A3
  Serial.print("  XR_NTC[4]  : "),Serial.print(NTC5);  //A4
  Serial.print("  XL_NTC[5]  : "),Serial.println(NTC6);//A5
  Serial.print("  Arduino_NTC[6]  : "),Serial.println(NTC7);//A6
  Serial.println("");
  
  zero_set();
}
