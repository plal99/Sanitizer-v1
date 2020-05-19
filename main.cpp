#include <Arduino.h>
const int pirPin = 2;
const int motorPin = 3;
const int fullPin = 7, halfPin = 8, qtrPin = 9;                          // pins of the level indicator

int pirStat = 0, fullStat = 0, halfStat = 0, qtrStat = 0; // status of the inputs
int rVoltage = 100;   // (1) pull down resistors ...  Reference voltage

unsigned int onTimeFull = 20;
unsigned int onTimeHalf = 20;
unsigned int onTimeQtr = 20;
unsigned int offTime = 2000;
unsigned int time[3] = {0, 0, 0}, normal_gap, Big_time;  //(2)
int count;

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(fullPin, INPUT);
  pinMode(halfPin, INPUT);
  pinMode(qtrPin, INPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  fullStat = analogRead(fullPin);
  halfStat = analogRead(halfPin); // Reads status of the pins and level indicators
  qtrStat = analogRead(qtrPin);
  pirStat = digitalRead(pirPin);

  for (count = 0; count < 3; count++)
  {
    if (pirStat == HIGH)
    {
      time[count] = millis();
			
      if (fullStat > rVoltage && halfStat > rVoltage && qtrStat > rVoltage)
      {
        digitalWrite(motorPin, HIGH);
        delay(onTimeFull); // When bottle is full level
        Serial.println("Pumping at top level....");
        digitalWrite(motorPin, LOW);
      }

      if (fullStat < rVoltage && halfStat > rVoltage && qtrStat > rVoltage)
      {
        digitalWrite(motorPin, HIGH);
        delay(onTimeHalf); // When bottle is half level
        Serial.println("Pumping at half level.....");
        digitalWrite(motorPin, LOW);
      }

      if (fullStat < rVoltage && halfStat < rVoltage && qtrStat > rVoltage)
      {
        digitalWrite(motorPin, HIGH);
        delay(onTimeQtr); // When bottle is qtr level
        Serial.println("Pumping at qtr level.....");
        digitalWrite(motorPin, LOW);
      }

      Serial.println("Pumping over, delaying.....");
      delay(offTime);
    }

    else
    {
      digitalWrite(motorPin, LOW);
    }
  }

  if ((time[2] - time[0]) < normal_gap)
	delay(Big_time);
	
	for (int i=0;i<3;i++){
    time[i]=0;
  }
}



