#include <Servo.h>
Servo ServoMain;
const int lightSensorM = A0;
const int lightSensorR = A1;
const int lightSensorL = A2;

int sensorValueM = 0;
int sensorValueL = 0;
int sensorValueR = 0;
int tresh = 50;

void setup()
{
  pinMode(lightSensorM, INPUT);
  pinMode(lightSensorL, INPUT);
  pinMode(lightSensorR, INPUT);
  ServoMain.attach(3);
  Serial.begin(9600);
}

void loop()
{

  sensorValueM = analogRead(lightSensorM);
  sensorValueL = analogRead(lightSensorL);
  sensorValueR = analogRead(lightSensorR);
  
  int averageLR = (sensorValueL + sensorValueR) / 2;
  int averageLM = (sensorValueL + sensorValueM) / 2;
  int averageRM = (sensorValueR + sensorValueM) / 2;




  int L = sensorValueL;
  int R = sensorValueR;
  int M = sensorValueM;
  


    if(L > M && L > R)
      ServoMain.write(180);
    /if(averageLM + tresh > M && averageLM + tresh > averageRM && averageLM + tresh > R && averageLM + tresh > averageLR && averageLM + tresh > L)
      ServoMain.write(135);
    if( M > averageRM && M > R  && M > averageLR && M > L && M > averageLM)
      ServoMain.write(90);
    if(averageRM + tresh > R && averageRM + tresh > averageRL && averageRM + tresh > L && averageRM + tresh > LM && averageRM + tresh > M)
      ServoMain.wriite(45);
    if(R > averageRL && R > L && R > averageLM && R > M & R > averageRM)
      ServoMain.write(0);
      //servo 0

  // Serial.print("Sensor middle:");
  // Serial.println(sensorValueM);
  // Serial.print("Sensor left:");
  // Serial.println(sensorValueL);
  // Serial.print("Sensor right:");
  // Serial.println(sensorValueR);
  
 
  // Serial.print("average LR:");
  // Serial.println(averageLR);
  // Serial.print("average LM:");
  // Serial.println(averageLM);
  // Serial.print("average RM:");
  // Serial.println(averageRM);
  delay(2000);
}

/*
Arduino Servo Test sketch
*/
// #include <Servo.h>
// Servo servoMain; // Define our Servo
// void setup()
// {
// servoMain.attach(3); // servo on digital pin 10
// }
// void loop()
// {
// servoMain.write(0); // Turn Servo Left to 45 degrees
// delay(3000); // Wait 1 second
// servoMain.write(45); // Turn Servo Left to 0 degrees
// delay(3000); // Wait 1 second
// servoMain.write(90); // Turn Servo back to center position (90 degrees)
// delay(3000); // Wait 1 second
// servoMain.write(135); // Turn Servo Right to 135 degrees
// delay(3000); // Wait 1 second
// servoMain.write(180); // Turn Servo Right to 180 degrees
// delay(3000); // Wait 1 second
// servoMain.write(90); // Turn Servo back to center position (90 degrees)
// delay(3000); // Wait 1 second
// }