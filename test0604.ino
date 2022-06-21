//20210604 測試版本可控制可以顯示電量 原版本為modified0412withbatter.ino
#include "ros.h"
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/UInt16.h>
#include <ros/time.h>

std_msgs::UInt16 str_msg;
ros::Publisher chatter("power", &str_msg);
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

unsigned long currentMillis;
unsigned long previousMillis;
int loopTime = 10;


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
  
  pinMode(22, OUTPUT);     // motor PWM pins
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);     
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);    
  pinMode(29, OUTPUT);
  pinMode(3,OUTPUT);//speed
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  //battery
  pinMode(analogInput, INPUT);
  nh.initNode();
  nh.advertise(chatter);
}

void loop() {

     nh.spinOnce();        // make sure we listen for ROS messages and activate the callback if there is one

     currentMillis = millis();  

     if (currentMillis - previousMillis >= loopTime) {  // start timed loop for everything else
         previousMillis = currentMillis;
         value = analogRead(analogInput);
         vout = (value * 5.0) / 1024.0; // see text
         vin = vout / (R2/(R1+R2));
         percentage = ((vin-11.3)*1000)/13;    
         str_msg.data = percentage;
         chatter.publish( &str_msg );


        // drive motors

        if (demandz!=0 && demandx!=0){
          if(demandz>0.1){
              zpositive();
              delay(1000);
              stopmotor();
              delay(500);
            
          }
          else if(demandz<-0.1){
              znegative();
              delay(1000);
              stopmotor();
              delay(500);
            
          }
          else{
                front();
          }
          
        }
      
      
      else if (demandz==0 && demandx!=0){
            front();
      }

      else if (demandz==0&&demandx==0){
              stopmotor();
      }

      else if (demandz!=0&&demandx==0){
        if(demandz>0.2){
              zpositive();
              delay(1000);
              stopmotor(500);
              delay(500);
        }
        else if (demandz<-0.2){
              znegative();
              delay(1000);
              stopmotor();
              delay(500);
        }
        else{
              stopmotor();
        }
      }
    }   
}

//control function
void front(){
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
void znegative(){
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
void zpositive(){
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
void stopmotor(){
            digitalWrite(22,LOW);
            digitalWrite(23,LOW);
            digitalWrite(26,LOW);
            digitalWrite(27,LOW);
            digitalWrite(24,LOW);
            digitalWrite(25,LOW); 
            digitalWrite(28,LOW);
            digitalWrite(29,LOW);
}

         
