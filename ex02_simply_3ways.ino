#include <Servo.h>
Servo ServoMain;

const int lightSensorM = A0;
const int lightSensorR = A1;
const int lightSensorL = A2;

int sensorValueM = 0;
int sensorValueL = 0;
int sensorValueR = 0;
int tresh = 100;  // Minimum difference to cause movement

void setup() {
  pinMode(lightSensorM, INPUT);
  pinMode(lightSensorL, INPUT);
  pinMode(lightSensorR, INPUT);
  ServoMain.attach(3);
  Serial.begin(9600);
}

void loop() {
  sensorValueM = analogRead(lightSensorM);
  sensorValueL = analogRead(lightSensorL);
  sensorValueR = analogRead(lightSensorR);


  Serial.print("L: "); Serial.print(sensorValueL);
  Serial.print(" M: "); Serial.print(sensorValueM);
  Serial.print(" R: "); Serial.println(sensorValueR);

  // Find the maximum light value
  int maxValue = max(sensorValueL, max(sensorValueM, sensorValueR));

  if (maxValue - sensorValueM < tresh && maxValue == sensorValueM) {
    ServoMain.write(90);  // Face south
  } else if (maxValue - sensorValueL < tresh && maxValue == sensorValueL) {
    ServoMain.write(180); // Face west
  } else if (maxValue - sensorValueR < tresh && maxValue == sensorValueR) {
    ServoMain.write(0);   // Face east
  }

  delay(2000);
}
