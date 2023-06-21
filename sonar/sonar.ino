const int leftSonarTrigPin = 10;
const int leftSonarEchoPin = 11;

const int rightSonarTrigPin = 12;
const int rightSonarEchoPin = 13;

// defines variables
long durationL, durationR;
int distanceL, distanceR;
void setup() {
  pinMode(leftSonarTrigPin, OUTPUT); 
  pinMode(leftSonarEchoPin, INPUT); 
  pinMode(rightSonarTrigPin, OUTPUT); 
  pinMode(rightSonarEchoPin, INPUT); 
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // Clears the trigPin
  digitalWrite(leftSonarTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(leftSonarTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(leftSonarTrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationL = pulseIn(leftSonarEchoPin, HIGH);
  // Calculating the distance
  distanceL = durationL * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance L: ");
  Serial.println(distanceL);

// Ardutidu
// Clears the trigPin
  digitalWrite(rightSonarTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(rightSonarTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightSonarTrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationR = pulseIn(rightSonarEchoPin, HIGH);
  // Calculating the distance
  distanceR = durationR * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance R: ");
  Serial.println(distanceR);  

}