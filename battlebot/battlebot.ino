#include <Ultrasonic.h>
// Definicje pinów czujników podczerwieni
// TODO
const int frontLeftSensorPin = A0;   // Pin dla lewego przedniego czujnika
const int frontRightSensorPin = A1;  // Pin dla prawego przedniego czujnika
// TODO
// const int frontLeftSensorPin = A2;   // Pin dla lewego przedniego czujnika
// const int frontRightSensorPin = A3;  // Pin dla prawego przedniego czujnika

const int trig = 10;
const int echo = 11;

Ultrasonic sonar(trig, echo);

// Definicje pinów sterujących silnikami
//bialy silnik
const int enL = 3;
const int leftMotorPin1 = 2;   // Pin 1 dla lewego silnika
const int leftMotorPin2 = 5;   // Pin 2 dla lewego silnika

const int enR = 6;
const int rightMotorPin2 = 8;  // Pin 1 dla prawego silnika
const int rightMotorPin1 = 4;  // Pin 2 dla prawego silnika

// Stałe prędkości silników
int baseSpeed = 255;     // Bazowa prędkość silników 127 + 20 delay
const int backSpeed = 255;     // Bazowa prędkość silników 127 + 20 delay
const int turnSpeed = 255;     // Prędkość podczas skrętu

// Zmienne pomocnicze
unsigned long lineDetectedTime = 0;    // Czas wykrycia linii

int frontLeftSensorValue = 0;
int frontRightSensorValue = 0;
int backLeftSensorValue = 0;
int backRightSensorValue = 0;
int sonarValue = 0;

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
  pinMode(LED_BUILTIN, OUTPUT);

  delay(1000);

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

void goBackward(int speed, int ms = 0){
    setSpeedBoth(speed);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    delay(ms);
}

void goForward(int speed, int ms = 0){
    setSpeedBoth(speed);
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(ms);
}

void goLeft(int speed, int ms = 60){
    // goBackward(backSpeed);
    // delay(5);
    setSpeedBoth(speed);
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    delay(ms);
}

void goRight(int speed, int ms = 60){
    // goBackward(backSpeed);
    // delay(5);
    setSpeedBoth(speed);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(ms);
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

void loop() {
  frontLeftSensorValue = analogRead(frontLeftSensorPin);
  frontRightSensorValue = analogRead(frontRightSensorPin);
  sonarValue = (int)(sonar.read() +sonar.read()+sonar.read()+sonar.read() )/4;



  if (sonarValue > 20) {
    goLeft(baseSpeed);

  }
  else {
    if (isLine(frontLeftSensorValue)) {
      goRight(255, 400);
    }
    else if (isLine(frontRightSensorValue)) {
      goLeft(255, 400);
    }
    else if(isLine(frontRightSensorValue) && isLine(frontLeftSensorValue)) {
      goBackward(baseSpeed);
    } else {
      goForward(baseSpeed);
    }
  }
}