#ifndef _FWKS_ROBOTICS_H_
#define _FWKS_ROBOTICS_H_
#include <inttypes.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

/** A driver for the FWKS Robot
 *
 * It operates by setting the motor state (velocity) and returns immediately. 
 * Most calls will not block, and will clearly state if they do. This means you have to
 * place delays if you want them. 
 *
 * For instance if you want to move the robot forward then stop, you would need to do the
 * following in approximately this order:
 *
 *    Robot myRobot; //create the book keeping object
 *
 *    myRobot.begin(); //initialize controls
 *    myRobot.forward(); //Set the shield to move the motors forward.
 *    delay(100); //wait for the robot to move forward
 *    myRobot.brake(); //stop the robot
 */
class Robot {
private:
   Adafruit_MotorShield _shield;
   uint8_t _speed;
   struct MotorState {
      Adafruit_DCMotor *motor;
      uint8_t speed;
      uint8_t state;
      float strait_comp;
   } _left, _right;
public:
   Robot();

   /** Sets up the initial motor state, and enables the motor driver
    *
    * This function must be called once and only once before any movements are attempted.
    */
   void begin(uint8_t motor_left=2, uint8_t motor_right=3);
   /** The default speed, used when speed is not specified in command
    */
   void speed(uint8_t speed);
   uint8_t speed() const;

   /** How much speed should be compensated to make the robot travel strait
    *
    * left - =1 no compensation, <1 less speed, >1 more speed
    * right - =1 no compensation, <1 less speed, >1 more speed
    */
   void straitness(float left, float right);
   float straitness_left() const;
   float straitness_right() const;

   /** Runs the motors with compensation in one of the motor modes.
    *
    */
   void run(uint8_t left_speed, uint8_t right_speed,
            uint8_t left_mode, uint8_t right_mode);

   /** Runs the motors with compensation in one of the motor modes, assuming mode is the same for both motors
    *
    */
   void run(uint8_t left_speed, uint8_t right_speed, uint8_t mode);

   /** Runs the motors with compensation in one of the motor modes, assuming speed and mode are the same
    *
    */
   void run(uint8_t speed, uint8_t mode);

   //----------------------------------------------------------------------------------------------------
   /** Releases the motors, this does not brake, just enables "coasting"
    *
    */
   void release(bool left=true, bool right=true);

   /** Brakes, this applies a short inverse pulse of constant amplitude, then releases the motors
    *
    */
   void brake(unsigned long duration=25);

   //----------------------------------------------------------------------------------------------------
   /** Runs motors forward using the default speed
    */
   void forward();

   /** Runs motors backward using the default speed
    */
   void backward();
   
   /** Runs the left motor forward or backward using the default speed
    */
   void left(bool forward=true);

   /** Runs the right motor forward or backward using the default speed
    */
   void right(bool forward=true);

   /** Runs the left motor forward and the right motor backward using the default speed
    */
   void pivot_ccw();

   /** Runs the right motor forward and the left motor backward using the default speed
    */
   void pivot_cw();

   //----------------------------------------------------------------------------------------------------
   /** Runs motors forward using the specified speed
    */
   void forward(uint8_t speed);

   /** Runs motors backward using the specified speed
    */
   void backward(uint8_t speed);

   /** Runs the left motor forward or backward using the specified speed
    */
   void left(uint8_t speed, bool forward=true);

   /** Runs the right motor forward or backward using the specified speed
    */
   void right(uint8_t speed, bool forward=true);

   /** Runs the right motor forward and the left motor backward using the specified speed
    */
   void pivot_ccw(uint8_t speed);

   /** Runs the right motor forward and the left motor backward using the specified speed
    */
   void pivot_cw(uint8_t speed);
};
#endif
