#include <Ultrasonic.h>

const int trig = 10;
const int echo = 11;
Ultrasonic sonar(trig, echo);

// Definicje pinów czujników podczerwieni
// TODO
const int frontLeftSensorPin = A0;   // Pin dla lewego przedniego czujnika
const int frontRightSensorPin = A1;  // Pin dla prawego przedniego czujnika

// Definicje pinów sterujących silnikami
//bialy silnik
const int enL = 3;
const int leftMotorPin1 = 2;   // Pin 1 dla lewego silnika
const int leftMotorPin2 = 5;   // Pin 2 dla lewego silnika

const int enR = 6;
const int rightMotorPin1 = 7;  // Pin 1 dla prawego silnika
const int rightMotorPin2 = 4;  // Pin 2 dla prawego silnika

// Stałe prędkości silników
int baseSpeed = 225;     // Bazowa prędkość silników 127 + 20 delay
const int turnSpeed = 255;     // Prędkość podczas skrętu

// Zmienne pomocnicze
unsigned long lineDetectedTime = 0;    // Czas wykrycia linii

int frontLeftSensorValue = 0;
int frontRightSensorValue = 0;

int lineCount = 0;
int gapCount = 0;


void setup() {
  // Inicjalizacja pinów czujników jako wejść
  pinMode(frontLeftSensorPin, INPUT);
  pinMode(frontRightSensorPin, INPUT);

  // Inicjalizacja pinów sterujących silnikami jako wyjść
  pinMode(enL, OUTPUT);
  pinMode(enR, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  delay(2000);
  Serial.begin(9600);
}

void setSpeedLeft(int speed){
  analogWrite(enL, speed);
}

void setSpeedRight(int speed){
  analogWrite(enR, speed);
}

void setSpeedBoth(int speed){
  analogWrite(enL, speed);
  analogWrite(enR, speed);
}

void goBackward(){
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
}

void goForward(){
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
}

void goLeft(){
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    delay(20);
}

void goRight(){
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(20);
}

void goStop() {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
}


bool isLine(int val) {
  return val > 400;
}


void log3() {
  Serial.print("lewy: ");
  Serial.println(frontLeftSensorValue);
  Serial.print("prawy: ");
  Serial.println(frontRightSensorValue);
  Serial.print(isLine(frontLeftSensorValue));
  Serial.print(" ");
  Serial.print(isLine(frontRightSensorValue));
  Serial.print(" ");
  Serial.println(!isLine(frontLeftSensorValue) && !isLine(frontRightSensorValue));
  Serial.print(" ");
  Serial.println(sonar.read());

  delay(500);
}

void logSensor(int sensor) {
  Serial.print("sensor: ");
  Serial.println(analogRead(sensor));
  delay(500);
}


void loop() {
  frontLeftSensorValue = analogRead(frontLeftSensorPin);
  frontRightSensorValue = analogRead(frontRightSensorPin);

  // logSensor(A2);
  // working more or less
  // if (isLine(frontLeftSensorValue) && isLine(frontRightSensorValue)) {
  //   // Robot znajduje się nad linią, jazda prosto
  //   if (lineCount == gapCount) lineCount += 1;
  //   if (lineCount >= 4) {
  //     // goStop();
  //     baseSpeed = 0;
  //   }
  // } else if(!isLine(frontLeftSensorValue) && !isLine(frontRightSensorValue)) {
  //   if (gapCount == lineCount -1) gapCount += 1;
  // }

  log3();

  // if (!isLine(frontLeftSensorValue) && !isLine(frontRightSensorValue)) {
  //   setSpeedBoth(baseSpeed);
  //   goForward();
  // }
  // else if (isLine(frontLeftSensorValue) && !isLine(frontRightSensorValue)) {
  //   // Robot znajduje się na prawo od linii, skręt w lewo
  //   setSpeedBoth(turnSpeed);
  //   goLeft();
  // }
  // else if (!isLine(frontLeftSensorValue) && isLine(frontRightSensorValue)) {
  //   // Robot znajduje się na lewo od linii, skręt w prawo
  //   setSpeedBoth(turnSpeed);
  //   goRight();
  // }
}