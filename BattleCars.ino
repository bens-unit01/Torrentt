



#include <Servo.h>
#include <SoftwareSerial.h>


#define rotation_servo_pin 3
#define MCLR  5

Servo rotationServo;
byte buffer[50]; 
int b, i =0;
int angle = 90;

int estimated = 90;
SoftwareSerial mySerial(8, 6); // RX, TX
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
  mySerial.begin(9600);
 
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
     if( angle != estimated){
          if( angle > estimated){
              angle--;
          } else {
             angle++;
          }
          
       if( angle < 5 ) angle = 10;
       if( angle > 170) angle = 165;
         rotationServo.write(180 - angle);
     //  mySerial.println(angle);
          delay(15);
     } 
    }
//     mySerial.println(estimated);
    
   if( Serial.available() > 0 ){
     b = Serial.read();
 
       int temp = 0;
       if( b > 0x60 ){

            //angle ++;
            temp = 90 + 90 *( b - 0x60 ) / 32;
    
       } else {
  
           temp = 90 - 90 *( b - 0x40 ) / 32;
          
                
       }
       
       if( temp < 5 ) temp = 5;
       if( temp > 170) temp = 170;
       
       estimated = temp;
    //   mySerial.print(estimated);  mySerial.print(" ");  mySerial.println(b); 
      
     
   
     }
  
}



