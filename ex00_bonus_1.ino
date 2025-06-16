#include <LiquidCrystal.h>

const int ledGreen = 6;
const int rs = 7;
const int enable = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

const int stabilityWindow = 10;
const int initialReadings = 20;
const int fastReadings = 2;
const int maxReadings = 20;

int numReadings = initialReadings; 
int averageHistory[stabilityWindow];
int stabilityIndex = 0;
bool isReady = false;
int stabilityCounter = 0;
int potentiometer = A0;

int readings[maxReadings];
int readIndex = 0;
int total = 0;
int average = 0;
int lastDisplayValue = -1;

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);


void setup()
{
  Serial.begin(9600);
  delay(1000);
  pinMode(ledGreen, OUTPUT);

  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  int startValue = analogRead(potentiometer);
  startValue = constrain(startValue, 335, 390);
  for (int i = 0; i < initialReadings; i++)
  {
    readings[i] = startValue;
    total += readings[i];
    Serial.println(i);
  }
  // Serial.print("total:");
  // Serial.println(total);
}

void loop()
{
  total = total - readings[readIndex]; // delete oldest value
  Serial.print("total -:");
  Serial.println(total);
  readings[readIndex] = analogRead(potentiometer);
  readings[readIndex] = constrain(readings[readIndex], 335, 390);
  total = total + readings[readIndex]; // replace the oldest value
  // Serial.print("total +:");
  // Serial.println(total);

  readIndex = (readIndex + 1) % numReadings;
  average = total / numReadings;

  //Collect values for stabilizing
  averageHistory[stabilityIndex] = average;
  stabilityIndex = (stabilityIndex + 1) % stabilityWindow;

  if (!isReady)
  {
    int minVal = averageHistory[0];
    int maxVal = averageHistory[0];
    for (int i = 1; i < stabilityWindow; i++)
    {
      if (averageHistory[i] < minVal) minVal = averageHistory[i];
      if (averageHistory[i] > maxVal) maxVal = averageHistory[i];
    }
    if ((maxVal - minVal) <= 1)
    {
      stabilityCounter++;
      if (stabilityCounter >= 2)
      {
        isReady = true;
        lcd.clear();

        // switch to faster response
        numReadings = fastReadings;

        // reinitialize readings buffer
        total = 0;
        for (int i = 0; i < numReadings; i++)
        {
          readings[i] = average;
          total += readings[i];
        }
        readIndex = 0;
      }
    } else
    {
      stabilityCounter = 0;
    }
  }

  if (!isReady)
  {
    lcd.setCursor(0, 0);
    lcd.print("Calibrating"); 
    lcd.setCursor(0, 1);
    lcd.print("start value...     "); 
    // lcd.print("Loading...     "); 
    delay(250);
    return;
  }

  // after pendeling: normal display
  int brightness = map(average, 335, 390, 1, 100);
  int pwmValue = map(brightness, 1, 100, 0, 255);

  if (abs(average - lastDisplayValue) > 2)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Brightness:");
    lcd.print(brightness);
    lcd.print("%   ");
    analogWrite(ledGreen, pwmValue);
    lastDisplayValue = average;
  }

  delay(250);
}
