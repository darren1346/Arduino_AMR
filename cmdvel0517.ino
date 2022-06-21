//20210517版本可控制可以顯示電量可以顯示重量
#include "ros.h"
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/UInt16.h>
#include <ros/time.h>
#include "HX711.h"

std_msgs::UInt16 str_msg;
ros::Publisher chatter("power", &str_msg);
ros::Publisher weighta("AreaA",&areaa);
ros::Publisher weightb("AreaB",&areab);
ros::NodeHandle nh;

//cmd_vel data
float demandx;
float demandz;

//power voltage data
int analogInput = A0;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; //  
float R2 = 7500.0; // 
int value = 0;
int percentage;

//weight detect
const int DT_PIN = 6;
const int SCK_PIN = 5;
const int DT_PIN2 = 9;
const int SCK_PIN2 = 10;

unsigned long currentMillis;
unsigned long previousMillis;
int loopTime = 10;

const int scale_factor = 445; //比例參數，從校正程式中取得
const int scale_factor2 = 400;

HX711 scale;
HX711 scale2;

// ** ROS callback & subscriber **

void velCallback(  const geometry_msgs::Twist& vel)
{
     demandx = vel.linear.x;
     demandz = vel.angular.z;

}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel" , velCallback);     //create a subscriber for ROS cmd_vel topic

// ** Setup **
                        
void setup() {  

  nh.initNode();              // init ROS
  nh.subscribe(sub);          // subscribe to cmd_vel
  
  //weight sensor setup
  scale.begin(DT_PIN, SCK_PIN);
  scale2.begin(DT_PIN2 , SCK_PIN2);  
  scale.set_scale(scale_factor);       // 設定比例參數
  scale2.set_scale(scale_factor2);
  scale.tare();               // 歸零
  scale2.tare();  

  //motor setup
  pinMode(22, OUTPUT);     // motor PWM pins
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);     
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);    
  pinMode(29, OUTPUT);
  pinMode(3,OUTPUT);    //speed set
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  
  //advertise battery data on ros
  pinMode(analogInput, INPUT);
  nh.initNode();
  nh.advertise(chatter);
  
  //advertise weight data on ros
  nh.advertise(weighta);
  nh.advertise(weightb);
  
}

void loop() {

     nh.spinOnce();        // make sure we listen for ROS messages and activate the callback if there is one

     currentMillis = millis();  

     if (currentMillis - previousMillis >= loopTime) {  // start timed loop for everything else
         previousMillis = currentMillis;
         value = analogRead(analogInput);
         
         //publish voltage percentage data on ros
         vout = (value * 5.0) / 1024.0; 
         vin = vout / (R2/(R1+R2));
         percentage = ((vin-11.3)*1000)/13;    
         str_msg.data = percentage;
         chatter.publish( &str_msg );

         //publish weight data on ros 
         areaa.data = scale.get_units(10);
         areab.data = scale2.get_units(10);
         weighta.publish( &areaa );
         weightb.publish( &areab );
         scale.power_down();             // 進入睡眠模式
         scale2.power_down();             // 進入睡眠模式
         delay(1000);
         scale.power_up();               // 結束睡眠模式
         scale2.power_up();               // 結束睡眠模式
         
        

        // drive motors
        if (demandz!=0 && demandx!=0){
          if(demandz>0.1){
            digitalWrite(22,HIGH);
            digitalWrite(23,LOW);
            digitalWrite(26,HIGH);
            digitalWrite(27,LOW);
            digitalWrite(24,HIGH);
            digitalWrite(25,LOW); 
            digitalWrite(28,HIGH);
            digitalWrite(29,LOW); 
            analogWrite(3, 150);
            analogWrite(4, 150);
            analogWrite(5, 150);
            analogWrite(6, 60);
            
          }
          else if(demandz<-0.1){
            digitalWrite(22,LOW);
            digitalWrite(23,HIGH);
            digitalWrite(24,LOW);
            digitalWrite(25,HIGH);
            digitalWrite(26,LOW);
            digitalWrite(27,HIGH); 
            digitalWrite(28,LOW);
            digitalWrite(29,HIGH); 
            analogWrite(3, 150);
            analogWrite(4, 150);
            analogWrite(5, 150);
            analogWrite(6, 60);
            
          }
          else{
              digitalWrite(22,LOW);
              digitalWrite(23,HIGH);
              digitalWrite(24,HIGH);
              digitalWrite(25,LOW);
              digitalWrite(26,LOW);
              digitalWrite(27,HIGH); 
              digitalWrite(28,HIGH);
              digitalWrite(29,LOW);
              analogWrite(3, 255);
              analogWrite(4, 255);
              analogWrite(5, 255);
              analogWrite(6, 80);
          }
          
        }
      
      
      else if (demandz==0 && demandx!=0){
            digitalWrite(22,LOW);
            digitalWrite(23,HIGH);
            digitalWrite(24,HIGH);
            digitalWrite(25,LOW);
            digitalWrite(26,LOW);
            digitalWrite(27,HIGH); 
            digitalWrite(28,HIGH);
            digitalWrite(29,LOW);
            analogWrite(3, 255);
            analogWrite(4, 255);
            analogWrite(5, 255);
            analogWrite(6, 80);
      }

      else if (demandz==0&&demandx==0){
            digitalWrite(22,LOW);
            digitalWrite(23,LOW);
            digitalWrite(26,LOW);
            digitalWrite(27,LOW);
            digitalWrite(24,LOW);
            digitalWrite(25,LOW); 
            digitalWrite(28,LOW);
            digitalWrite(29,LOW);
      }

      else if (demandz!=0&&demandx==0){
        if(demandz>0.2){
            digitalWrite(22,HIGH);
            digitalWrite(23,LOW);            
            digitalWrite(24,HIGH);
            digitalWrite(25,LOW);
            digitalWrite(26,HIGH);
            digitalWrite(27,LOW);
            digitalWrite(28,HIGH);
            digitalWrite(29,LOW); 
            analogWrite(3, 150);
            analogWrite(4, 150);
            analogWrite(5, 150);
            analogWrite(6, 60);
        }
        else if (demandz<-0.2){
            digitalWrite(22,LOW);
            digitalWrite(23,HIGH);
            digitalWrite(24,LOW);
            digitalWrite(25,HIGH);
            digitalWrite(26,LOW);
            digitalWrite(27,HIGH); 
            digitalWrite(28,LOW);
            digitalWrite(29,HIGH); 
            analogWrite(3, 150);
            analogWrite(4, 150);
            analogWrite(5, 150);
            analogWrite(6, 60);
        }
        else{
            digitalWrite(22,LOW);
            digitalWrite(23,LOW);
            digitalWrite(26,LOW);
            digitalWrite(27,LOW);
            digitalWrite(24,LOW);
            digitalWrite(25,LOW); 
            digitalWrite(28,LOW);
            digitalWrite(29,LOW);
        }
      }
    }   
}

         
