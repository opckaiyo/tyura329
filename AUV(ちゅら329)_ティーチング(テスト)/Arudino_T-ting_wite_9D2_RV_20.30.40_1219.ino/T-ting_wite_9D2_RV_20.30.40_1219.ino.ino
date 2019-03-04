#include <SetUp.h>
#include <stdio.h>
#include <string.h>
#include <ArduinoJson.h>
static long cnt0 = 0;
static long cnt1 = 0;
static int midori = 41;
static int aka = 39;
static int ao = 37;
static long TimerA=0;
static int flgA=2;
static int buffer_len=0;
static int long Y_PWM=0;
static int long X_PWM=0;
static int long Z_PWM=0;
static char buffer[500];
static StaticJsonBuffer<500> jsonBuffer;
static JsonObject& root = jsonBuffer.createObject();

static int mod_flg=0;
static int mod_timer_flg=0;

int F1_r_Pin = 2;
int F2_l_Pin = 3;
int F3_zr_Pin = 18;
int F4_zl_Pin = 19;


static long F1_xr=0;
static long F2_xl=0;
static long F3_zr=0;
static long F4_zl=0;
static long M1_r=0;
static long M2_l=0;

static double val1_a = 0;  //XL
static double val2_a = 0;  //XR
static double val3_a = 0;  //L
static double val4_a = 0;  //R
static double  battery1sel=0; //1sel
static double X_set=0;


void flash() {    
  TimerA=TimerA+100;
  flgA=0;
  if(mod_flg==2){
    mod_timer_flg=mod_timer_flg+1;
    if(mod_timer_flg==30){        //3秒間　rv3が-50以上なら　
      mod_flg=3;                  //モード３　AUV　ティーチング再生モード
      Serial.println(mod_flg);
    }
  }else mod_timer_flg=0;
}

void Pwm_Output2(){
  if(RV1<=20 && RV1>=1)m_l=20,m_r=20;
  if(RV1<=40 && RV1>=21)m_l=20,m_r=20;
  if(RV1<=60 && RV1>=41)m_l=20,m_r=20;
  if(RV2<=20 && RV2>=1)m_xl=20,m_xr=20;
  if(RV2<=40 && RV2>=21)m_xl=20,m_xr=20;
  if(RV2<=60 && RV2>=41)m_xl=20,m_xr=20;
  if(RV4<=20 && RV4>=1)m_zl=20,m_zr=20;
  if(RV4<=40 && RV4>=21)m_zl=20,m_zr=20;
  if(RV4<=60 && RV4>=41)m_zl=20,m_zr=20;
  if(RV1<=-20 && RV1>=-1)m_l=20,m_r=20;
  if(RV1<=-40 && RV1>=-21)m_l=20,m_r=20;
  if(RV1<=-60 && RV1>=-41)m_l=20,m_r=20;
  if(RV2<=-20 && RV2>=-1)m_xl=20,m_xr=20;
  if(RV2<=-40 && RV2>=-21)m_xl=20,m_xr=20;
  if(RV2<=-60 && RV2>=-41)m_xl=20,m_xr=20;
  if(RV4<=-20 && RV4>=-1)m_zl=20,m_zr=20;
  if(RV4<=-40 && RV4>=-21)m_zl=20,m_zr=20;
  if(RV4<=-60 && RV4>=-41)m_zl=20,m_zr=20;
  motor_zl.Pwm(m_zl),motor_zr.Pwm(m_zr);
  motor_xl.Pwm(m_xl),motor_xr.Pwm(m_xr);
  motor_l.Pwm(m_l),motor_r.Pwm(m_r);
  //モータPWM最大値設定
}

void setup() {
 attachInterrupt(digitalPinToInterrupt(F1_r_Pin), F1_blink, CHANGE);  //流量計割り込み入力
 attachInterrupt(digitalPinToInterrupt(F2_l_Pin), F2_blink, CHANGE);
 attachInterrupt(digitalPinToInterrupt(F3_zr_Pin), F3_blink, CHANGE);
 attachInterrupt(digitalPinToInterrupt(F4_zl_Pin), F4_blink, CHANGE); 
Serial.begin(230400);
MsTimer2::set(100, flash);  //タイマー割り込み設定
MsTimer2::start();
Motor_init();                //モータ設定
Set_Puropo();                 //プロポ設定
pinMode(swpin, INPUT);        //緊急停止用ボタン
pinMode(midori, OUTPUT);      //テープLED
pinMode(aka, OUTPUT);
pinMode(ao, OUTPUT);
pinMode(ledpin, OUTPUT);      
pinMode(A14, INPUT);          //バッテリー電圧

Set_9D();                     //9軸センサ設定
X_set=Get_9D();               //初期9軸値
Get_Puropo();                 //プロポ入力
}
void F1_blink() {            //割り込みがあったなら
    F1_xr=F1_xr+1;
}
void F2_blink() {
    F2_xl=F2_xl+1;
}
void F3_blink() {
    F3_zr=F3_zr+1;
}
void F4_blink() {
    F4_zl=F4_zl+1;
}
void M1_blink() {
    //M1_r=M1_r+1;
}
void M2_blink() {
    //M2_l=M2_l+1;
}

