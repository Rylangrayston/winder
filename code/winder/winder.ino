/*
This code runs winder 
winder is a coil making machine
find out more here http://github.com/rylangrayston/winder
Gpl2 
 */
 
// asing pins to motors
int mot1Step = 2;
int mot1Dir = 3;
int mot2Step = 4;
int mot2Dir = 5; 
int motEnabel = 10;

;
int coilSpindelMultiplier = 5;  //before speedDif is aplyed the coild spindle will go this much faster.
int dynamicSpeedDivisor = 1;  // speed differnce between the two motors 
int speedDivisorCount = 0;
int globalSpeed;  // affects the speed of both motors the same 

int loopDivisor = 100; // so that we can do things every N times we go thure the loop 
int loopCount = 0; // grows to 10 over and over 

int maxSpeed = 100;

int stepsPerRev = 3200;
int coilMotStepCount = 0; 
int coilTurns = 0;

int spoolCount = 0; 
int spoolDetect = 0;
int spoolSensor = 0;

double spoolSensorCercumfrance = 250; // each time the spool gose this around its this much wire in mm
double ohmsGoal = 16;

// Ohms of each gage of wire per meeter 
double awg42ohms = 6.07;
double awg40ohms = 3.42;
double awg38ohms = 2.19;
double awg36ohms = 1.3;
double awg34ohms = .844;

// spoolAwg is the oms per meeter on the curent spool.
double ohmsPerMeeter = awg38ohms;

double dynamicCoilOhms = 0;
double turnsPerMeeter = 1000 / spoolSensorCercumfrance;
double ohmsPerSensorTurn =   ohmsPerMeeter / turnsPerMeeter; 





// note A0 will control global speed 
// and A1 will control differnce in speed

int isFirstLoops = 1;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(mot1Step, OUTPUT);
  pinMode(mot1Dir, OUTPUT);
  pinMode(mot2Step, OUTPUT);
  pinMode(mot2Dir, OUTPUT);
  pinMode(motEnabel, OUTPUT);
}









// the loop routine runs over and over again forever:
void loop() {
// just a startup thing to knwo the motors work.
  while(isFirstLoops < 500){
    digitalWrite(motEnabel, LOW);
    ++isFirstLoops;
    digitalWrite(mot1Step, HIGH);
    digitalWrite(mot1Step, LOW);
    delayMicroseconds(500);
  }
 
 /// here where it all begins:
  ++loopCount;
  if (loopCount > loopDivisor){
   loopCount = 0;
   globalSpeed = analogRead(A0);
   dynamicSpeedDivisor = analogRead(A1)/50;
   //Serial.println(dynamicSpeedDivisor); 
   spoolSensor = analogRead(A2);
   // Serial.println(spoolSensor);
    
    
    if(spoolSensor < 200){
  spoolDetect = 0;
}

if(spoolSensor > 700 && spoolDetect == 0){
  spoolDetect = 1;
  ++spoolCount;
  dynamicCoilOhms += ohmsPerSensorTurn;
  Serial.println("Ohms off spool:");
  Serial.println(dynamicCoilOhms);
  if (dynamicCoilOhms > ohmsGoal){
    Serial.println("you coil has an Ohms resistance of:");
    Serial.println(dynamicCoilOhms);
    Serial.println("your coil has this many turns:");
    Serial.println(coilTurns);
    Serial.println("the spool count was:");
    Serial.println(spoolCount);
    Serial.println("finished");
    while(true){}
  }
}
    
    
    
  }
 delayMicroseconds(globalSpeed + maxSpeed);
 
 ++speedDivisorCount;
 if(speedDivisorCount > dynamicSpeedDivisor){
   speedDivisorCount = 0;
   digitalWrite(mot2Step, HIGH);
   digitalWrite(mot2Step, LOW);
 }
    
 for(int x = 0; x< coilSpindelMultiplier; ++x){
   digitalWrite(mot1Step, HIGH);
   digitalWrite(mot1Step, LOW);
     
 }
 coilMotStepCount += coilSpindelMultiplier ;
 if(coilMotStepCount > stepsPerRev){
   coilMotStepCount -= stepsPerRev;
   ++coilTurns;
   //Serial.println(coilTurns);
 }
 
 


 
  
    
    // read the input on analog pin 0:
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
 //float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.println(coilTurns);
}
