// Definicje pinów czujników podczerwieni
// TODO
const int frontLeftSensorPin = A0;   // Pin dla lewego przedniego czujnika
const int frontRightSensorPin = A1;  // Pin dla prawego przedniego czujnika
// const int rearSensorPin = 4;        // Pin dla tylnego czujnika

// Definicje pinów sterujących silnikami
//bialy silnik
const int enL = 3;
const int leftMotorPin1 = 2;   // Pin 1 dla lewego silnika
const int leftMotorPin2 = 5;   // Pin 2 dla lewego silnika

const int enR = 6;
const int rightMotorPin1 = 7;  // Pin 1 dla prawego silnika
const int rightMotorPin2 = 4;  // Pin 2 dla prawego silnika

// Stałe prędkości silników
int baseSpeed = 220;     // Bazowa prędkość silników 127 + 20 delay
const int backSpeed = 255;     // Bazowa prędkość silników 127 + 20 delay
const int turnSpeed = 255;     // Prędkość podczas skrętu

bool wasLastTurnLeft = false;

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

void goBackward(int speed){
    setSpeedBoth(speed);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
}

void goForward(int speed){
    setSpeedBoth(speed);
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
}

void goLeft(int speed){
    wasLastTurnLeft = true;
    // goBackward(backSpeed);
    // delay(5);

    setSpeedBoth(speed);
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    delay(200);
}

void goRight(int speed){
    wasLastTurnLeft = false;

    // goBackward(backSpeed);
    // delay(5);

    setSpeedBoth(speed);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    delay(200);
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

  if (!isLine(frontLeftSensorValue) && !isLine(frontRightSensorValue)) {
      // if (gapCount == lineCount -1) gapCount += 1;

    // setSpeedBoth(baseSpeed);
    goForward(baseSpeed);
  }
  else if (isLine(frontLeftSensorValue) && !isLine(frontRightSensorValue)) {
    // Robot znajduje się na prawo od linii, skręt w lewo
    // setSpeedBoth(turnSpeed);
    goLeft(turnSpeed);
  }
  else if (!isLine(frontLeftSensorValue) && isLine(frontRightSensorValue)) {
    // Robot znajduje się na lewo od linii, skręt w prawo
    // setSpeedBoth(turnSpeed);
    goRight(turnSpeed);
  } else {
    if (wasLastTurnLeft) goLeft(turnSpeed);
    else goRight(turnSpeed);

    // if (lineCount == gapCount) lineCount += 1;
    // if (lineCount >= 4) {
    //   // goStop();
    //   baseSpeed = 0;
    // }
  }
}