String serialRead() {         //シリアル通信
  String  str;
  if (Serial.available() > 0) {    //シリアル通信があったら
    str = Serial.readStringUntil(';');    //；までstrに代入
  }
  if(str=="END"){                         //endが送られたら終わり
    Get_Puropo();                         //プロポ入力
    mod_flg=0;                            //モード0　ROVモード
    mod_timer_flg=0;
  }
  return str;
}


void loop(){
  Get_9D();     //9軸センサ値取得
  NTC1=ntc.get(0),NTC2=ntc.get(1),NTC3=ntc.get(2),NTC4=ntc.get(3),NTC5=ntc.get(4),NTC6=ntc.get(5),NTC7=ntc.get(6);    //温度取得
  if(RV3>=-49&& mod_flg!=3){ //rv3   ROVモード
    mod_flg=2;
    Get_Puropo();
  }
  if(RV3<=-50 ){
    mod_flg=1;
    Get_Puropo();
 }
  if(mod_flg==1){           //T
    PS=analogRead(A14); 
    val1_a = analogRead(A8);
    val2_a = analogRead(A9);   
    val3_a = analogRead(A12);   
    val4_a= analogRead(A13); //*5/1024*5
    battery1sel = analogRead(A15); //*5/1024*3
    Get_9D();
    if(RV1 >= 1){
      digitalWrite(42,1); //R 
      digitalWrite(40,1); //L
      MM_R=1,MM_L=1;
    }else{
      RV1 = -RV1;
      digitalWrite(42,0); //R 
      digitalWrite(40,0); //L
      MM_R=0,MM_L=0;
      }
    if(RV2 >= 1){
      digitalWrite(7,0); //R 
      digitalWrite(5,1); //L
       MM_XR=0,MM_XL=1;
    }else{
      RV2 = -RV2;
      digitalWrite(7,1);
      digitalWrite(5,0);
      MM_XR=1,MM_XL=0;
    }
    if(RV4 >= 1){
      RV1=0;
      RV2=0;
      digitalWrite(13,1);
      digitalWrite(11,1);
      MM_ZR=1,MM_ZL=1;
    }else{
      RV4 = -RV4;
      digitalWrite(13,0);
      digitalWrite(11,0);
      MM_ZR=0,MM_ZL=0;
    }
    
    if(RV1>=2){
       digitalWrite(ao,HIGH);
    }else digitalWrite(ao,LOW);
    if(RV2>=2){
       digitalWrite(midori,HIGH);
    }else digitalWrite(midori,LOW);
    if(RV4>=2){
       digitalWrite(aka,HIGH);
    }else digitalWrite(aka,LOW);
    m_l  = RV1,m_r  = RV1;
    m_zl = RV4,m_zr = RV4;
    m_xl = RV2,m_xr = RV2;
    Pwm_Output2();
    float nn=1;
    if(TimerA%100==0 && flgA==0){
      /*
     Serial.print("RV1: ");
    Serial.print(RV1);
    Serial.print(" RV2: ");
    Serial.print(RV2);
    Serial.print(" RV4: ");
    Serial.print(RV4);
    Serial.print(" RV3: ");
    Serial.print(RV3);
    Serial.print(" TimerA: ");
    Serial.println(TimerA);
    */
    /*
    Serial.print("val_PWM1 : ");
    Serial.println(RV1);
    Serial.print("val_PWM2 : ");
    Serial.println(RV2);
    Serial.print("val_PWM3 : ");
    Serial.println(RV3);
    Serial.println("val_PWM4 : ");
    Serial.print("NTC1 : ");
    Serial.println(NTC1);
    Serial.print("NTC2 : ");
    Serial.println(NTC2);
    Serial.print("NTC3 : ");
    Serial.println(NTC3);
    Serial.print("NTC4 : ");
    Serial.println(NTC4);
    Serial.print("NTC5 : ");
    Serial.println(NTC5);
    Serial.print("NTC6 : ");
    Serial.println(NTC6);
    Serial.print("NTC7 : ");
    Serial.println(NTC7);
    */
    /*
    Serial.print("PS : ");
    Serial.println(PS);
    Serial.println(val1_a*5/1024*5);
    Serial.println(val2_a*5/1024*5);
    Serial.println(val3_a*5/1024*5);
    Serial.println(val4_a*5/1024*5);
    Serial.println(battery1sel*5/1024*3-0.7);
    Serial.print(" sin X :" );
    Serial.println(sin(X*PI/180));
    Serial.print(" sin X_set :" );
    Serial.println(X);*/
    
    //Serial.println(buffer_len);
    if(buffer_len>=376 && buffer_len<=410){
      Serial.println(buffer);
    }
    flgA=1;
    }
    root["RM1"] = RM1,root["RM2"] = RM2,root["RM3"] = RM3,  root["RM4"] = RM4,  root["RM5"] = RM5,  root["RM6"] = RM6;
    root["FM1"] = F1_xr, root["FM2"] = F2_xl, root["FM3"] =F3_zr, root["FM4"] = F4_zl;
    root["PS1"] = PS;
    root["NTC1"] = NTC1,root["NTC2"] = NTC2,root["NTC3"] = NTC3,root["NTC4"] = NTC4,root["NTC5"] = NTC5,root["NTC6"] = NTC6,root["NTC7"] = NTC7;
    root["CS1"] = (val1_a*5/1024*5),root["CS2"] = val2_a*5/1024*5,root["CS3"] = val3_a*5/1024*5;
    root["CS4"] = val4_a*5/1024*5,root["CS5"] = CS5,root["CS6"] = CS6;
    root["VS1"] = battery1sel*5/1024*3;
    root["PWM1"] = m_l,root["PWM2"] = m_xl,root["PWM3"] = m_zl,root["PWM4"] = PWM4,root["PWM5"] = PWM5,root["PWM6"] = PWM6;
    root["X9D"] = X,  root["Y9D"] = Y9D,  root["Z9D"] = Z9D;
    root["MM_R"] = MM_R,  root["MM_L"] = MM_L,  root["MM_XR"] = MM_XR,root["MM_XL"] = MM_XL,root["MM_ZR"] = MM_ZR,root["MM_ZL"] = MM_ZL;
    root.printTo(buffer, sizeof(buffer));
    buffer_len=root.measureLength(); //Json 文字数
   // Serial.println(buffer_len);
  }//rv3

 if(mod_flg==3){
String  cmd = serialRead();
  //Serial.println(cmd);
  int s2;
  int s3;
  int len_cmd = 0;
  String M1_r, M2_l, val_M3, val_M4, val_M5, val_M6, s_M1, s_M2, s_M3, s_M4, s_M5, s_M6;
  String val_F1, val_F2, val_F3, val_F4, val_PWM1, val_PWM2, val_PWM3, val_PWM4, val_PWM5, val_PWM6;
  String val_X9D, val_Y9D, val_Z9D;
  String val_MM_R, val_MM_L, val_MM_XR, val_MM_XL, val_MM_ZR, val_MM_ZL;

  String s = cmd;
  len_cmd = cmd.length();

  if (len_cmd >= 656 - 1 && len_cmd <= 700) {
    //Serial.println("受信成功");
    //Serial.println(len_cmd);
    //Serial.println(cmd);
    //s2=cmd.indexOf("M1");

    s = cmd.substring(cmd.indexOf("rM1"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    M1_r = s.substring(s2 + 3, s2 + s3 - 5);


    s = cmd.substring(cmd.indexOf("rM2"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    M2_l = s.substring(s2 + 3, s2 + s3 - 5);
    s = cmd.substring(cmd.indexOf("rM3"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_M3 = s.substring(s2 + 3, s2 + s3 - 5);
    s = cmd.substring(cmd.indexOf("rM4"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_M4 = s.substring(s2 + 3, s2 + s3 - 5);
    s = cmd.substring(cmd.indexOf("rM5"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_M5 = s.substring(s2 + 3, s2 + s3 - 5);
    s = cmd.substring(cmd.indexOf("rM6"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_M6 = s.substring(s2 + 3, s2 + s3 - 5);
    s = cmd.substring(cmd.indexOf("rF1"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_F1 = s.substring(s2 + 3, s2 + s3 - 5);
    s = cmd.substring(cmd.indexOf("rF2"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_F2 = s.substring(s2 + 3, s2 + s3 - 5);
    s = cmd.substring(cmd.indexOf("rF3"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_F3 = s.substring(s2 + 3, s2 + s3 - 5);
    s = cmd.substring(cmd.indexOf("rF4"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_F4 = s.substring(s2 + 3, s2 + s3 - 5);
    s = cmd.substring(cmd.indexOf("PWM1"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_PWM1 = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("PWM2"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_PWM2 = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("PWM3"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_PWM3 = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("PWM4"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_PWM4 = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("PWM5"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_PWM5 = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("PWM6"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_PWM6 = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("X9D"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_X9D = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("Y9D"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_Y9D = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("Z9D"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_Z9D = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("MM_R"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_MM_R = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("MM_L"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_MM_L = s.substring(s2 + 3, s2 + s3 - 6);
    s = cmd.substring(cmd.indexOf("MM_XR"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_MM_XR = s.substring(s2 + 3, s2 + s3 - 7);
    s = cmd.substring(cmd.indexOf("MM_XL"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_MM_XL = s.substring(s2 + 3, s2 + s3 - 7);
    s = cmd.substring(cmd.indexOf("MM_ZR"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_MM_ZR = s.substring(s2 + 3, s2 + s3 - 7);
    s = cmd.substring(cmd.indexOf("MM_ZL"), cmd.length());
    s2 = s.indexOf(",");
    s3 = s.indexOf(")");
    val_MM_ZL = s.substring(s2 + 3, s2 + s3 - 7);




    digitalWrite(42, val_MM_R.toInt()); //R
    digitalWrite(40, val_MM_L.toInt()); //L
    digitalWrite(7, val_MM_XR.toInt()); //R
    digitalWrite(5, val_MM_XL.toInt()); //Lu8
    digitalWrite(13, val_MM_ZR.toInt());
    digitalWrite(11, val_MM_ZL.toInt());

       cnt0 = cnt0 + 1;
    Serial.println(cnt0);
    int cc1=0;
    cc1=val_PWM1.toInt();
    m_l = cc1,m_r =cc1;
    int cc2=0;
    //cc2=val_PWM2.toInt();
    //m_xl = cc2,m_xr =cc2;
    int cc3=0;
    cc3=val_PWM3.toInt();
    m_zl = cc3,m_zr =cc3;
    
   // Serial.println(val_X9D.toInt());
      
    
    Get_9D();
    if((sin(X*PI/180))-(sin(val_X9D.toInt()*PI/180))>0.01){
      digitalWrite(7,1); //R 
      digitalWrite(5,0); //L
      m_xl = 40,m_xr =40;
      RV2 = 40,RV2 =40;
    }else if((sin(X*PI/180))-(sin(val_X9D.toInt()*PI/180))>-0.01){
      digitalWrite(7,0); //R 
      digitalWrite(5,1); //L
      RV2 = 40,RV2 =40;
      m_xl = 40,m_xr =40;
    }
    
    Serial.print( "val_X9D : ");
    Serial.println(val_X9D);
    Serial.print(" X :" );
    Serial.println(X);
    Serial.println((sin(X*PI/180))-(sin(val_X9D.toInt()*PI/180)));
    //delay(1000);
/*
    Serial.print("val_M1 : ");
    Serial.println(val_M1);
    Serial.print("val_M2 : ");
    Serial.println(val_M2);
    Serial.print("val_M3 : ");
    Serial.println(val_M3);
    Serial.print("val_M4 :");
    Serial.println(val_M4);
    Serial.print("val_M5 : ");
    Serial.println(val_M5);
    Serial.print("val_M6 : ");
    Serial.println(val_M6);
    Serial.print("val_F1 : ");
    Serial.println(val_F1);
    Serial.print("val_F2 : ");
    Serial.println(val_F2);
    Serial.print("val_F3 : ");
    Serial.println(val_F3);
    Serial.print("val_F4 :");
    Serial.println(val_F4);
*/
    /*Serial.print("val_PWM1 : ");
    Serial.println(val_PWM1);*/
   
    Serial.print("val_PWM2 : ");
    Serial.println(val_PWM2);
    /*Serial.print("val_PWM3 : ");
    Serial.println(val_PWM3);
    Serial.println("val_PWM4 : ");
    Serial.print("NTC1 : ");
    Serial.println(NTC1);
    Serial.print("NTC2 : ");
    Serial.println(NTC2);
    Serial.print("NTC3 : ");
    Serial.println(NTC3);
    Serial.print("NTC4 : ");
    Serial.println(NTC4);
    Serial.print("NTC5 : ");
    Serial.println(NTC5);
    Serial.print("NTC6 : ");
    Serial.println(NTC6);
    Serial.print("NTC7 : ");
    Serial.println(NTC7);*/
    
    /*
    Serial.print("val_MM_R : ");
    Serial.println(val_MM_R);
    Serial.print("val_MM_L : ");
    Serial.println(val_MM_L);
    Serial.print("val_MM_XR : ");
    Serial.println(val_MM_XR);
    Serial.print("val_MM_XL : ");
    Serial.println(val_MM_XL);
    Serial.print("val_MM_ZR : ");
    Serial.println(val_MM_ZR);
    Serial.print("val_MM_ZL : ");
    Serial.println(val_MM_ZL);
    */

    /*
      Serial.print("val_X9D : ");
      Serial.println(val_X9D);
      Serial.print("val_Y9D : ");
      Serial.println(val_Y9D);
      Serial.print("val_Z9D : ");
      Serial.println(val_Z9D);
    */
 
    Pwm_Output2();
  }
    
  }//rv3
   
  
} //loop end
