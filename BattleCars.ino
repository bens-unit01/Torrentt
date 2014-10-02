



#include <Servo.h>
//#include <SoftwareSerial.h>


#define rotation_servo_pin 3
#define MCLR  5

Servo rotationServo;
byte buffer[50]; 
int b, i =0;
int angle = 90;

int estimated = 90;
//SoftwareSerial mySerial(8, 9); // RX, TX
void setup()
{
  

  
 // XYZ board init 
   pinMode(MCLR, OUTPUT);
   delay(1000);
   digitalWrite(MCLR, LOW);
   delay(10);
   digitalWrite(MCLR, HIGH);
   pinMode(MCLR, INPUT);
 
 
 
 
 //--------------
  
  
 
  Serial.begin(9600);
//  mySerial.begin(9600);
 
 delay(30);
 Serial.write(0x3e);
 Serial.write(0x54);
 Serial.write(0x0a);
  
  // projector setup
  
 rotationServo.attach(rotation_servo_pin);
 rotationServo.write(90);
 delay(15);
  
  
}


void loop()
{
  i++;
   if( i % 10 == 0 ) {

      angle = estimated;
    } else {
     
          if( angle > estimated){
              angle--;
          } else {
             angle++;
          }
          
       if( angle < 5 ) angle = 10;
       if( angle > 170) angle = 165;
          rotationServo.write(angle);
          delay(15);
        
    }
 //    mySerial.println(estimated);
    
   if( Serial.available() >= 3 ){
     int j = 0;
    while(Serial.available()){
       buffer[j] = Serial.read();
       j++;
        }
        j = 0;
      while(buffer[i] != 0x78 )  j++;
	 //if( i > 3 ) return; 
         // byte fwd_bwd= buffer[i+1];
          b = buffer[j+2];  
          int curAngle = 0;
       if( b > 0x60 ){

            //angle ++;
            curAngle = 90 - 2*(b - 0x60 );
    
       } else {
  
          curAngle = 90 + 2*( b - 0x40 );
                
       }
       
       if( curAngle < 5 ) curAngle = 10;
       if( curAngle > 170) curAngle = 165;
       
       estimated = curAngle;
      
     
   
     }
  
}

void serialEvent() {
  
  
 

 
}

