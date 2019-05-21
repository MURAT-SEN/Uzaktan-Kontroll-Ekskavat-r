

#include <SPI.h>  
#include "RF24.h"
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h> 
RF24 myRadio (7, 8); 
void escavator(int X1,int Y1);
Servo servo;
Servo servo1;   


struct package
{
  int X=512;
  int Y=512;
  int X1=512;
  int Y1=512;

};

byte addresses[][6] = {"0"}; 
int OUT1 = 2;
int OUT2 = 4;
int EnA=3;
int OUT3 = ;
int OUT4 = ;
int EnB=9;
int servo_pin = 5;
int servo1_pin = 6;


typedef struct package Package;
Package data;



  

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  servo.attach (servo_pin) ; 
  servo1.attach (servo1_pin ) ; 
  analogWrite(OUT1, 0);
  analogWrite(OUT2, 0);
  analogWrite(OUT3, 0);
  analogWrite(OUT4, 0);
}


void loop()  
{
  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print("X:");
    Serial.print(data.X);
    Serial.print("      Y");
    Serial.println(data.Y);
    int X = data.X;
    int Y = data.Y;
    int foward = map(X,524,1024,0,255);
    int backward = map(X,500,0,0,255);
    int right = map(Y,524,1024,0,255);
    int left = map(Y,500,0,0,255);
    int X1 = data.X1;
    int Y1 = data.Y1;
    int escavator_up=map(X1,524,1024,90,180);
    int escavator_dowm=map(X1,524,1024,0,89);
    int escavator1_up=map(Y1,524,1024,90,180);
    int escavator1_down=map(Y1,524,1024,0,89);
   
  
   
  

    if(X > 524 && Y < 524 && Y > 500){
      analogWrite(OUT3, 1);
      analogWrite(OUT4, 0);
      analogWrite(EnA, foward);
      analogWrite(OUT1,1 );
      analogWrite(OUT2, 0);
      analogWrite(EnB, foward);
        
    }else if(X < 500 && Y < 524 && Y > 500){
      analogWrite(OUT4, 1);
      analogWrite(OUT3, 0);
      analogWrite(EnA,  backward);
      analogWrite(OUT2,1);
      analogWrite(OUT1, 0);
       analogWrite(EnB,  backward);
      
    }else if(X < 524 && X > 500 && Y < 524 && Y > 500){
      analogWrite(OUT4, 0);
      analogWrite(OUT3, 0);
      analogWrite(OUT2, 0);
      analogWrite(OUT1, 0);
      
    }else if(X < 524 && X > 500 && Y > 524){
      analogWrite(OUT4, 0);
      analogWrite(OUT3, 1);
       analogWrite(EnA,  left);
      analogWrite(OUT2, 1);
      analogWrite(OUT1, 0);
      analogWrite(EnB,  left);
      
    }else if(X < 524 && X > 500 && Y < 500){
      analogWrite(OUT4, 1);
      analogWrite(OUT3, 0);
      analogWrite(EnA,  right);
      analogWrite(OUT2, 0);
      analogWrite(OUT1, 1);
      analogWrite(EnB, right);
    
    }else if(X > 524 && Y > 524){
      analogWrite(OUT3, 1);
      analogWrite(OUT4, 0);
      analogWrite(EnA, foward);
      analogWrite(OUT1, 1);
      analogWrite(OUT2, 0);
      analogWrite(EnB, foward-right);
    
    }else if(X > 524 && Y < 500){
      analogWrite(OUT3, 1);
      analogWrite(OUT4, 0);
      analogWrite(EnA, foward-left);
      analogWrite(OUT1, 1);
      analogWrite(OUT2, 0);
      analogWrite(EnB, foward);
 
    }else if(X < 500 && Y > 524){
      analogWrite(OUT4, 1);
      analogWrite(OUT3, 0);
         analogWrite(EnA, backward);
      analogWrite(OUT2, 1);
      analogWrite(OUT1, 0);
      analogWrite(EnB, backward-right);
      
    }else if(X < 500 && Y < 500)
    {
      analogWrite(OUT4, 1);
      analogWrite(OUT3, 0);
        analogWrite(EnA, backward-left);
      analogWrite(OUT2, 1);
      analogWrite(OUT1, 0);
       analogWrite(EnB, backward);
      
    }
     else if(X1 > 524 && Y1 < 524 && Y1 > 500)
    {
      servo.write (escavator_up) ;
    }
    else if(X1 < 500 && Y1 < 524 && Y1 > 500)
    {
    servo.write (escavator_dowm);
    }
    else if(X1 < 524 && X1 > 500 && Y1 < 524 && Y1 > 500)
    {
      servo.write (90) ;
      servo1.write (90) ;
    }
    else if(X1 < 524 && X1 > 500 && Y1 > 524)
    {
         servo1.write (escavator_up) ;
    }
    else if(X1 < 524 && X1 > 500 && Y1 < 500)
    {
    servo1.write (escavator_dowm) ;
    }
    else if(X1 > 524 && Y1 > 524)
    {
     servo.write (escavator_up) ;
      servo1.write (escavator_up) ;
    }
    else if(X1 > 524 && Y1 < 500)
    {
      servo.write (escavator_up) ;
      servo1.write (escavator_dowm) ;
    }
    else if(X1 < 500 && Y1 > 524)
    {
      servo.write (escavator_dowm) ;
      servo1.write (escavator_up) ;
    }
    else if(X1 < 500 && Y1 < 500)
    {
         servo.write (escavator_dowm) ;
      servo1.write (escavator_dowm) ;
    }

  
  

    
  }

}
