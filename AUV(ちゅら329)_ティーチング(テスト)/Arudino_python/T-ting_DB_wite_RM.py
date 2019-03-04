# -*- coding: utf-8 -*-
import serial
import pymysql.cursors
import datetime
import collections as cl #collections
import time
import signal
import json
import RPi.GPIO as GPIO

ys = cl.OrderedDict()

id_data= 0;
time_flg=0
max_id_data=0
GPIO.setmode(GPIO.BCM)
pin = 17
pin2 = 22
cnt_l=0
cnt_r=0

def callBackTest(channel):
    global cnt_l
    cnt_l=cnt_l+1
    print("cnt_l",cnt_l)

def callBackTest2(channel):
    global cnt_r
    cnt_r=cnt_r+1
    print("cnt_l",cnt_r)

def task(arg1, arg2):
    time_flg=1
    #print(time.time())
    
GPIO.setup(pin, GPIO.IN, GPIO.PUD_UP)
GPIO.add_event_detect(pin, GPIO.FALLING, callback=callBackTest, bouncetime=1) 
GPIO.setup(pin2, GPIO.IN, GPIO.PUD_UP)
GPIO.add_event_detect(pin2, GPIO.FALLING, callback=callBackTest2, bouncetime=1) 
    



signal.signal(signal.SIGALRM, task)
signal.setitimer(signal.ITIMER_REAL, 0.1, 0.1)

connection = pymysql.connect(host='localhost',
                             user='root',
                             password='password',
                             db='test1db',
                             charset='utf8',             
                             cursorclass=pymysql.cursors.DictCursor)
 
ser = serial.Serial('/dev/ttyACM0',230400,timeout=None)

#============================# date base id + 1
sql = "INSERT INTO date_and_time (dataTime,memo)\
            VALUES (%s,%s)"
with connection.cursor() as cursor:
    now = datetime.datetime.now()
    memo="test2"
    r = cursor.execute(sql, (now,memo))
    connection.commit()
print(now)
print("DB_id_increment OK")
#============================#

#--------------------------------------------------------------# date base max id chak
with connection.cursor() as cursor:
    sql = 'SELECT MAX(id) FROM date_and_time '
    r=cursor.execute(sql)
    max_id = cursor.fetchall()
    #print(max_id[0])
    my_max_id=""
    #print(r)
    #print(max_id[0]['MAX(id)'])
    db_id_max=max_id[0]['MAX(id)']        ###
    #print(db_id_max)
connection.commit()
print("DB_id_ max_To take_OK")
#---------------------------------------------------------------#

make_table="DROP TABLE IF EXISTS log_meter"+str(db_id_max)
print(db_id_max)

#///////////////////////////////////////////////////////////////////////////////# make table

with connection.cursor() as cursor:
    r=cursor.execute("DROP TABLE IF EXISTS log_meter"+str(db_id_max))
    print(r)
    sql = "CREATE TABLE log_meter"+str(db_id_max)+"(\
                        id INT(11) PRIMARY KEY AUTO_INCREMENT,\
                        M1 varchar(255) DEFAULT NULL,M2 varchar(255) DEFAULT NULL,M3 varchar(255) DEFAULT NULL,M4 varchar(255) DEFAULT NULL,M5 varchar(255) DEFAULT NULL,M6 varchar(255) DEFAULT NULL,\
                        F1 varchar(255) DEFAULT NULL,F2 varchar(255) DEFAULT NULL,F3 varchar(255) DEFAULT NULL,F4 varchar(255) DEFAULT NULL,\
                        PS1 varchar(255) DEFAULT NULL,\
                        T1 varchar(255) DEFAULT NULL,T2 varchar(255) DEFAULT NULL,T3 varchar(255) DEFAULT NULL,\
                        T4 varchar(255) DEFAULT NULL,T5 varchar(255) DEFAULT NULL,T6 varchar(255) DEFAULT NULL,\
                        T7 varchar(255) DEFAULT NULL,\
                        C1 varchar(255) DEFAULT NULL,C2 varchar(255) DEFAULT NULL,C3 varchar(255) DEFAULT NULL,\
                        C4 varchar(255) DEFAULT NULL,C5 varchar(255) DEFAULT NULL,C6 varchar(255) DEFAULT NULL,\
                         V1 varchar(255) DEFAULT NULL,\
                         PWM1 varchar(255) DEFAULT NULL,PWM2 varchar(255) DEFAULT NULL,PWM3 varchar(255) DEFAULT NULL,PWM4 varchar(255) DEFAULT NULL,\
                         PWM5 varchar(255) DEFAULT NULL,PWM6 varchar(255) DEFAULT NULL,\
                         9DX varchar(255) DEFAULT NULL,9DY varchar(255) DEFAULT NULL,9DZ varchar(255) DEFAULT NULL,\
                         MM_R varchar(255) DEFAULT NULL,MM_L varchar(255) DEFAULT NULL,MM_XR varchar(255) DEFAULT NULL,\
                         MM_XL varchar(255) DEFAULT NULL,MM_ZR varchar(255) DEFAULT NULL,MM_ZL varchar(255) DEFAULT NULL,\
                        dataTime varchar(255)  DEFAULT NULL)"
    r=cursor.execute(sql)
    print(r)
connection.commit()
print("DB_table_set_OK")
#///////////////////////////////////////////////////////////////////////////////#
    

