#include <LiquidCrystal.h>

const int potentiometer = A0;
const int ledGreen = 6;
const int rs = 7;
const int enable = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

int pot_read = 0;


LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);
  delay(1000);
  pinMode(ledGreen, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop()
{
  pot_read = analogRead(potentiometer);
  Serial.println(pot_read);
  int pwmValue = map(pot_read, 0, 1000, 0, 255);
  int brightness = map(pwmValue, 0, 255, 0, 100);

  lcd.setCursor(0, 1);
  lcd.print("Brightness:");
  lcd.print(brightness);
  lcd.print("%   ");
  analogWrite(ledGreen, pwmValue);
}
