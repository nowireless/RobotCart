#include <Servo.h>

//Define Buttons
const int For_M1 = 8; //Rotate m1 cw
const int Rev_M1 = 6; //Rotate m2 ccw
const int For_M2 = 10; //Rotate m2 cw
const int Rev_M2 = 12; //rotate m2 ccw

const int SERVO_1 = 3;
const int SERVO_2 = 5;

Servo servo1;  
Servo servo2;

//Comment out to disable debug messages
#define DEBUG

//Comment out to select spark motor controller constants
//#define JAGUAR

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

	pinMode(For_M1, INPUT);
	digitalWrite(For_M1, HIGH); // connect internal pull-up

	pinMode(Rev_M1, INPUT);
	digitalWrite(Rev_M1, HIGH); // connect internal pull-up

	pinMode(For_M2, INPUT);
	digitalWrite(For_M2, HIGH); // connect internal pull-up

	pinMode(Rev_M2, INPUT);
	digitalWrite(Rev_M2, HIGH); // connect internal pull-up
}

float m1 = 1;
float m2 = 1;

void loop() {
	int fM1State = digitalRead(For_M1);
	if (fM1State == LOW){
		writeMotor(servo1, m1);
	} else { 
		int rM1State = digitalRead(Rev_M1);
		if (rM1State == LOW){
			writeMotor(servo1, -m1);
		} else { 
			writeMotor(servo1, 0);
		}
	}
	
	int fM2State = digitalRead(For_M2);
	if (fM2State == LOW){
		writeMotor(servo2, m2);
	} 

	int rM2State = digitalRead(Rev_M2);
	if (rM2State == LOW){
		writeMotor(servo2, -m2);
	} else {
		writeMotor(servo2, 0);
	}
}

