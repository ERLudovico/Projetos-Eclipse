#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>



#define SERVOMIN  120 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  580 // this is the 'maximum' pulse length count (out of 4096)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // the servo

class Sweeper {


	int srvn ;
	int pos; // current servo position
	int increment; // increment to move for each interval
	int updateInterval; // interval between updates
	unsigned long lastUpdate; // last update of position

	public:
	Sweeper(int servo,int interval) {
		updateInterval = interval;
		increment = 1;
		srvn = servo;
	}

	void Attach(){
		//servo.attach(pin);
		moveServo(srvn, 90);
		delay(1000);
	}

	void Detach() {
		//servo.detach();
	}

	void moveServo(int servo, int angle) {
	    int pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
	    pwm.setPWM(servo, 0, pulselength);
	}

	void Update() {
		// CADA VEZ QUE ENTRA AQUI INCREMENTA EM UM, EH COMO SE FOSE UM FOR BASEADO EM TEMPO (INTERVAL)
		if((millis() - lastUpdate) > updateInterval){ // time to update

			lastUpdate = millis();
			pos += increment;
			moveServo(srvn,pos);
			Serial.println(pos);

			if ((pos >= 180) || (pos <= 0)){ // end of sweep
				// reverse direction
				increment = -increment;
			}
		}
	}
};


Sweeper sweeper1(0, 50);
Sweeper sweeper2(3, 50);
Sweeper sweeper3(4, 50);



void setup() {
	pwm.begin();
	pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
	sweeper1.Attach();
	sweeper2.Attach();
	sweeper3.Attach();
}

void loop(){
	sweeper1.Update();
	sweeper2.Update();
	sweeper3.Update();
}
