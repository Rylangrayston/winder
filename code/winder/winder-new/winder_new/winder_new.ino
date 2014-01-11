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
int dynamicSpeedDivider = 1;  			//speed differnce of the motors

double ohmsGoal;
double ohmsPerMeter;
double currentCoilOhms = 0;
double turnsPerMeter;
double ohmsPerSensorTurn;

//Constants
const int COILSPEEDMULTIPLIER = 1;		//speed of the coil motor
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
  //display the menu and get the new settings
  while(!(Menu()));
  turnsPerMeter = 1000 / SPOOLSENSORCIRC;
  ohmsPerSensorTurn =   ohmsPerMeter / turnsPerMeter;
}

boolean Menu()
{
  int menuOption = 0;
  int incomingByte;
  boolean returnCondition = false;
  //Display menu choose options
  Serial.println("****************************************");
  Serial.println("      Choose an option:");
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
      Serial.println("Enter Impedance");
      while(!Serial.available());
      if (Serial.available() > 0)
      {
        ohmsGoal = Serial.parseInt();
      }
      returnCondition = false;
      break;
    case 2:
      //Wire Gauge
      Serial.println("****************************************");
      Serial.println("  Choose Wire Gauge:");
      Serial.println("	1.  AWG 42");
      Serial.println("	2.  AWG 40");
      Serial.println("	3.  AWG 38");
      Serial.println("	4.  AWG 36");
      Serial.println("	5.  AWG 34");
      Serial.println("****************************************");
      while(!Serial.available());
      if (Serial.available() > 0)
      {
        incomingByte = Serial.parseInt();
      }
      switch(incomingByte)
      {
        case 1:
          wireGauge = AWG42;
          ohmsPerMeter = AWG42OHMS;
          break;
        case 2:
          wireGauge = AWG40;
          ohmsPerMeter = AWG40OHMS;
          break;
        case 3:
          wireGauge = AWG38;
          ohmsPerMeter = AWG38OHMS;
          break;
        case 4:
          wireGauge = AWG36;
          ohmsPerMeter = AWG36OHMS;
          break;
        case 5:
          wireGauge = AWG34;
          ohmsPerMeter = AWG34OHMS;
          break;
        default:
          wireGauge = AWG36;
          ohmsPerMeter = AWG36OHMS;
          break;
      }
      returnCondition = false;
      break;
    case 3:
      //Make the coil
      Serial.println("Lets make a coil wooooooooooooooooo!!!");
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
  // just a startup thing to knwo the motors work.
  while(isFirstLoops < 500){
    digitalWrite(motEnable, LOW);
    ++isFirstLoops;
    digitalWrite(mot1Step, HIGH);
    digitalWrite(mot1Step, LOW);
    delayMicroseconds(500);
  }
 
 /// here where it all begins:
  ++loopCount;
  if (loopCount > LOOPDIVIDER){
   loopCount = 0;
   globalSpeed = analogRead(A0);
   dynamicSpeedDivider = analogRead(A1)/50; 
   spoolSensor = analogRead(A2);
    
  if(spoolSensor < 200){spoolDetect = 0;}

  if(spoolSensor > 700 && spoolDetect == 0){
    spoolDetect = 1;
    ++spoolCount;
    currentCoilOhms += ohmsPerSensorTurn;
    Serial.print("Ohms off spool: ");
    Serial.println(currentCoilOhms);
    if (currentCoilOhms > ohmsGoal){
      Serial.print("you coil has an Ohms resistance of: ");
      Serial.println(currentCoilOhms);
      Serial.print("your coil has this many turns: ");
      Serial.println(coilTurns);
      Serial.print("the spool count was: ");
      Serial.println(spoolCount);
      Serial.println("finished");
      while(true){}
    }
  }
    
    
    
  }
 delayMicroseconds(globalSpeed + MAXSPEED);
 
 ++speedDividerCount;
 if(speedDividerCount > dynamicSpeedDivider){
   speedDividerCount = 0;
   digitalWrite(mot2Step, HIGH);
   digitalWrite(mot2Step, LOW);
 }
    
 for(int x = 0; x< COILSPEEDMULTIPLIER; ++x){
   digitalWrite(mot1Step, HIGH);
   digitalWrite(mot1Step, LOW);
     
 }
 coilMotStepCount += COILSPEEDMULTIPLIER;
 if(coilMotStepCount > STEPSPERREV){
   coilMotStepCount -= STEPSPERREV;
   ++coilTurns;
   //Serial.print("Coil Turns: "); Serial.println(coilTurns);
   //Serial.print("Current Ohms: "); Serial.println(currentCoilOhms);
 }
    

}

