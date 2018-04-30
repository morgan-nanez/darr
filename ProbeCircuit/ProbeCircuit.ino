#include <AFMotor.h>
AF_DCMotor motor(2);

const int ledPin =  23; // the number of the LED pin
const int redLED = 22;

int analogPin = 7; // read from multiplexer using analog input 0
int strobePin = 52; // strobe is attached to digital pin 2
int resetPin = 53; // reset is attached to digital pin 3
float spectrumVals[2]; // two values we need
unsigned long DELAY = 3620, LEDDelay = 200;

void setup() {
  Serial.begin(9600);
  //pinMode(analogPin, INPUT);
  analogReference(DEFAULT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  

  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);

  motor.setSpeed(LEDDelay);
}

void loop() {
  // Blink twice
  //digitalWrite(ledPin, HIGH);
  //delay(LEDDelay);
  //digitalWrite(ledPin, LOW);
  //delay(LEDDelay);
  //digitalWrite(ledPin, HIGH);
  //delay(LEDDelay);
  //digitalWrite(ledPin, LOW);

  // Wait 1/2 second
  delay(500);
  
  spinAndFind();
  delay(7000);
}

void setVals() {

  // Blink red LED once
  //digitalWrite(redLED, HIGH);
  //delay(LEDDelay);
  //digitalWrite(redLED, LOW);

  // Wait 1/2 second
  
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
   
  
  for (int i = 0; i < 7; i++) {
    digitalWrite(strobePin, LOW);
    delayMicroseconds(30); // to allow the output to settle
    if (i == 2 || i == 3) {
      spectrumVals[i-2] = (5.0 / 1023.0) * analogRead(analogPin);
      Serial.println(spectrumVals[i-2]);
    }  
    digitalWrite(strobePin, HIGH);
  }
}

void spin_duration(int duration) {
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
  // Blink 3 times
  //digitalWrite(ledPin, HIGH);
  //delay(LEDDelay);
  //digitalWrite(ledPin, LOW);
  //delay(LEDDelay);
  //digitalWrite(ledPin, HIGH);
  //delay(LEDDelay);
  //digitalWrite(ledPin, LOW);
  //delay(LEDDelay);
  //digitalWrite(ledPin, HIGH);
  //delay(LEDDelay);
  //digitalWrite(ledPin, LOW);
  
  // Wait 1/2 second
  delay(500);
  float topAvg = -1;
  int howFar = 0, numIntervals = 10;
  Serial.println("SPIN AND FIND");
  
  // Find what direction had the greatest signal.
  for (int i = 0; i < numIntervals; i++) {
    motor.run(FORWARD);
    Serial.println(DELAY / numIntervals);
    delay(DELAY / numIntervals);
    motor.run(RELEASE);
    
    setVals();
    float currentAvg = (spectrumVals[0] + spectrumVals[1]) / 2;
    if (currentAvg > topAvg) {
      topAvg = currentAvg;
      howFar = i;
    }
  }
  delay(1000);

  // Go back to the direction of the greatest signal.
  motor.run(FORWARD);
  // 0 <= (howFar / numIntervals) <= 1
  // A fraction specifying how much delay we want (ex 3 / 10);
  delay(DELAY * (howFar / numIntervals));
  motor.run(RELEASE);
}

