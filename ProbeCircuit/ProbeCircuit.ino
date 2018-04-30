#include <AFMotor.h>
AF_DCMotor motor(4);

int analogPin = 7; // read from multiplexer using analog input 0
int strobePin = 52; // strobe is attached to digital pin 2
int resetPin = 53; // reset is attached to digital pin 3
float spectrumValue[7]; // to hold a2d values
float spectrumVals[2]; // two values we need
int DELAY = 3400;

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  analogReference(DEFAULT);

  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);

  motor.setSpeed(200);
}

void loop() {
  spinAndFind();
  //setVals();

  //checks to see if any of the values are in the frequencey range
  if (spectrumVals[0] > 3.0 || spectrumVals[1] > 3.0) {
    spin();
  }
}

void setVals() {
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
   
  
  for (int i = 0; i < 7; i++) {
    digitalWrite(strobePin, LOW);
    delayMicroseconds(30); // to allow the output to settle
    if (i == 2 || i == 3) {
      spectrumVals[i-2] = (5.0 / 1023.0) * analogRead(analogPin);
      spectrumValue[i] = spectrumVals[i-2];
    } else {
      spectrumValue[i] = (5.0 / 1023.0) * analogRead(analogPin);
    }
    
    Serial.print(i);
    Serial.print(": SEVEN VAL: ");
    Serial.print(spectrumValue[i]);
    Serial.print(" ");
  
    Serial.println();
     
    digitalWrite(strobePin, HIGH);
   }
}

void spin(int duration) {
  Serial.print("SPIN DURATION:");
  Serial.println(duration);
  motor.run(FORWARD);
  delay(duration);
  motor.run(RELEASE);
}
/* Spins the car in one full revolution. */
void spin() {
  Serial.println("SPIN");
  motor.run(FORWARD);
  delay(DELAY);
  motor.run(RELEASE);
}
/* Spins the car in NUM_INTERVALS intervals. At each interval,
   keeps track of the largest value seen so far and how we got
   there. Predicates on the assumption that DELAY creates one 
   full revolution for the bot. */
void spinAndFind() {
  float topAvg = 0;
  int howFar = 0, numIntervals = 10;
  Serial.println("SPIN AND FIND");
  
  // Find what direction had the greatest signal.
  for (int i = 0; i < numIntervals; i++) {
    motor.run(FORWARD);
    delay(DELAY / numIntervals);
    motor.run(RELEASE);
    
    setVals();
    float currentAvg = (spectrumVals[0] + spectrumVals[1]) / 2;
    if (currentAvg > topAvg) {
      topAvg = currentAvg;
      howFar = i;
    }
  }

  // Go back to the direction of the greatest signal.
  motor.run(FORWARD);
  // 0 <= (howFar / numIntervals) <= 1
  // A fraction specifying how much delay we want (ex 3 / 10);
  delay(DELAY * (howFar / numIntervals));
  motor.run(RELEASE);
}

/*
void spinAndFind()
{
  //stops car
   digitalWrite(rightMotorPin, LOW);
   digitalWrite(leftMotorPin, LOW);

   double highest = 0; //highest frequencey found
   
   unsigned long start = millis();
   unsigned long timeToSpin = 0;

   
   digitalWrite(rightMotorPin, HIGH);
   for (int i = 0; i < 7; i++)
   {
    if (spectrumValue[i] > highest) {
      highest = spectrumValue[i]  
      timeToSpin = millis();  
      }
   }

   long spin = start - timeToStart;
   while (spin >= 0) 
   {
       digitalWrite(rightMotorPin, HIGH);
       spin = spin - 1;
   }
   
   digitalWrite(rightMotorPin, LOW);
   digitalWrite(leftMotorPin, LOW);
   loop()
   }
*/

