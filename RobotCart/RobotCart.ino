#include <Servo.h>

const int SERVO_1 = 9;
const int SERVO_2 = 10;

Servo servo1;  
Servo servo2;

//Comment out to disable debug messages
#define DEBUG

//Comment out to select spark motor controller constants
#define JAGUAR

#ifdef JAGUAR
//Jagaur
//https://github.com/wpilibsuite/allwpilib/blob/ed1a94531a6aa14617b74bc5139817c0529faf54/wpilibc/athena/src/Jaguar.cpp
const float MIN_REVERSE = 1448.0;
const float FULL_REVERSE = 685.0;
const float MIN_FORWARD = 1552.0;
const float MAX_FORWARD = 2302.0;
const float NEUTRAL = 1450;
#else
//Spark constants
//TODO, need to tune the following constants
//https://github.com/wpilibsuite/allwpilib/blob/ed1a94531a6aa14617b74bc5139817c0529faf54/wpilibc/athena/src/Spark.cpp
const float MIN_REVERSE = 1460.0;
const float FULL_REVERSE = 999.0;
const float MIN_FORWARD = 1550.0;
const float MAX_FORWARD = 2003;
const float NEUTRAL = 1500;
#endif


void writeMotor(Servo &s, float speed) {
  if(speed > 0.001) {
     //Forward
    int out = (MAX_FORWARD-MIN_FORWARD)*speed+MIN_FORWARD;
    s.writeMicroseconds(out);

#ifdef DEBUG
    Serial.print("FOut:");
    Serial.println(out);
#endif
  } else if(speed < -0.001) {
    //Reverse
    int out = (FULL_REVERSE-MIN_REVERSE)*abs(speed)+MIN_REVERSE;
    s.writeMicroseconds(out);

#ifdef DEBUG
    Serial.print("BOut:");
    Serial.println(out);
#endif
  } else {
    //Nuetral
    s.writeMicroseconds(NEUTRAL);
  }
}

void setup() {
  servo1.attach(SERVO_1);  
  servo2.attach(SERVO_2);
  Serial.begin(9600);
  Serial.println("Please input a floating point number from -1.00 to 1.00, with 0.0 being neutral");
}

float i = 0;

void loop() {
  if(Serial.available()) {
    i = Serial.parseFloat();
  }
  writeMotor(servo1, i);
  writeMotor(servo2, i);
  delay(50);
}


