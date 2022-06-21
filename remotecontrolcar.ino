#include <PPMReader.h>//沒for版本 單純控制沒有ROS
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
  Serial.begin(9600);
}
void loop() {
    if (k==0){
      delay(2000);
      k = 1;
    }
    
    // Print latest valid values from all channels
        int value1 = ppm.latestValidChannelValue(1, 0);//左右
        int value2 = ppm.latestValidChannelValue(2, 0);//前後
        Serial.println(value1);
          if(value1>1550){
            //speeds = 100+((value1-1500)/3);
            analogWrite(speed1,255);
            analogWrite(speed2,255);
            analogWrite(speed3,255);
            analogWrite(speed4,80);
            //Serial.println("Right");
            mright();
            delay(300);
            mstop();
            delay(1);
          }
          if(value1<1400){
            //Serial.println("Left");
            analogWrite(speed1,255);
            analogWrite(speed2,255);
            analogWrite(speed3,255);
            analogWrite(speed4,80);
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

 
