# -*- coding: utf-8 -*-
import serial
import pymysql.cursors
import datetime
import collections as cl #collections
import time
import signal
import json

ys = cl.OrderedDict()
Select_id = 1
mydict ={}
cnt_id=1
cnt_task=2

i=1
n=1


task_flg=0
connection = pymysql.connect(host='localhost',
                             user='root',
                             password='password',
                             db='test1db',
                             charset='utf8',
                             cursorclass=pymysql.cursors.DictCursor)

#--------------------------------------------------------------# date base id chak
with connection.cursor() as cursor:
    sql = 'SELECT MAX(id) FROM date_and_time '
    r=cursor.execute(sql)
    max_id = cursor.fetchall()
    my_max_id=""
    #print(r)
    #print(max_id[0]['MAX(id)'])
    db_id_max=max_id[0]['MAX(id)']        ###
    #print(db_id_max)
connection.commit()
print("DB_id_ max_To take_OK")

#---------------------------------------------------------------#
with connection.cursor() as cursor:
    sql = 'SELECT MAX(id) FROM log_meter'+str(db_id_max)
    r=cursor.execute(sql)
    max_id = cursor.fetchall()
    #print(r)
    #print(max_id[0]['MAX(id)'])
    db_data_id_max=max_id[0]['MAX(id)']        ###
    print(db_data_id_max)
connection.commit()
#---------------------------------------------------------------#

#///////////////////////////////////////////////////////////////////////////////#


with connection.cursor() as cursor:
    sql = 'SELECT id,M1,M2,M3,M4,M5,M6,F1,F2,F3,F4,PS1,T1,T2,T3,T4,T5,T6,T7,C1,C2,C3,C4,C5,C6,V1,\
        PWM1,PWM2,PWM3,PWM4,PWM5,PWM6,9DX,9DY,9DZ,MM_R,MM_L,MM_XR,MM_XL ,MM_ZR,MM_ZL FROM log_meter'+str(db_id_max)
    r=cursor.execute(sql)
    results = cursor.fetchall()
    print(r)                #itibu
   #print(results) //zennbu


    for r in results:
        now = datetime.datetime.now()
        ys[cnt_id] = cl.OrderedDict({"rM1": r["M1"],"rM2":r["M2"],"rM3":r["M3"],"rM4":r["M4"],"rM5":r["M5"],"rM6":r["M6"],
                                     "rF1":r["F1"],"rF2":r["F2"],"rF3":r["F3"],"rF4":r["F4"],"PS1":r["PS1"],"NTC1":r["T1"],"NTC2":r["T2"],"NTC3":r["T3"],
                                  "NTC4":r["T4"],"NTC5":r["T5"],"NTC6":r["T6"],"NTC7":r["T7"],
                                  "CS1":r["C1"], "CS2":r["C2"], "CS3":r["C3"], "CS4":r["C4"], "CS5":r["C5"], "CS6":r["C6"],
                                  "VS1":r["V1"], "PWM1":r["PWM1"],"PWM2": r["PWM2"], "PWM3":r["PWM3"],"PWM4": r["PWM4"],
                                  "PWM5":r["PWM5"], "PWM6":r["PWM6"], "X9D":r["9DX"], "9DY":r["9DY"], "Z9D":r["9DZ"],
                                  "MM_R":r["MM_R"], "MM_L":r["MM_L"], "MM_XR":r["MM_XR"], "MM_XL":r["MM_XL"], "MM_ZR":r["MM_ZR"],
                                  "MM_ZL":r["MM_ZL"], "now":now})
        print(cnt_id)
        #print(results)
        #print("PWM1",r["PWM1"]) #DB data
        cnt_id=cnt_id+1
connection.commit()


def task(arg1, arg2):
    global task_flg
    task_flg=0
    #print("set_time : ",time.time())
    
    pass

signal.signal(signal.SIGALRM, task)
signal.setitimer(signal.ITIMER_REAL, 0.1, 0.1)


with serial.Serial('/dev/ttyACM0',230400) as ser:
    while 1:
        try:
            global task_flg
            if(task_flg==0) :
                mystr=bytes(str(ys[n])+";",'utf-8')
                #mystr=bytes(str("{PWM2:22}")+";",'utf-8')
                #print(mystr)
                ser.write(mystr)
                #time.sleep(0.1)
            
                print("PWM1 : ",ys[n]["PWM1"] )
                print("PWM2 : ",ys[n]["PWM2"] )
                print("PWM3 : ",ys[n]["PWM3"] )
                print("X9D : ",ys[n]["X9D"] )
                print("set_time : ",time.time())
                print("cnt : ",n)
                #print(cnt_task)
                print(db_data_id_max)
                if(n>=db_data_id_max):
                    mystr=bytes("END"+";",'utf-8')
                    ser.write(mystr)
                    break
            
                n=n+1
                task_flg=1
        except KeyboardInterrupt:
            mystr=bytes("END"+";",'utf-8')
            ser.write(mystr)
            break
                
        
