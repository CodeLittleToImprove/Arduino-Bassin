# include  <LiquidCrystal.h>

const int ledGreen = 6;
const int rs = 7;
const int enable = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;


int controlValue;
int potentiometer = A0;

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);


void setup() {
  Serial.begin(9600);
  pinMode(ledGreen, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Brightness level inc");
}

void loop() {
  controlValue = analogRead(potentiometer);

  // Clamp to expected range
  controlValue = constrain(controlValue, 335, 390);

  // Map to 1 - 100
  int brightness = map(controlValue, 335, 390, 1, 100);

  // Scale to 0 - 255 for analogWrite
  int pwmValue = map(brightness, 1, 100, 0, 255);
  analogWrite(ledGreen, pwmValue);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(brightness);

  // Debug output
  Serial.print("Potentiometer: ");
  Serial.print(controlValue);
  Serial.print(" -> Helligkeit: ");
  Serial.print(brightness);
  Serial.print(" -> PWM: ");
  Serial.println(pwmValue);

  delay(250);
}
