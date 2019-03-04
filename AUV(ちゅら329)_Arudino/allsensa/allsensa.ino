//このプログラムはすべての通信の動作確認用のプログラム

//初期セットアップ用ライプラリ読み込み
#include <SetUp.h>

void setup(void) {
  Set_9D();
  Motor_init();
  isr_setup();
  MsTimer2::set(1000, timerFire);
  MsTimer2::start();
  
  Rps[0] = 0,Rps[1] = 0,Rps[2] = 0,Rps[3] = 0,Rps[4] = 0,Rps[5] = 0;
  Rps[6] = 0,Rps[7] = 0,Rps[8] = 0,Rps[9] = 0;
  Rotation[0] = 0,Rotation[1] = 0,Rotation[2] = 0,Rotation[3] = 0,Rotation[4] = 0;
  Rotation[5] = 0,Rotation[6] = 0,Rotation[7] = 0,Rotation[8] = 0,Rotation[9] = 0;  
  
  pinMode(ledpin, OUTPUT);
  pinMode(swpin, INPUT);
  pinMode(A14, INPUT);
}

void loop(void) {
  sei();
  while(1){
    Get_9D();
    //非常停止のフラグ確認
    if(digitalRead(swpin) == 1){
        m_zr = 10;
        m_zl = 10;
        m_xr = 10;
        m_xl = 10;
        m_r  =  10;
        m_l  =  10;
        motor_zl.Pwm(m_zl),motor_zr.Pwm(m_zr);
        motor_xl.Pwm(m_xl),motor_xr.Pwm(m_xr);
        motor_l.Pwm(m_l),motor_r.Pwm(m_r);
        LED_ON();
    }else{
      Stop();
      LED_OFF();
    }
  }
}


void timerFire() {  
  RM1=Rps[0],RM2=Rps[2],RM3=Rps[1],RM4=Rps[3],RM5=Rps[5],RM6=Rps[4];
  S_RM = String(RM1)+","+String(RM2)+","+String(RM3)+","+String(RM4)+","+String(RM5)+","+String(RM6)+",";
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
  Serial.print("XR_RPS[6] : "),Serial.print(FM1);
  Serial.print("  XL_RPS[7] : "),Serial.print(FM2);
  Serial.print("  R_RPS[8]  : "),Serial.print(FM3);
  Serial.print("  L_RPS[9]  : "),Serial.println(FM4);
  Serial.println("");
  
  PS = analogRead(A14);
  S_PS =String(PS)+",";
  Serial.println("圧力センサ");
  Serial.print("圧力センサ : "),Serial.println(PS);  //A14
  Serial.println("");

  NTC1=ntc.get(0),NTC2=ntc.get(1),NTC3=ntc.get(2),NTC4=ntc.get(3),NTC5=ntc.get(4),NTC6=ntc.get(5),NTC7=ntc.get(6);
  S_NTC = String(NTC1)+","+String(NTC2)+","+String(NTC3)+","+String(NTC4)+","+String(NTC5)+","+String(NTC6)+","+String(NTC7)+",";
  Serial.println("温度センサ");
  Serial.print("ZR_NTC[0] : "),Serial.print(NTC1);  //A0
  Serial.print("  ZL_NTC[1] : "),Serial.print(NTC2);  //A1
  Serial.print("  R_NTC[2]  : "),Serial.print(NTC3);  //A2
  Serial.print("  L_NTC[3]  : "),Serial.println(NTC4);//A3
  Serial.print("  XR_NTC[4]  : "),Serial.print(NTC5);  //A4
  Serial.print("  XL_NTC[5]  : "),Serial.println(NTC6);//A5
  Serial.print("  Arduino_NTC[6]  : "),Serial.println(NTC7);//A6
  Serial.println("");
  
  CS1=0,CS2=0,CS3=0;
  S_CS = String(CS1)+","+String(CS2)+","+String(CS3)+",";
  CS4=0,CS5=0,CS6=0;
  S_CS2 = String(CS4)+","+String(CS5)+","+String(CS6)+",";
  Serial.println("電流センサ");
  Serial.print("ZR_CS : "),Serial.print(CS1);    //A8
  Serial.print("  ZL_CS : "),Serial.print(CS2);   //A9
  Serial.print("  XR_CS : "),Serial.print(CS3);  //A10
  Serial.print("  XL_CS : "),Serial.print(CS4);  //A11
  Serial.print("  R_CS : "),Serial.print(CS5);   //A12
  Serial.print("  L_CS : "),Serial.println(CS6); //A13
  Serial.println("");
  
  VS1=0;
  S_VS = String(VS1)+",";
  Serial.println("電圧センサ");
  Serial.print("電圧センサ : "),Serial.println(m_zr);
  Serial.println("");
  
  PWM1=m_zr,PWM2=m_zl,PWM3=m_xr,PWM4=m_xl,PWM5=m_r,PWM6=m_l;
  S_PWM = String(PWM1)+","+String(PWM2)+","+String(PWM3)+","+String(PWM4)+","+String(PWM5)+","+String(PWM6)+",";
  Serial.println("モータPWM");
  Serial.print("M_ZR : "),Serial.print(m_zr);
  Serial.print("  M_ZL : "),Serial.print(m_zl);
  Serial.print("  M_XR : "),Serial.print(m_xr);
  Serial.print("  M_XL : "),Serial.print(m_xl);
  Serial.print("  M_R  : "),Serial.print(m_r);
  Serial.print("  M_L  : "),Serial.println(m_l);
  Serial.println("");
  
  X9D=X,Y9D=Y,Z9D=Z;
  S_9D = String(X9D)+","+String(Y9D)+","+String(Z9D)+",";
  Serial.println("コンパス");
  Serial.print("X : "),Serial.print(X9D);
 // Serial.print("  Y : "),Serial.print(Y9D);
  //Serial.print("  Z : "),Serial.println(Z9D);
  Serial.println("");

  zero_set();
  
  S_ALLDATA=S_RM+S_FM+S_PS+S_NTC+S_CS+S_CS2+S_VS+S_PWM+S_9D;
  //Serial.println(S_ALLDATA);
}

