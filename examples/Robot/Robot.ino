#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <FWKS_Robotics.h>
#include <limits.h>

Robot myRobot;

void setup(){
   Serial.begin(9600);

   myRobot.begin();
   myRobot.speed(255);
   //Our robot here is "perfect", meaning both wheels move in lockstep
   myRobot.straitness(1, 1);

   Serial.println("Moving Forward");
   myRobot.forward();
   delay(1000);

   Serial.println("Moving Backward");
   myRobot.backward();
   delay(1000);

   Serial.println("Moving Left");
   myRobot.left();
   delay(1000);

   Serial.println("Moving Right");
   myRobot.right();
   delay(1000);

   Serial.println("Rotating Clock-wise");
   myRobot.pivot_cw();
   delay(500);

   Serial.println("Rotating Counter-clockwise");
   myRobot.pivot_ccw();
   delay(500);

   for(uint8_t i = 0; i < UCHAR_MAX; i++){
      myRobot.forward(i);
      delay(10);
   }
   for(uint8_t i = UCHAR_MAX; i>0; i--){
      myRobot.forward(i);
      delay(10);
   }

   Serial.println("Braking");
   myRobot.brake();
   //myRobot.release();

}

void loop(){

}
