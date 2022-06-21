#include "ros.h"
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <ros/time.h>

ros::NodeHandle nh;


float demandx;
float demandz;


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
  //Serial.begin(57600);

}

void loop() {

     nh.spinOnce();        // make sure we listen for ROS messages and activate the callback if there is one

     currentMillis = millis();  

     if (currentMillis - previousMillis >= loopTime) {  // start timed loop for everything else
         previousMillis = currentMillis;

        // drive motors

        if (demandz!=0)
        {
          if(demandz>0.1)
          {
            digitalWrite(22,HIGH);
            digitalWrite(23,LOW);
            digitalWrite(26,HIGH);
            digitalWrite(27,LOW);
            digitalWrite(24,HIGH);
            digitalWrite(25,LOW); 
            digitalWrite(28,HIGH);
            digitalWrite(29,LOW); 
            analogWrite(3, 255);
            analogWrite(4, 255);
            analogWrite(5, 255);
            analogWrite(6, 80);
          }
          else if(demandz<-0.1)
          {
            digitalWrite(22,HIGH);
            digitalWrite(23,LOW);
            digitalWrite(24,LOW);
            digitalWrite(25,HIGH);
            digitalWrite(26,LOW);
            digitalWrite(27,HIGH); 
            digitalWrite(28,LOW);
            digitalWrite(29,HIGH); 
            analogWrite(3, 255);
            analogWrite(4, 255);
            analogWrite(5, 255);
            analogWrite(6, 80);
          }
          else 
          {
            digitalWrite(22,LOW);
            digitalWrite(23,LOW);
            digitalWrite(26,LOW);
            digitalWrite(27,LOW);
            digitalWrite(24,LOW);
            digitalWrite(25,LOW); 
            digitalWrite(28,LOW);
            digitalWrite(29,LOW);
            if (demandx!=0) //前進
            {
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
          
        }
    
        }

     }    
