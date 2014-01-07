/*************************************/
/*	Arduino Code for the Winder  */
/*	Written By Albert La	     */
/*	January 7, 2014		     */
/*************************************/

//Pin Assignments
#define mot1Step	2
#define mot1Dir		3
#define mot2Step	4
#define mot2Dir		5
#define motEnable	10

#define AWG42           42
#define AWG40           40
#define AWG38           38
#define AWG36           36
#define AWG34           34

//Variables
int speedDividerCount = 0;
int loopCount = 0;
int globalSpeed;
int coilMotStepCount = 0; 
int coilTurns = 0;
int spoolCount = 0; 
int spoolDetect = 0;
int spoolSensor = 0;
int isFirstLoops = 1;
int wireGauge;

double ohmsGoal;
double ohmsPerMeter;
double dynamicCoilOhms = 0;

//Constants
const int COILSPEEDMULTIPLIER = 5;		//speed of the coil motor
const int SPEEDDIVIDER = 1;  			//speed differnce of the motors
const int LOOPDIVIDER = 100; 			//We can accomplish N things when we go through the loop
const int MAXSPEED = 100;				//Maximum speed of the spool
const int STEPSPERREV = 3200;
const double SPOOLSENSORCIRC = 250; 	// each time the spool rotates around it is this much wire in mm

// Ohms of each gauge of wire per meter 
const double AWG42OHMS = 6.07;
const double AWG40OHMS = 3.42;
const double AWG38OHMS = 2.19;
const double AWG36OHMS = 1.3;
const double AWG34OHMS = .844;

double turnsPerMeter = 1000 / SPOOLSENSORCIRC;
double ohmsPerSensorTurn =   ohmsPerMeter / turnsPerMeter;


// note A0 will control global speed 
// and A1 will control differnce in speed

// This setup routine runs whenever you reset the Arduino
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //assign pinmodes to motor control
  pinMode(mot1Step, OUTPUT);
  pinMode(mot1Dir, OUTPUT);
  pinMode(mot2Step, OUTPUT);
  pinMode(mot2Dir, OUTPUT);
  pinMode(motEnable, OUTPUT);

  //set defaults for settings
  wireGauge = AWG36;
  ohmsGoal = 16;
  ohmsPerMeter = AWG36OHMS;
}

boolean Menu()
{
  int menuOption = 0;
  boolean returnCondition = false;
  //Display menu choose options
  Serial.println("****************************************");
  Serial.println("		Choose an option:");
  Serial.println("	1.  Enter impedance");
  Serial.println("	2.  Enter wire gauge");
  Serial.println("	3.  Make coil");
  Serial.println("****************************************");
  Serial.print("Current Settings: Impedance: ");
  Serial.print(ohmsGoal);
  Serial.print(" Wire Gauge: ");
  Serial.println(wireGauge);
  
  while (!Serial.available());
  if (Serial.available() > 0)
  {
    menuOption = Serial.parseInt();
  }
  
  switch (menuOption)
  {
    case 1:
      //Impedance
      returnCondition = false;
      break;
    case 2:
      //Wire Gauge
      returnCondition = false;
      break;
    case 3:
      //Make the coil
      returnCondition = true;
      break;
    default:
      //handle invalid input
      Serial.println("Invalid input");
      returnCondition = false;
      break;
  }
  return returnCondition;
}

void loop()
{
    while(!(Menu()));

}

