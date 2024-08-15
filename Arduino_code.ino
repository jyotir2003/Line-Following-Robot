#define MOTOR_SPEED 150

// IR sensor pin from left
int IRpin1 = A0;
int IRpin2 = A1;
int IRpin3 = A2;
int IRpin4 = A3;
int IRpin5 = A4;

//motor constants
// Motor right motor A connections
int enableRightMotor = 9;
int rightMotorPin1 = 8;
int rightMotorPin2 = 7;

// Motor left B connections
int enableLeftMotor = 4;
int leftMotorPin1 = 6;
int leftMotorPin2 = 5;
//motor constants

int time = 500;

void setup() {
  //ir
  pinMode(IRpin1, INPUT); // set IR pin as input
  pinMode(IRpin2, INPUT);
  pinMode(IRpin3, INPUT);
  pinMode(IRpin4, INPUT);
  pinMode(IRpin5, INPUT);

  Serial.begin(9600); // initialize serial communication

  TCCR0B = TCCR0B & B11111000 | B00000010;

  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  rotateMotor(0, 0);
}

void loop() {
  //ir
  int IRval1 = analogRead(IRpin1); // read IR sensor value
  int IRval2 = analogRead(IRpin2);
  int IRval3 = analogRead(IRpin3);
  int IRval4 = analogRead(IRpin4);
  int IRval5 = analogRead(IRpin5);
  //Serial.println(IRval3);

  //if middle sensor detects the black line...
  if (IRval3 > 400 || IRval2 > 400 || IRval4 > 400) {
    rotateMotor(-180, -180); // move straight
  } else if (IRval1 > 400) {
    rotateMotor(-200, -140); // move left
  } else if (IRval5 > 400) {
    rotateMotor(-140, -200); // move right
  } else {
    rotateMotor(0, 0); // stop moving
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));

  delay(time);
}
