#include <LiquidCrystal.h>

const int ledGreen = 6;
const int rs = 7;
const int enable = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

int brightness = 0;
int pwmValue = 0;
String command;

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);


void setup()
{
  Serial.begin(9600);
  delay(250);
  pinMode(ledGreen, OUTPUT);

  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  // Serial.print("total:");
  // Serial.println(total);
}

void controlLed(int step)
{
  brightness += step;
  if (brightness < 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("value invalid:"); 
    brightness = 1;
  } 
  if (brightness >= 101)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("value invalid:"); 
    brightness = 100;
  }
  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("value not allowed:");
}

void loop()
{
 if (Serial.available())
 {
  command = Serial.readStringUntil('\n');
  command.trim();
  if (command.equalsIgnoreCase("brighter"))
  {
    lcd.clear();
    controlLed(10);
  }
  else if (command.equalsIgnoreCase("darker"))
  {
    lcd.clear();
    controlLed(-10);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("invalid cmd:");
  }
 }

 pwmValue = map(brightness, 1, 100, 0, 255);
 analogWrite(ledGreen, pwmValue);

 lcd.setCursor(0, 1);
 lcd.print("Brightness:");
 if (brightness == 0)
 {
    lcd.print(0);
    brightness++;
    return;
 }
 else
 {
    lcd.print(brightness);
    lcd.print("%   ");
 }

 delay(250);
}
