#include <LiquidCrystal.h>

const int ledGreen = 6;
const int rs = 7;
const int enable = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

int startBrightness = 50;
int brightness = startBrightness;
String command;

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);
  pinMode(ledGreen, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Wait for cmd...");
}

void controlLed(int step)
{
  brightness += step;

  if (brightness < 1)
    brightness = 1;
  else if (brightness > 100)
    brightness = 100;

  lcd.clear();
  lcd.setCursor(0, 0);

  if (brightness == 1 && step < 0)
  {
    lcd.print("Min reached");
  } 
  else if (brightness == 100 && step > 0)
  {
    lcd.print("Max reached");
  } 
  else
  {
    lcd.print("Updated value");
  }
}

void loop()
{
  if (Serial.available())
  {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("brighter"))
    {
      controlLed(10);
    } 
    else if (command.equalsIgnoreCase("darker"))
    {
      controlLed(-10);
    } 
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Invalid command");
    }
  }

  int pwmValue = map(brightness, 1, 100, 0, 255);
  analogWrite(ledGreen, pwmValue);

  lcd.setCursor(0, 1);
  lcd.print("Brightness: ");
  lcd.print(brightness);
  lcd.print("%   ");

  delay(250);
}
