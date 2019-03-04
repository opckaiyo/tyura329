#ifndef SetUp_h
#define SetUp_h

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <pcint_int.h>
#include <motor.h> 
#include <ntc.h>
#include <MsTimer2.h>
#include <Arduino.h>
#include <ntc.h>
#include <Serial.h>

ntc ntc("SETUP");

//9Dコンパスセット
Adafruit_BNO055 bno = Adafruit_BNO055(55);

//serial通信
static String S_ALLDATA="";

//
static int kaitensu = 0;

//puropo
int rcv1 = 47; //30
int rcv2 = 43; //26
int rcv4 = 49; //32
int RV1 = 0;
int RV2 = 0;
int RV4 = 0;

//格モータPWM格納
static int m_zr = 0;
static int m_zl = 0;
static int m_xr = 0;
static int m_xl = 0;
static int m_r = 0;
static int m_l = 0;
static int DataZ;
static int DataX;

//格モータの初期PWM値
static int motorZ_init_pwm = 0;
static int motorX_init_pwm = 30;
static int motor_init_pwm = 10;

//9軸センサグローバル変数
static float Z;
static float X;
static float Y;

//testLEDpin
int ledpin = 25;

//testSW
int swpin = 23;

//aturyoku
long aturyoku = 0;

//Z潜水・バランス用モータ制御部
motor motor_zr(13,12);  //Ald:D:13 Ald:P:12  Mdd:D:24 Mdd:P:13
motor motor_zl(11,8);   //Ald:D:11 Ald:P:8  Mdd:D:26 Mdd:P:12

//X方向転換用モータ制御部
//X9軸センサの左右の動き
motor motor_xr(7,6);    //Ald:D:7 Ald:P:6  Mdd:D:24 Mdd:P:13
motor motor_xl(5,4);    //Ald:D:5 Ald:P:4  Mdd:D:26 Mdd:P:12

//推進用モータ制御部
motor motor_r(42,46);   //Ald:D:42 Ald:P:46  Mdd:D:24 Mdd:P:13
motor motor_l(40,44);   //Ald:D:40 Ald:P:44  Mdd:D:26 Mdd:P:12

//Z潜水中はTrue
static bool Diving = false;
//Z潜水時のモータの回転数UP
static int DivingPlus = 0;

//X旋回中はTrue
static bool Turning = false;
//bool Turning = true;
//X復路走行中はTrue
//static bool Return = true;
static bool Return = false;

//プールテスト時のタイミング
static int time100ms = 0;

LED_ON(){
	digitalWrite(ledpin, HIGH);
}

LED_OFF(){
	digitalWrite(ledpin, LOW);
}

Set_9D(){
  Serial.begin(115200);
  Serial.print("9DConnection : ");
  if(!bno.begin()){
    Serial.println("Failure");
    while(1);
  }
  Serial.println("Success");
  delay(100);
  bno.setExtCrystalUse(true);
}

Get_9D(){
  sensors_event_t event; 
  bno.getEvent(&event);
  X = event.orientation.x;
  Y = event.orientation.y;
  Z = event.orientation.z;	
}

int puropo(int RV){
  if(RV >= 1515){
    if(RV >= 1565) RV = map(RV, 1565, 1920, 0, 60);
    else RV = 0;
  }else{
    if(RV <= 1465) RV = map(1465 - RV, 0, 370, 0, -60);
    else RV = 0;
  }
  return RV;
}

Set_Puropo(){
  pinMode(rcv1,INPUT);
  pinMode(rcv2,INPUT);
  pinMode(rcv4,INPUT); 
}

Get_Puropo(){
  RV1 = pulseIn(rcv1,HIGH); // PulseがHIGHになったら計測開始
  RV2 = pulseIn(rcv2,HIGH); 
  RV4 = pulseIn(rcv4,HIGH); 

  RV1 = puropo(RV1);
  RV2 = puropo(RV2);
  RV4 = puropo(RV4);
}

Motor_init(){
  //motor_init_set
  motor_zl.High(),motor_zr.High();
  motor_xl.High(),motor_xr.High();
  motor_l.High(),motor_r.High();
}

//ストップ
Stop(){
  motor_zl.Pwm(0),motor_zr.Pwm(0);
  motor_xl.Pwm(0),motor_xr.Pwm(0);
  motor_l.Pwm(0),motor_r.Pwm(0);
}

//pwmin
Pwm_Output(){
  motor_zl.Pwm(m_zl),motor_zr.Pwm(m_zr);
  motor_xl.Pwm(m_xl),motor_xr.Pwm(m_xr);
  motor_l.Pwm(m_l),motor_r.Pwm(m_r);
}

Rpms_set(int pwm){
  kaitensu = map(pwm, 0, 100, 0, 30);
}

#endif