while 1:
    try:
            log_data = ser.readline()
            log_len=len(log_data)
            #print(log_data)
            #print(log_len)
    except KeyboardInterrupt:
        print("exid")
        max_id_data=id_data-2
        print("max_id_data : ",max_id_data)
        print("break")
        GPIO.cleanup()
        #################################################################
        #DB insart
        for j in range(max_id_data):
            print("PWM1: ",ys[j]["PWM1"])
            #print(j)
            try:
                sql = "INSERT INTO log_meter"+str(db_id_max)+"(M1,M2,M3,M4,M5,M6,F1,F2,F3,F4,PS1,T1,T2,T3,T4,T5,T6,T7,\
                            C1,C2,C3,C4,C5,C6,V1,PWM1,PWM2,PWM3,PWM4,PWM5,PWM6,9DX,9DY,9DZ,MM_R,MM_L,MM_XR,MM_XL,MM_ZR,MM_ZL,dataTime)\
                            VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\
                            %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"
                with connection.cursor() as cursor:
                    now = datetime.datetime.now()
                    #now = "0"
                    
                    r = cursor.execute(sql, (ys[j]["RM1"],ys[j]["RM2"],ys[j]["RM3"],ys[j]["RM4"],ys[j]["RM5"],ys[j]["RM6"],
                                             ys[j]["FM1"],ys[j]["FM2"],ys[j]["FM3"],ys[j]["FM4"],ys[j]["PS1"],ys[j]["NTC1"],ys[j]["NTC2"],ys[j]["NTC3"],ys[j]["NTC4"],ys[j]["NTC5"],ys[j]["NTC6"],ys[j]["NTC7"],
                                             ys[j]["CS1"],ys[j]["CS2"],ys[j]["CS3"],ys[j]["CS4"],ys[j]["CS5"],ys[j]["CS6"],ys[j]["VS1"],
                                             ys[j]["PWM1"], ys[j]["PWM2"],ys[j]["PWM3"],ys[j]["PWM4"],ys[j]["PWM5"],ys[j]["PWM6"], ys[j]["X9D"], ys[j]["Y9D"], ys[j]["Z9D"],
                                             ys[j]["MM_R"], ys[j]["MM_L"], ys[j]["MM_XR"], ys[j]["MM_XL"], ys[j]["MM_ZR"], ys[j]["MM_ZL"], now))
                                             
                    
                    connection.commit()
            except Exception as e:
                print("DB error")
                print(e)
        
        #################################################################
        break

    try:
        log_data = log_data.decode("UTF-8")
        if(log_len>=375 and log_len<=400 ):
            print("len_ok")
            global json_log
            json_log = json.loads(log_data)
            #print('R : ' ,json_log['MM_R'])
            ys[id_data] = cl.OrderedDict({"RM1":cnt_r,"RM2":cnt_l,"RM3":json_log['RM3'],"RM4":json_log['RM4'],"RM5":json_log['RM5'],"RM6":json_log['RM6'],
                                  "FM1":json_log['FM1'],"FM2":json_log['FM2'],"FM3":json_log['FM3'],"FM4":json_log['FM4'],
                                  "PS1":json_log['PS1'],"NTC1":json_log['NTC1'],"NTC2":json_log['NTC2'],"NTC3":json_log['NTC3'],
                                  "NTC4":json_log['NTC4'],"NTC5":json_log['NTC5'],"NTC6":json_log['NTC6'],"NTC7":json_log['NTC7'],
                                  "CS1":json_log['CS1'], "CS2":json_log['CS2'], "CS3":json_log['CS3'], "CS4":json_log['CS4'], "CS5":json_log['CS5'], "CS6":json_log['CS6'],
                                  "VS1":json_log['VS1'], "PWM1":json_log['PWM1'],"PWM2": json_log['PWM2'], "PWM3":json_log['PWM3'],"PWM4": json_log['PWM4'],
                                  "PWM5":json_log['PWM5'], "PWM6":json_log['PWM6'], "X9D":json_log['X9D'], "Y9D":json_log['Y9D'], "Z9D":json_log['Z9D'],
                                  "MM_R":json_log['MM_R'], "MM_L":json_log['MM_L'], "MM_XR":json_log['MM_XR'], "MM_XL":json_log['MM_XL'], "MM_ZR":json_log['MM_ZR'],
                                  "MM_ZL":json_log['MM_ZL'], "now":now})
            #print(ys[id_data]["PWM1"])
           
            print("cnt : id_data : ",id_data)
            print("PWM1: ",ys[id_data]["PWM1"])
            print("PWM2 : ",ys[id_data]["PWM2"])
            print("PWM3 : ",ys[id_data]["PWM3"])
            print("MM_R : ",ys[id_data]["MM_R"])
            print("MM_L : ",ys[id_data]["MM_L"])
            print("MM_XR : ",ys[id_data]["MM_XR"])
            print("MM_XL : ",ys[id_data]["MM_XL"])
            print("MM_ZR : ",ys[id_data]["MM_ZR"])
            print("MM_ZL : ",ys[id_data]["MM_ZL"])
            print("X9D    : ",ys[id_data]["X9D"])
            print("X9D2 : ",ys[id_data]["Y9D"])
            print("cnt_r ",cnt_r)
            print("cnt_l ",cnt_l)
            
            id_data=id_data+1
        else:
            print("json nasi")
        #print(json_log)
    except:
        print("json_log_conversion_error")
        now = datetime.datetime.now()

    #ys[id_data] = cl.OrderedDict({"RM1": json_log['RM1'] })
    #print("RM1 : ",ys[id_data]["RM1"])
    #print(json_log['RM1'])

   
    #print(json_log)

    #time.sleep(1)
