#include <SetUp.h>

void setup(){
  Set_9D();
  Set_Puropo();
  pinMode(ledpin, OUTPUT);
  pinMode(swpin, INPUT);
}

void loop(){
    if(digitalRead(swpin) == 1){
    Get_Puropo();
  
    if(RV1 >= 0){
      motor_l.High(),motor_r.High(); 
    }else{
      RV1 = -RV1;
      motor_l.Low(),motor_r.Low();
    }
  
    if(RV2 >= 0){
      motor_xl.High(),motor_xr.Low();
    }else{
      RV2 = -RV2;
      motor_xl.Low(),motor_xr.High();
    }
    /*
    if(RV4 >= 0){
      motor_zl.High(),motor_zr.High();
    }else{
      RV4 = -RV4;
      motor_zl.Low(),motor_zr.Low();
    }
    */
//    m_zl = RV4,m_zr = RV4;
    //m_zl = 0,m_zr = 0;
    m_xl = RV2,m_xr = RV2;
    m_l  = RV1,m_r  = RV1;
  }else{
    Stop();
  }
  Pwm_Output();
      Serial.print("RV1: ");
    Serial.print(RV1);
    Serial.print(" RV2: ");
    Serial.print(RV2);
    Serial.print(" RV4: ");
    Serial.println(RV4);
}

