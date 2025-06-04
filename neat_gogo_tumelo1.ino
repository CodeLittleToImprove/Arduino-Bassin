const int buttonPin = 2;
const int ledOne = 13;
const int ledTwo = 12;
const int ledThree = 8;
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
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);

  Serial.begin(9600);

  digitalWrite(ledThree, ledStateGreen);
}

void toggleGreenLed()
{
  ledStateGreen = !ledStateGreen;
  digitalWrite(ledThree, ledStateGreen);
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
    digitalWrite(ledOne, LOW);
    digitalWrite(ledTwo, LOW);
    return;
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval)
    {
      previousMillis = currentMillis;
      currentBlinkLedState = !currentBlinkLedState;
      digitalWrite(ledOne, currentBlinkLedState ? HIGH : LOW);
      digitalWrite(ledTwo, currentBlinkLedState ? HIGH : LOW);
    }
}
void loop()
{
  handleButton();
  handle_BlinkingLeds();
}
