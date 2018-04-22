int analogPin = 0; // read from multiplexer using analog input 0
int strobePin = 2; // strobe is attached to digital pin 2
int resetPin = 3; // reset is attached to digital pin 3
int rightMotorPin = 4 //pin number for the right motor
int leftMotorPin = 5 //pin number for the left motor
int spectrumValue[7]; // to hold a2d values

void setup()
{
 Serial.begin(9600);
 pinMode(analogPin, INPUT);
 pinMode(strobePin, OUTPUT);
 pinMode(resetPin, OUTPUT);
 pinMode(rightMotorPin, OUTPUT);
 pinMode(leftMotorPin, OUTPUT);
 analogReference(DEFAULT);

 digitalWrite(resetPin, LOW);
 digitalWrite(strobePin, HIGH);
}

void loop()
{
 digitalWrite(resetPin, HIGH);
 digitalWrite(resetPin, LOW);

 //the car starts to move
 digitalWrite(rightMotorPin, HIGH);
 digitalWrite(leftMotorPin, HIGH);
 

 for (int i = 0; i < 7; i++)
 {
   digitalWrite(strobePin, LOW);
   delayMicroseconds(30); // to allow the output to settle
   spectrumValue[i] = (5.0 / 1023.0) * analogRead(analogPin);
  
   Serial.print(i);
   Serial.print(":");
   Serial.print(spectrumValue[i] * (5.0 / 1023.0));
   Serial.print(" ");
    }

 //checks to see if any of the values are in the frequencey range
for (int i : spectrumValue) {
  //replace with real values
  if (i > 1 && i < 5) {
    spinAndFind();
  }

  digitalWrite(strobePin, HIGH);
  }
  Serial.println();
}

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
    if (spectrunValue[i] > highest) {
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

}

