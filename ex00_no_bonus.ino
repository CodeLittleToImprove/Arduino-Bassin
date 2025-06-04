const int buttonPin = 2;
const int ledRed = 13;
const int ledYellow = 12;
const int ledGreen = 8;
const unsigned long blinkInterval = 500;

int		buttonState = HIGH; //default is 1
int		lastButtonState = HIGH; //default is 1
bool	ledStateGreen = true; // default turned on
bool	blinking = false;
bool currentBlinkLedState = LOW;
unsigned long previousMillis = 0;

void setup()
{
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  Serial.begin(9600);

  digitalWrite(ledGreen, ledStateGreen);
}

void toggleGreenLed()
{
  ledStateGreen = !ledStateGreen;
  digitalWrite(ledGreen, ledStateGreen);
  Serial.print("Green LED is now ");
  Serial.println(ledStateGreen ? "ON" : "OFF");

  blinking = !ledStateGreen;
}

void handleButton()
{
  buttonState = digitalRead(buttonPin);
  Serial.print("Button state: ");
  Serial.println(buttonState);

  if (lastButtonState == HIGH && buttonState == LOW) // detects change from 1 to 0
  {
    toggleGreenLed();
    delay(200);
  }
  lastButtonState = buttonState;

}
void handle_BlinkingLeds()
{
  if (!blinking)
  {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    return;
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval)
    {
      previousMillis = currentMillis;
      currentBlinkLedState = !currentBlinkLedState;
      digitalWrite(ledRed, currentBlinkLedState ? HIGH : LOW);
      digitalWrite(ledYellow, currentBlinkLedState ? HIGH : LOW);
    }
}
void loop()
{
  handleButton();
  handle_BlinkingLeds();
}
