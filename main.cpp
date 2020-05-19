#include <Arduino.h>

int pirPin = 2;
int motorPin = 3;
int pirStat = 0, fullStat = 0, mediumStat = 0, bottomStat = 0;                                // status of the inputs
int rVoltage = 100;                                                          // (1) pull down resistors ...  Reference voltage
int full = 7, medium = 8, bottom = 9;                                                        // pins of the level indicator

unsigned int onTimeFull = 20;
unsigned int onTimeMedium = 20;
unsigned int onTimeBottom = 20;
unsigned int offTime = 2000;
unsigned int time[3] = {0, 0, 0}, normal_gap, Big_time;                           //(2)
int count;

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(full, INPUT);
  pinMode(medium, INPUT);
  pinMode(bottom, INPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  fullStat = analogRead(full);
  mediumStat = analogRead(medium); // Reads status of the pins and level indicators
  bottomStat = analogRead(bottom);
  pirStat = digitalRead(pirPin);

  for (count = 0; count < 3; count++)
  {
    if (pirStat == HIGH)
    {
      time[count] = millis();
			
      if (fullStat > rVoltage && mediumStat > rVoltage && bottomStat > rVoltage)
      {
        digitalWrite(motorPin, HIGH);
        delay(onTimeFull);                                                                // When bottle is full level
        Serial.println("Pumping at top level....");
        digitalWrite(motorPin, LOW);
      }

      if (fullStat < rVoltage && mediumStat > rVoltage && bottomStat > rVoltage)
      {
        digitalWrite(motorPin, HIGH);
        delay(onTimeMedium);                                                                  // When bottle is medium level
        Serial.println("Pumping at medium level.....");
        digitalWrite(motorPin, LOW);
      }

      if (fullStat < rVoltage && mediumStat < rVoltage && bottomStat > rVoltage)
      {
        digitalWrite(motorPin, HIGH);
        delay(onTimeBottom);                                                                // When bottle is bottom level
        Serial.println("Pumping at bottom level.....");
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



