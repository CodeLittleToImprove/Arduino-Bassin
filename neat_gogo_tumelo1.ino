const int buttonPin = 2;
const int ledOne = 13;
const int ledTwo = 12;
const int ledThree = 8;

int		buttonState = HIGH; //default is 1
int		lastButtonState = HIGH; //default is 1
bool	ledStateGreen = true; // default turned on
bool	blinking = false;


void setup()
{
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  Serial.begin(9600);
  digitalWrite(ledThree, ledStateGreen);
}


void loop()
{
  buttonState = digitalRead(buttonPin);
  Serial.print("Button state: ");
  Serial.println(buttonState);
  
  if (lastButtonState == HIGH && buttonState == LOW) // detects change from 1 to 0
  {
    ledStateGreen = !ledStateGreen;
    digitalWrite(ledThree, ledStateGreen);
    Serial.print("Green LED is now ");
    Serial.println(ledStateGreen ? "ON" : "OFF");
    blinking = !ledStateGreen;
  }
  
  lastButtonState = buttonState;
  if (blinking)
  {
    digitalWrite(ledTwo, 1);
    digitalWrite(ledOne, 1);
    delay(500);
    digitalWrite(ledTwo, 0);
    digitalWrite(ledOne, 0);
    delay(500);
  }
}