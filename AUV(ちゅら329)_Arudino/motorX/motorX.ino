#include <SetUp.h>
    
void setup(void) {
  Set_9D();
  Motor_init();

  MsTimer2::set(250, flash); // 1000msごとにオンオフ
  MsTimer2::start();

  pinMode(ledpin, OUTPUT);
  pinMode(swpin, INPUT);
}

//推進補助・方向転換用モータ制御部
//9軸センサの「X」、Xは0~360で変化する
//Return = falseのときに住路
//Returnk = trueのときに復路
//Xモータはドライバに接続する際、±を逆に接続する必要がある
void motorX(){
  if(!Turning){
    //Xが0～360で変化するからXの値の調整を行い、住路、復路とも０から変動するようにする
    //住路方向に進行
    DataX = X;
    //test用
    //Return = true;
    if(!Return && DataX > 180) DataX = int(X) - 360;
    //復路方向に進行
    else if(Return) DataX = int(X) - 180;
    //Xモータのみ使用
    //左に傾く
    if(DataX <= -3){
      motor_xl.High(),motor_xr.Low();
      m_xr = motorX_init_pwm - DataX;
      m_xl = motorX_init_pwm - DataX;

    //右に傾く
    }else if(DataX >= 3){
      motor_xl.Low(),motor_xr.High();
      m_xr = motorX_init_pwm + DataX;
      m_xl = motorX_init_pwm + DataX;
    }else{
    //変更必要？
      m_xr = 0;
      m_xl = 0;
    }
    
    if(m_xr >= 60)  m_xr = 60;
    if(m_xr <= 0)   m_xr = 0;
    if(m_xl >= 60)  m_xl = 60;
    if(m_xl <= 0)   m_xl = 0;
  }
}

void loop(void) {
  Get_9D();
  //潜水・バランス用モータ制御部  
  if(digitalRead(swpin) == 0){
    motorX();
    LED_ON();
    Pwm_Output();
  }else{
    Stop();
    LED_OFF();
  }
}

void flash(){
    /*
    Serial.print("X : ");
    Serial.println(X);
    Serial.print("DataX : ");
    Serial.println(DataX);
    if(DataX > 3) Serial.println("右に傾く");
    else if(DataX < -3)  Serial.println("左に傾き");
    Serial.print("m_xr : ");
    Serial.println(m_xr);
    Serial.print("m_xl : ");
    Serial.println(m_xl);
    Serial.println("");
    */
    Serial.print("Rps[5] : ");
    Serial.println(Rps[5]);
    Serial.print("Rps[4] : ");
    Serial.println(Rps[5]);
    Serial.println("");
    
}
