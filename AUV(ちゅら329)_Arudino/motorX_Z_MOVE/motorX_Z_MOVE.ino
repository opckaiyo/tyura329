#include <SetUp.h>
static int midori = 41;
static int aka = 39;
static int ao = 37;
void setup(void) {
  Motor_init();
  isr_setup();
  MsTimer2::set(100, timerFire);

  motorZ_init_pwm = 0;
  motorX_init_pwm = 20;
  motor_init_pwm = 40;

  pinMode(swpin, INPUT);
    pinMode(midori, OUTPUT);
  pinMode(aka, OUTPUT);
  pinMode(ao, OUTPUT);
}

int cnt = 0;

//huzyou
long Emerge = 340;
//umi 360
//moguru
long Dive = 470;
//umi 440

/*
long suim1 = 200;
long dive1 = 750;
long suim2 = 800;
long suim3 = 850;
long dive2 = 1350;
long suim4 = 1600;
*/


long suim1 = 50;
long dive1 = 100;
long suim2 = 150;
long suim3 = 200;
long dive2 = 250;
long suim4 = 300;

int divemax = 30;
int divecnt = 0;
void timerFire() {
  if(digitalRead(swpin) == 1){
    //Serial.p2rintln(time100ms);
    if(!Turning)  time100ms++;
    if((time100ms >= suim1 && time100ms <= dive1 && divecnt == 0)||(time100ms >= suim3 && time100ms <= dive2 && divecnt == 1)){
      //Serial.print("潜水開始");
      Diving = true;
    }else Diving = false;
    if(time100ms >= suim2 && !Turning && !Return){
      //Serial.print("旋回開始");
      Turning = true;
      divecnt = 1;
    }if(time100ms >= suim4) Stop();
  } 
}

void motor(){
  motor_l.High(),motor_r.High();
  m_l = motor_init_pwm;
  m_r = motor_init_pwm;
}

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

  if(m_zr >= divemax)  m_zr = divemax;
  else if(m_zr <= 0)   m_zr = 0;
  if(m_zl >= divemax)  m_zl = divemax;
  else if(m_zl <= 0)   m_zl = 0;
}

void motorX(){
  DataX = X;
  if(!Return && DataX > 180) DataX = int(X) - 360;
  else if(Return) DataX = int(X) - 180;

  //左に傾く
  if(DataX <= -1){
    //Serial.println("左に傾き");
    motor_xl.High(),motor_xr.Low();
    m_xr = motorX_init_pwm - DataX;
    m_xl = motorX_init_pwm - DataX;
    if(!Diving){
      digitalWrite(midori, HIGH);
      digitalWrite(ao, HIGH);
      digitalWrite(aka, HIGH);
    }else{
      digitalWrite(midori, HIGH);
      digitalWrite(ao, HIGH);
      digitalWrite(aka, HIGH);
    }
  //右に傾く
  }else if(DataX >= 1){
    //Serial.println("右に傾き");
    motor_xl.Low(),motor_xr.High();
    m_xr = motorX_init_pwm + DataX;
    m_xl = motorX_init_pwm + DataX;
    if(!Diving){
      digitalWrite(midori, HIGH);
      digitalWrite(ao, HIGH);
      digitalWrite(aka, HIGH);
    }else{
      digitalWrite(midori, HIGH);
      digitalWrite(ao, HIGH);
      digitalWrite(aka, HIGH);
    }
  }else{
    if(!Diving){
      digitalWrite(midori, HIGH);
      digitalWrite(ao, LOW);
      digitalWrite(aka, LOW);
    }else{
      digitalWrite(midori, LOW);
      digitalWrite(ao, HIGH);
      digitalWrite(aka, LOW);
    }
    m_xr = 0;
    m_xl = 0;
  }

  if(m_xr >= 40)  m_xr = 40;
  else if(m_xr <= 0)   m_xr = 0;
  if(m_xl >= 40)  m_xl = 40;
  else if(m_xl <= 0)   m_xl = 0;
}

int turnvalu = 0;
int turnled = 0;

void Turn(){

  digitalWrite(midori, LOW);
  digitalWrite(ao, HIGH);
  digitalWrite(aka, HIGH);
   motor_xl.High(),motor_xr.Low();
   motor_l.High(),motor_r.Low();

  if(!Return && X <= 180) turnvalu = 180 - X;
  else if(!Return && X >= 180)  turnvalu = 40;
  else if(Return)  turnvalu = 360 - X; 
  
   m_xr = 40;
   m_xl = 40;
   //m_r = 0;
   //m_l = 0;
   m_r = 40;
   m_l = 40;
   m_zr = 0;
   m_zl = 0;

  if(!Return && X >= 177 && X <= 183){
    Turning = false;
    Return = true;
    m_xr = 0;
   m_xl = 0;
   m_r = 0;
   m_l = 0;
   m_zr = 0;
   m_zl = 0;
  }
  
  if(m_xr >= 40)  m_xr = 40;
  else if(m_xr <= 0)   m_xr = 0;
  if(m_xl >= 40)  m_xl = 40;
  else if(m_xl <= 0)   m_xl = 0;
  
  if(m_r >= 40)  m_r = 40;
  else if(m_r <= 0)   m_r = 0;
  if(m_l >= 40)  m_l = 40;
  else if(m_l <= 0)   m_l = 0;
}

void loop(void) {
    sei();
    LED_OFF();
    digitalWrite(midori, LOW);
    digitalWrite(ao, LOW);
    digitalWrite(aka, HIGH); 
    if(digitalRead(swpin) == 1){
        LED_ON();
        if(!cnt){
            for(int i = 25; i > 0; i--){
                digitalWrite(aka, HIGH); 
                for(int ii = 0; ii  <= i; ii++) delay(10);
                digitalWrite(aka, LOW);
                for(int ii = 0; ii  <= i; ii++) delay(10);
            }
            //start
            digitalWrite(midori, HIGH);
            digitalWrite(aka, HIGH);
            digitalWrite(ao, HIGH);
            Set_9D();
            digitalWrite(midori, HIGH);
            digitalWrite(aka, LOW);
            digitalWrite(ao, LOW);
            MsTimer2::start();
            cnt = true;
          }
    }
    while(cnt){
        if(digitalRead(swpin) == 1 && time100ms <= suim4){
            Get_9D();
            if(!Turning){
                motorZ();
                motorX();
                //if((!Diving && !DivingChack) || (Diving && DivingChack))motor();
                motor();
                //Serial.print(Rps[0]);
            }else{
                Turn();
            }
            Pwm_Output();
        }else{
            Stop();
            if(digitalRead(swpin) == 1){
                digitalWrite(midori, HIGH);
                digitalWrite(ao, LOW);
                digitalWrite(aka, HIGH); 
            }else{
                digitalWrite(midori, LOW);
                digitalWrite(ao, LOW);
                digitalWrite(aka, HIGH); 
            }
        }
    }
}
