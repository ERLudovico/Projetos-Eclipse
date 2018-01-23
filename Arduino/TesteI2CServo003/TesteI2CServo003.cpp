#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

void moveServo(int servo, int angle)
{
    int pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servo, 0, pulselength);
}

void setup()
{
  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void loop(){

	for (int ang = 0; ang <= 180; ang++){
		for (int srv = 0; srv < 5; srv++){
			moveServo(srv,ang);
			//moveServo(4,ang);
			delay(10);
		}
	}
	for (int ang = 180; ang > 0; ang--){
		for (int srv = 0; srv < 5; srv++){
			moveServo(srv,ang);
			//moveServo(4,ang);
			delay(10);
		}
	}
}
