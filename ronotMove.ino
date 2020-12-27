
void fowardRobot(int spd){
  
    digitalWrite(INR1,HIGH);
    digitalWrite(INR2,LOW);
    digitalWrite(INL1,HIGH);
    digitalWrite(INL2,LOW);

    analogWrite(ENR,spd);
    analogWrite(ENL,spd); 
  }
  
void brakeRobot(void){

    digitalWrite(INR1,HIGH);
    digitalWrite(INR2,HIGH);
    digitalWrite(INL1,HIGH);
    digitalWrite(INL2,HIGH);

    analogWrite(ENR,255);
    analogWrite(ENL,255);
}

void reverseRobot(int spd){
    digitalWrite(INR2,HIGH);
    digitalWrite(INR1,LOW);
    digitalWrite(INL2,HIGH);
    digitalWrite(INL1,LOW);

    analogWrite(ENR,spd);
    analogWrite(ENL,spd); 
}



void turnRobot(float angle){
    float heading1 = getHeading();
    heading1 += angle;
    if(heading1 >= 360){
      heading1 -= 360;  
    }
    else if(heading1<0){
        heading1 += 360;
    }
    while(true){
        float err = errorang(heading1);
        if (err < 3.0){
          break;  
        }
        //float speed_P = map(err,0,180,pwm_min,pwm_max);
        //Serial.print(err);
        //Serial.print("\t");
       // Serial.println(speed_P);
        turnRobotAngle(heading1);
        delay(300);
        //Serial.println(getHeading());
      
    }  
    
}


void turnRobotAngle(float goangle){
      analogWrite(ENR,0);
      analogWrite(ENL,0);
    if(errorang(goangle) <= 3){
      return;  
    }else{
        float heading = getHeading();
        if(goangle<180){
          if((heading >= goangle)&&(heading <= (goangle+180))){
            digitalWrite(INR1,HIGH);
            digitalWrite(INR2,LOW);
            digitalWrite(INL1,LOW);
            digitalWrite(INL2,HIGH); 
            while(true){
              heading = getHeading();
              if(heading > (goangle+180)){
                heading -= 360;  
              }
              if(heading <= (goangle+3.0)){
                  brakeRobot();
                  break;
              }
              
              analogWrite(ENR,map(errorang(goangle),0,180,pwm_min,pwm_max));
              analogWrite(ENL,map(errorang(goangle),0,180,pwm_min,pwm_max));  
            }
          } else{
           // Serial.println("EN");
            digitalWrite(INR1,LOW);
            digitalWrite(INR2,HIGH);
            digitalWrite(INL1,HIGH);
            digitalWrite(INL2,LOW);  
            while(true){
              heading = getHeading();
              if(heading > (goangle+180)){
                heading -= 360;  
              }
              if(heading >= (goangle-3.0)){
                  brakeRobot();
                  break;
              }
              analogWrite(ENR,map(errorang(goangle),0,180,pwm_min,pwm_max));
              analogWrite(ENL,map(errorang(goangle),0,180,pwm_min,pwm_max));  
            } 
          }
        }else{
          if((heading <= goangle)&&(heading >= (goangle-180))){
                digitalWrite(INR1,LOW);
                digitalWrite(INR2,HIGH);
                digitalWrite(INL1,HIGH);
                digitalWrite(INL2,LOW); 
                                            //                while(getHeading() < (goangle-4.0)){
                                            //                  analogWrite(ENR,spd);
                                            //                  analogWrite(ENL,spd);
                                            //                }
                                            //                brakeRobot();  

              while(true){
                heading = getHeading();
                if(heading < (goangle-180)){
                  heading += 360;  
                }
                if(heading >= (goangle-3.0)){
                    brakeRobot();
                    break;
                }
                analogWrite(ENR,map(errorang(goangle),0,180,pwm_min,pwm_max));
                analogWrite(ENL,map(errorang(goangle),0,180,pwm_min,pwm_max));  
            }
  
          } else{
              digitalWrite(INR1,HIGH);
              digitalWrite(INR2,LOW);
              digitalWrite(INL1,LOW);
              digitalWrite(INL2,HIGH);

              while(true){
              heading = getHeading();
              if(heading < (goangle-180)){
                heading += 360;  
              }
              if(heading <= (goangle+3.0)){
                  brakeRobot();
                  break;
              }
              analogWrite(ENR,map(errorang(goangle),0,180,pwm_min,pwm_max));
              analogWrite(ENL,map(errorang(goangle),0,180,pwm_min,pwm_max));  
            }
          }
        }
    }
}


float errorang(float goangle){
    float heading = getHeading();
    float error = abs(heading-goangle);
    if(error > 180.0){
      error = 360 - error;  
    }
    return error;
}




