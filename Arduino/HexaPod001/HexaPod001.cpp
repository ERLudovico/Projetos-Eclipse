#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// COXA - FEMUR - TIBIA

#define SERVOMIN  120 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  580 // this is the 'maximum' pulse length count (out of 4096)
boolean sobe = 0 ;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // the servo

class Pata {


	int coxa ;
	int femur ;
	int tibia ;
	int coxaDegrMin ;
	int coxaDegrMax ;
	int femurDegrMin ;
	int femurDegrMax ;
	int tibiaDegrMin ;
	int tibiaDegrMax ;
	int patan ;
	int pataOffSet [4][3] = {
			{ 0, 0,  0}, //Pata 0 - Coxa, Femur, Tibia
			{30,-5,  0}, //Pata 1 - Coxa, Femur, Tibia
			{ 0, 0,  0}, //Pata 2 - Coxa, Femur, Tibia
			{80,20,-20}  //Pata 3 - Coxa, Femur, Tibia
	};
	//		   Pata N        {coxa,femur,tibia}
	boolean dir ;
	boolean fflop ;
	boolean isPata0Down = true;
	boolean isPata1Down = true;
	boolean isPata2Down = true;
	boolean isPata3Down = true;
	int pos = 90; // current servo position
	int increment; // increment to move for each interval
	int updateInterval; // interval between updates
	unsigned long lastUpdate; // last update of position

	public:
	Pata(int Patan , int Coxa, int Femur, int Tibia, boolean FF , boolean Dir , int CoxaDegrMin, int CoxaDegrMax , int FemurDegrMin , int FemurDegrMax, int TibiaDegrMin, int TibiaDegrMax, int interval) {
		updateInterval = interval; //tempo em ms que o servo será atualizado em um grau
		increment = 1; // De quantos em quantos graus será incrmentado o servo
		patan = Patan ;
		coxa = Coxa  ;
		femur = Femur ;
		tibia = Tibia ;
		dir = Dir;
		fflop = FF;
		coxaDegrMin  = CoxaDegrMin  + pataOffSet [patan] [0];
		coxaDegrMax  = CoxaDegrMax  + pataOffSet [patan] [0];
		femurDegrMin = FemurDegrMin + pataOffSet [patan] [1];
		femurDegrMax = FemurDegrMax + pataOffSet [patan] [1];
		tibiaDegrMin = TibiaDegrMin + pataOffSet [patan] [2];
		tibiaDegrMax = TibiaDegrMax + pataOffSet [patan] [2];

	}

	void RedefineThreadInterval(int interval){
		updateInterval = interval;
	}

	void init(){
		//servo.attach(pin);
		moveServo(coxa,  coxaDegrMax);
		moveServo(femur, femurDegrMax);
		moveServo(tibia, tibiaDegrMax);

			if ( dir == 0 ){
				pos = coxaDegrMax ;
			} else {
				pos = coxaDegrMin ;
			}

			if ( patan == 1 ) pos = pos + 75 ;
			//if ( patan == 2 ) pos = pos + 25 ;
			//if ( patan == 3 ) pos = pos + 0 ;

		delay(1000);
	}

	void Detach() {
		//servo.detach();
	}

	void moveServo(int servo, int angle) {
	    int pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
	    pwm.setPWM(servo, 0, pulselength);
	}

	boolean getIsPataDown (){
		boolean pataDown = true ;
		if ( patan = 0 ) pataDown = isPata0Down;
		if ( patan = 1 ) pataDown = isPata1Down;
		if ( patan = 2 ) pataDown = isPata2Down;
		if ( patan = 3 ) pataDown = isPata3Down;

		return pataDown;
	}

	void setIsPataDown(boolean pata0, boolean pata1,boolean pata2,boolean pata3){

		if ( patan != 0 ) isPata0Down = pata0;
		if ( patan != 1 ) isPata1Down = pata1;
		if ( patan != 2 ) isPata2Down = pata2;
		if ( patan != 3 ) isPata3Down = pata3;

	}



	void Update() {
		// CADA VEZ QUE ENTRA AQUI INCREMENTA EM UM, EH COMO SE FOSE UM FOR BASEADO EM TEMPO (INTERVAL)
		//Serial.println("==============================================");
		//Serial.print("Incio -->");
		//Serial.print(patan);
		//Serial.print("<-->");
		//Serial.print(pos);
		//Serial.println("<--");
		if((millis() - lastUpdate) > updateInterval){ // time to update

			lastUpdate = millis();
			//if ( ( ( patan == 0 ) && ( isPata1Down ) )  ||  ( ( patan == 1 ) && ( isPata0Down ) ) ){
			//if ( ( ( patan == 1 ) && ( isPata0Down ) ) || ( patan == 0 )  ) {
				/*
				 * Coxa para Frente
				 */
				if (dir) {
					//degreeMin += increment;
					if (pos < coxaDegrMax){
						pos += increment;
						moveServo(coxa, pos);
						//Serial.println("=========== move coxa ========================");
						//Serial.print(patan); Serial.print(" <==> ") ;Serial.print(coxa);Serial.print(" <==> ");Serial.println(pos);
						//Serial.println("=========== move coxa ========================");
					} else {
						if (fflop) dir = 0 ;
						if ( patan == 0 ) isPata0Down = true ;
						if ( patan == 1 ) isPata1Down = true ;
						Serial.println(patan);
						Serial.print("isPata0Down: ");Serial.println(isPata0Down);
						Serial.print("isPata1Down: ");Serial.println(isPata1Down);
						// Sobe Femur
						moveServo(femur, femurDegrMin);//100);
						moveServo(tibia, tibiaDegrMin);//70);


					}
				/*
				 * Coxa para tras
				 */
				} else {
					if (pos > coxaDegrMin ){
						pos -= increment;
						moveServo(coxa, pos);
					} else {
						if (fflop) dir = 1 ;
						if ( patan == 0 ) isPata0Down = false ;
						if ( patan == 1 ) isPata1Down = false ;
						Serial.print("isPata0Down: ");Serial.println(isPata0Down);
						Serial.print("isPata1Down: ");Serial.println(isPata1Down);
						// Abaixa femur
						moveServo(femur, femurDegrMax);
						moveServo(tibia, tibiaDegrMax);

					}
				}

			//}
		}
	}
};

// Lado Direito
Pata pata0_Dir_frt(0,  0, 1, 2, 1, 1, 35,110, 80,150, 50,100, 10);
Pata pata1_Dir_trs(1,  4, 5, 6, 1, 1, 35,110, 80,150, 50,100, 10);
// Lado Esquerdo
//Pata pata2_Esq_trs(2,  8, 9,10, 1, 1,  0, 75, 30,80,  80,130, 10);
//Pata pata3_Esq_frt(3, 12,13,14, 1, 1,  0, 75, 30,80,  80,130, 10);



void setup() {
	Serial.begin(9600);
	pwm.begin();
	pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
	pata0_Dir_frt.init();
	pata1_Dir_trs.init();
	//pata2_Esq_trs.init();
	//pata3_Esq_frt.init();
}

void loop(){
	//Serial.println("\nLoop\r");
	pata0_Dir_frt.Update();
	pata1_Dir_trs.Update();

	pata0_Dir_frt.setIsPataDown(true,pata1_Dir_trs.getIsPataDown(),true,true);
	pata1_Dir_trs.setIsPataDown(pata0_Dir_frt.getIsPataDown(),true,true,true);

	//pata2_Esq_trs.Update();
	//pata3_Esq_frt.Update();
}
