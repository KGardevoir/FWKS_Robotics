#include <FWKS_Robotics.h>
#include <limits.h>

uint8_t invert_direction(uint8_t dir){
   switch(dir){
   case BACKWARD: return FORWARD;
   case FORWARD:  return BACKWARD;
   default:       return dir;
   }
}

Robot::Robot() : _shield() {
   _left.motor = NULL;
   _left.speed = 0;
   _left.state = RELEASE;
   _right.motor = NULL;
   _right.speed = 0;
   _right.state = RELEASE;
}

void Robot::begin(uint8_t motor_left, uint8_t motor_right){
   _shield.begin();
   _left.motor =  _shield.getMotor(motor_left);
   _right.motor =  _shield.getMotor(motor_right);
   speed(150);
   _left.speed = 0;
   _left.state = RELEASE;
   _right.speed = 0;
   _right.state = RELEASE;
}

void Robot::speed(uint8_t speed){ _speed = speed; }
uint8_t Robot::speed() const { return _speed; }

void  Robot::straitness(float left, float right){
   _left.strait_comp = left;
   _right.strait_comp = right;
}
float Robot::straitness_left() const { return _left.strait_comp; }
float Robot::straitness_right() const { return _right.strait_comp; }

void Robot::run(uint8_t left_speed, uint8_t right_speed,
                uint8_t left_mode, uint8_t right_mode){
//rounding
   left_speed = max(min(left_speed*_left.strait_comp+.5,  UCHAR_MAX), 0);
   right_speed = max(min(right_speed*_right.strait_comp+.5, UCHAR_MAX), 0);
   _left.speed = left_speed;
   _left.state = left_mode;
   _right.speed = right_speed;
   _right.state = right_mode;

   _left.motor->run(left_mode);
   _right.motor->run(right_mode);
   _left.motor->setSpeed(left_speed);
   _right.motor->setSpeed(right_speed);
}
void Robot::run(uint8_t left_speed, uint8_t right_speed, uint8_t mode){
   run(left_speed, right_speed, mode, mode);
}
void Robot::run(uint8_t speed, uint8_t mode){
   run(speed, speed, mode, mode);
}

void Robot::release(bool left, bool right){
   if(left){
      _left.motor->run(RELEASE);
      _left.speed = 0;
      _left.state = RELEASE;
   }
   if(right){
      _right.motor->run(RELEASE);
      _right.speed = 0;
      _right.state = RELEASE;
   }
}
void Robot::brake(unsigned long duration){
   run(_left.speed, _right.speed, invert_direction(_left.state), invert_direction(_right.state));
   delay(duration);
   release();
}

void Robot::forward(uint8_t speed){ run(speed, speed, FORWARD); }
void Robot::backward(uint8_t speed){ run(speed, speed, BACKWARD); }
void Robot::left(uint8_t speed, bool forward){ run(speed, 0, forward?FORWARD:BACKWARD); }
void Robot::right(uint8_t speed, bool forward){ run(0, speed, forward?FORWARD:BACKWARD); }
void Robot::pivot_ccw(uint8_t speed){ run(speed, speed, FORWARD, BACKWARD); }
void Robot::pivot_cw(uint8_t speed){ run(speed, speed, BACKWARD, FORWARD); }

void Robot::forward(){ forward(_speed);  }
void Robot::backward(){ backward(_speed); }
void Robot::left(bool forward){ left(_speed, forward); }
void Robot::right(bool forward){ right(_speed, forward); }
void Robot::pivot_ccw(){ pivot_ccw(_speed); }
void Robot::pivot_cw(){ pivot_cw(_speed); }

