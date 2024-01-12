/*------ Arduino Fire Fighting Robot Code by hobby project---- */
#include <Adafruit_I2CDevice.h>
#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>  //include servo.h library
Servo myservo;

Adafruit_PWMServoDriver srituhobby = Adafruit_PWMServoDriver();

int pos = 0;    
boolean fire = false;
 
#define Left 10      // left sensor
#define Right 12    // right sensor
#define Forward 13   //front sensor

#define servo1 0
#define servo2 1
#define servo3 2

#define LM1 3       // left motor
#define LM2 5       // left motor
#define RM1 6       // right motor
#define RM2 9       // right motor
#define pump 7
 
void setup()
{
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);

  srituhobby.begin();
  srituhobby.setPWMFreq(60);
  srituhobby.setPWM(servo1, 0, 340);
  srituhobby.setPWM(servo2, 0, 150);
  srituhobby.setPWM(servo3, 0, 300);
 
  myservo.attach(11);
  myservo.write(90); 
}
 
void put_off_fire()
{
   delay (500);
 
   digitalWrite(LM1, LOW);
   digitalWrite(LM2, LOW);
   digitalWrite(RM1, LOW);
   digitalWrite(RM2, LOW);
    

    
  for (int S3value = 300; S3value <= 520; S3value++) {
    srituhobby.setPWM(servo3, 0, S3value);
    delay(10);
  }

   digitalWrite(pump, HIGH);
  
  for (int S2value = 150; S2value <= 190; S2value++) {
    srituhobby.setPWM(servo2, 0, S2value);
    delay(10);
  }
  for (int S1value = 340; S1value >= 150; S1value--) {
    srituhobby.setPWM(servo1, 0, S1value);
    delay(10);
  }
  for (int S2value = 190; S2value > 110; S2value--) {
    srituhobby.setPWM(servo2, 0, S2value);
    delay(10);
  }
  for (int S1value = 150; S1value < 530; S1value++) {
    srituhobby.setPWM(servo1, 0, S1value);
    delay(10);
  }
  for (int S2value = 110; S2value <= 150; S2value++) {
    srituhobby.setPWM(servo2, 0, S2value);
    delay(10);
  }
  for (int S1value = 530; S1value >= 340; S1value--) {
    srituhobby.setPWM(servo1, 0, S1value);
    delay(10);
  }

  digitalWrite(pump,LOW);
  
  for (int S3value = 520; S3value > 300; S3value--) {
    srituhobby.setPWM(servo3, 0, S3value);
    delay(10);
  }
  
  fire=false;
}
 
void loop()
{
   myservo.write(90); //Sweep_Servo();
    int motorSpeed = 150;  
 
    if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
    {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    }
    
    else if (digitalRead(Forward) ==0) 
    {
      analogWrite(LM1, motorSpeed);
      digitalWrite(LM2, LOW);
      analogWrite(RM1, motorSpeed);
      digitalWrite(RM2, LOW);
      fire = true;
    }
    
    else if (digitalRead(Left) ==0)
    {
      analogWrite(LM1, motorSpeed);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
    }
    
    else if (digitalRead(Right) ==0) 
    {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      analogWrite(RM1, motorSpeed);
      digitalWrite(RM2, LOW);
    }
    
delay(100);//change this value to increase the distance
 
     while (fire == true)
     {
      put_off_fire();
     }
}
