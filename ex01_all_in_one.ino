#include <LiquidCrystal.h>

const int potentiometer = A0;
const int ledGreen = 6;
const int rs = 7;
const int enable = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

int brightness = 50;
String command;
bool autoMode = true; // true = potentiometer control, false = manual command control

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);
  pinMode(ledGreen, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Manual mode");
  lcd.setCursor(0, 1);
  lcd.print("Loading...");
  delay(500);
  lcd.clear();
}

void controlLed(int step)
{
  brightness += step;
  if (brightness < 1) brightness = 1;
  if (brightness > 100) brightness = 100;

  lcd.clear();
  lcd.setCursor(0, 0);

  if (brightness == 1 && step < 0)
    lcd.print("Min reached");
  else if (brightness == 100 && step > 0)
    lcd.print("Max reached");
  else
    lcd.print("Updated value");
}

void loop()
{

  if (Serial.available())
  {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("brighter"))
    {
      if (!autoMode) controlLed(10);
    }
    else if (command.equalsIgnoreCase("darker"))
    {
      if (!autoMode) controlLed(-10);
    }
    else if (command.equalsIgnoreCase("manual"))
    {
      autoMode = false;
      brightness = 50;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Manual mode");
    }
    else if (command.equalsIgnoreCase("auto"))
    {
      autoMode = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Auto mode");
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Invalid command");
    }
  }

  if (autoMode)
  {
    int pot_read = analogRead(potentiometer);
    int pwmValue = map(pot_read, 0, 1000, 0, 255);
    brightness = map(pwmValue, 0, 255, 0, 100);
  }

  int pwmOut = map(brightness, 0, 100, 0, 255);
  analogWrite(ledGreen, pwmOut);

  lcd.setCursor(0, 1);
  lcd.print("Brightness: ");
  lcd.print(brightness);
  lcd.print("%   ");

  delay(250);
}
