#include"header.h"

#define LOW_SPEED 0.0
#define HIGH_SPEED 1023.0
#define CENTER_SPEED 512.0
#define MAX_SCALE 3.0/4.0
#define ERROR_GAP  10 

#define ROBOT_STOP 0
#define ROBOT_FORWARD 1
#define ROBOT_REVERSE 2
#define ROBOT_ROTATE_RIGHT 3
#define ROBOT_ROTATE_LEFT 4

unsigned direct = ROBOT_STOP;
unsigned old_direct = ROBOT_STOP;



float scale ;

void setup() {
    pinMode(joySW, INPUT);
    digitalWrite(joySW, HIGH);
    Serial.begin(115200);
    
    
//    float l = 0.0;
//    float m = 512.0;
//    float h = 1023.0;
//    float s = 2.0;
    
//    for(int i = m;i<= h;i++){
//    num = ((s-1.0)/(h-m))*(i-m) + 1.0;
//    Serial.println(num);
//    }


//    for(int i=512;i>=0;i--){
//      num = ((s-1.0)/(m-l))*(m-i) + 1.0; 
//      Serial.println(num); 
//    }
    
    


}

  int pwm = 0;
  int pwml = 0;
  int pwmr = 0;

void loop() {

  
  int pwmy = 0;
  int pwmx = 0;
  int X = analogRead(joyX);
  int Y = analogRead(joyY);
  
  if(Y<=531){
      Y = map(Y,0,531,0,512);
  }else {
      Y = map(Y,532,1016,512,1023);
  }

  if(X<=499){
      X = map(X,0,499,0,512);
  }else {
      X = map(X,500,1016,512,1023);
  }

  X = constrain(X, 0, 1023); 
  Y = constrain(Y, 0, 1023);

  
//  Serial.print(X);
//  Serial.print("\t");
//  Serial.println(Y);

  
//  if((X>510)&&(X<514)&&(Y>510)&&(Y<514)){
//    brakeRobot();
//  }else{
//    if(Y>512){
//        digitalWrite(INR1,HIGH);
//        digitalWrite(INR2,LOW);
//        digitalWrite(INL1,HIGH);
//        digitalWrite(INL2,LOW); 
//
//        pwmy = map(Y,512,1023,0,255);
//    } else if(Y<512){
//        digitalWrite(INR2,HIGH);
//        digitalWrite(INR1,LOW);
//        digitalWrite(INL2,HIGH);
//        digitalWrite(INL1,LOW);
//
//        pwmy = map(Y,512,0,0,255);
//    } 
//
//
//    if(X>520){
//        digitalWrite(INR1,LOW);
//        digitalWrite(INR2,HIGH);
//        digitalWrite(INL1,HIGH);
//        digitalWrite(INL2,LOW); 
//
//        pwmy = map(X,512,1023,0,200);
//    } else if(X<504){
//        digitalWrite(INR1,HIGH);
//        digitalWrite(INR2,LOW);
//        digitalWrite(INL1,LOW);
//        digitalWrite(INL2,HIGH);
//
//        pwmy = map(X,512,0,0,200);
//    }
//
//
//    analogWrite(ENR,pwmy);
//    analogWrite(ENL,pwmy);
//   
//  }

   
   if(Y >= (CENTER_SPEED + ERROR_GAP)){
      scale = ((MAX_SCALE-1.0)/(HIGH_SPEED - CENTER_SPEED))*(Y - CENTER_SPEED) + 1.0;
      direct = ROBOT_FORWARD;
//      digitalWrite(INR1,HIGH);
//      digitalWrite(INR2,LOW);
//      digitalWrite(INL1,HIGH);
//      digitalWrite(INL2,LOW);

      pwm = map(Y,512,1023,0,255);
      
   }else if(Y <= (CENTER_SPEED - ERROR_GAP)){
      scale = ((MAX_SCALE-1.0)/(CENTER_SPEED - LOW_SPEED))*(CENTER_SPEED - Y) + 1.0;
      direct = ROBOT_REVERSE;
//      digitalWrite(INR1,LOW);
//      digitalWrite(INR2,HIGH);
//      digitalWrite(INL1,LOW);
//      digitalWrite(INL2,HIGH);
       
      pwm = map(Y,512,0,0,255);
   }else{
      scale = 0; 
      pwm = 255; 
   }

   if(X >= (CENTER_SPEED + ERROR_GAP)){
      pwml = pwm;
      pwmr = map(X,512,1023,pwm,(pwm-(pwm*scale)));
      if(scale == 0){
        direct = ROBOT_ROTATE_RIGHT;
//        digitalWrite(INR1,LOW);
//        digitalWrite(INR2,HIGH);
//        digitalWrite(INL1,HIGH);
//        digitalWrite(INL2,LOW);  
      }
   }else if(X <= (CENTER_SPEED - ERROR_GAP)){
      pwmr = pwm;
      pwml = map(X,512,0,pwm,(pwm-(pwm*scale)));
      if(scale == 0){
      direct = ROBOT_ROTATE_LEFT;
//      digitalWrite(INR1,HIGH);
//      digitalWrite(INR2,LOW);
//      digitalWrite(INL1,LOW);
//      digitalWrite(INL2,HIGH);  
      }
   }else{
      pwml = pwmr = pwm;
      direct = ROBOT_STOP;     
//      digitalWrite(INR1,HIGH);
//      digitalWrite(INR2,HIGH);
//      digitalWrite(INL1,HIGH);
//      digitalWrite(INL2,HIGH);
   }

    if(direct != old_direct){
          old_direct = direct;
          switch(direct){
            case ROBOT_FORWARD :
                digitalWrite(INR1,HIGH);
                digitalWrite(INR2,LOW);
                digitalWrite(INL1,HIGH);
                digitalWrite(INL2,LOW); 
                break;
            case ROBOT_REVERSE : 
                digitalWrite(INR1,LOW);
                digitalWrite(INR2,HIGH);
                digitalWrite(INL1,LOW);
                digitalWrite(INL2,HIGH);
                break;
            case ROBOT_ROTATE_RIGHT : 
                digitalWrite(INR1,LOW);
                digitalWrite(INR2,HIGH);
                digitalWrite(INL1,HIGH);
                digitalWrite(INL2,LOW);
                break;
            case ROBOT_ROTATE_LEFT :
                digitalWrite(INR1,HIGH);
                digitalWrite(INR2,LOW);
                digitalWrite(INL1,LOW);
                digitalWrite(INL2,HIGH); 
                break;
            case ROBOT_STOP : 
                digitalWrite(INR1,HIGH);
                digitalWrite(INR2,HIGH);
                digitalWrite(INL1,HIGH);
                digitalWrite(INL2,HIGH);
                break;
              
          }
    }
    
    analogWrite(ENR,pwmr);
    analogWrite(ENL,pwml);

   
    
   Serial.print(pwml);
   Serial.print("\t");
   Serial.print(pwmr);
   Serial.print("\t");
   Serial.println(scale);
   delay(30);
   
}
















