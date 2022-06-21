#include "ros.h"//超聲波測距 on ROS
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/UInt16.h>
#include <ros/time.h>

std_msgs::UInt16 distance;
ros::Publisher detect("detect", &distance);
ros::NodeHandle nh;

int trigPin = 12;                  
int echoPin = 11;                  
long duration, cm;
unsigned long currentMillis;
unsigned long previousMillis;
int loopTime = 10;

void setup() {
  nh.initNode();
  Serial.begin (9600);             
  pinMode(trigPin, OUTPUT);         
  pinMode(echoPin, INPUT);
  nh.initNode();
  nh.advertise(detect);
}
 
void loop()
{
  nh.spinOnce();        
  currentMillis = millis();
  if (currentMillis - previousMillis >= loopTime) {  
    previousMillis = currentMillis;  
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);     
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  
    pinMode(echoPin, INPUT);             
    duration = pulseIn(echoPin, HIGH);   
    cm = (duration/2) / 29.1;           
    distance.data = cm;
    detect.publish( &distance );    
    delay(100);
  }
}
