#include "ros.h"
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/UInt16.h>
#include <ros/time.h>
#include <PPMReader.h>//沒for版本

std_msgs::UInt16 str_msg;
ros::Publisher chatter("power", &str_msg);
ros::NodeHandle nh;

int analogInput = A0;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; //  
float R2 = 7500.0; // 
int value = 0;
int percentage;

unsigned long currentMillis;
unsigned long previousMillis;
int loopTime = 10;

int interruptPin = 2;
int channelAmount = 6;
int speed1 = 3;
int speed2 = 4;
int speed3 = 5;
int speed4 = 6;
int speeds;
int k = 0 ;
//馬達 LN34 = 左前  56 = 右後
const int In1 = 22;
const int In2 = 23;
const int In3 = 24;      
const int In4 = 25; 
const int In5 = 26;
const int In6 = 27;
const int In7 = 28;      
const int In8 = 29; 
PPMReader ppm(interruptPin, channelAmount);
void setup() {
  nh.initNode();              // init ROS
  nh.subscribe(sub);          // subscribe to cmd_vel  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(In5, OUTPUT);
  pinMode(In6, OUTPUT);
  pinMode(In7, OUTPUT);
  pinMode(In8, OUTPUT);
  pinMode(speed1, OUTPUT);
  pinMode(speed2, OUTPUT);
  pinMode(speed3, OUTPUT);
  pinMode(speed4, OUTPUT);   
  //battery
  pinMode(analogInput, INPUT);
  nh.initNode();
  nh.advertise(chatter);
}
void loop() {
    if (k==0){
      delay(2000);
      k = 1;
    }
     nh.spinOnce();
     currentMillis = millis(); 
     if (currentMillis - previousMillis >= loopTime) {
         previousMillis = currentMillis;
         value = analogRead(analogInput);
         vout = (value * 5.0) / 1024.0; // see text
         vin = vout / (R2/(R1+R2));
         percentage = ((vin-11.3)*1000)/13;    
         str_msg.data = percentage;
         chatter.publish( &str_msg );                
     
    // Print latest valid values from all channels
        int value1 = ppm.latestValidChannelValue(1, 0);//左右
        int value2 = ppm.latestValidChannelValue(2, 0);//前後
        Serial.println(value1);
          if(value1>1550){
            //speeds = 100+((value1-1500)/3);
            analogWrite(speed1,150);
            analogWrite(speed2,150);
            analogWrite(speed3,150);
            analogWrite(speed4,150);
            //Serial.println("Right");
            mright();
            delay(300);
            mstop();
            delay(1);
          }
          if(value1<1400){
            //Serial.println("Left");
            analogWrite(speed1,150);
            analogWrite(speed2,150);
            analogWrite(speed3,150);
            analogWrite(speed4,150);
            mleft();
            delay(300);
            mstop();
            delay(1);
          }


          if(value2>1550){                  //前後
            //speeds = 105+((value2-1550)/3);
            analogWrite(speed1,255);
            analogWrite(speed2,255);
            analogWrite(speed3,255);
            analogWrite(speed4,80);
            //Serial.println("Frontspeed: ");
            mfront();
            delay(500);
            mstop();
            delay(1);
          }

          if(value2<1400){
            //Serial.print("Back");
            //speeds = 110+((1440-value2)/3);
            //Serial.println("Backspeed:");
            analogWrite(speed1,255);
            analogWrite(speed2,255);
            analogWrite(speed3,255);
            analogWrite(speed4,80);
            mback();
            delay(500);
            mstop();
            delay(1);
          }
     }
          
}
void mstop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  digitalWrite(In5, LOW);
  digitalWrite(In6, LOW);
  digitalWrite(In7, LOW);
  digitalWrite(In8, LOW);
}
void mfront(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  digitalWrite(In5, LOW);
  digitalWrite(In6, HIGH);
  digitalWrite(In7, HIGH);
  digitalWrite(In8, LOW);
}
void mback(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In5, HIGH);
  digitalWrite(In6, LOW);
  digitalWrite(In7, LOW);
  digitalWrite(In8, HIGH);
}
void mright(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In5,LOW);
  digitalWrite(In6, HIGH);
  digitalWrite(In7, LOW);
  digitalWrite(In8, HIGH);
}
void mleft(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  digitalWrite(In5, HIGH);
  digitalWrite(In6, LOW);
  digitalWrite(In7, HIGH);
  digitalWrite(In8, LOW);
}

 
