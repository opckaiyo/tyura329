#ifndef Serial_h
#define Serial_h
#include <Wire.h>

static int Rn=0;

static int RM1,RM2,RM3,RM4,RM5,RM6=0;
static int FM1,FM2,FM3,FM4=0;
static float PS=0;
static int PWM1,PWM2,PWM3,PWM4,PWM5,PWM6=0;
static float CS1,CS2,CS3,CS4=0,CS5=0,CS6=0;
static int NTC1,NTC2,NTC3,NTC4,NTC5,NTC6,NTC7=0;
static float VS1=0;
static float X9D,Y9D,Z9D = 1;

static String S_RM= "";
static String S_FM="";
static String S_PS ="";
static String S_NTC ="";
static String S_CS="";
static String S_CS2="";
static String S_VS ="";
static String S_PWM ="";
static String S_9D ="";

#endif
