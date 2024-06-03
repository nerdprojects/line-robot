int buttonPin = A5;
int buttonValue = 1;

int potentiometerPin = A6;
int potentiometerValue = 0;

int sensorPinL = A2;
int sensorPinR = A3;
int sensorValueL = 0;
int sensorValueR = 0;
int sensorModePin = A0;
bool sensorModeWhiteOnBlack = true;

int motorPinL = 10;
int motorPinR = 11; 

int ledPin = 13;
bool ledPinState = 0;
unsigned long ledLastBlinkTime = 0;

bool doRun = false;
int speed = 0;

void setup() {
  for (int i = 2; i <= 9; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

  pinMode(potentiometerPin, INPUT);

  pinMode(sensorPinL, INPUT); 
  pinMode(sensorPinR, INPUT);
  
  pinMode(sensorModePin, INPUT);
  digitalWrite(sensorModePin, HIGH);

  pinMode(motorPinL, OUTPUT);
  pinMode(motorPinR, OUTPUT);
}

void loop() {
  potentiometerValue = analogRead(potentiometerPin);
  speed = potentiometerValue / 4;

  sensorModeWhiteOnBlack = digitalRead(sensorModePin);

  buttonValue = digitalRead(buttonPin);
  if (buttonValue == 0 ) {
    if (doRun) {
      doRun = false;
      stop();
      digitalWrite(ledPin, LOW);
      delay(500);
    } else {
      doRun = true;
      delay(500);
      forward();
    }
  }

  if (!doRun) {
    return;
  }

  blinkLed(speed);

  sensorValueL = digitalRead(sensorPinL);
  sensorValueR = digitalRead(sensorPinR);
  
  if (sensorModeWhiteOnBlack) {
    if (sensorValueL == 0 && sensorValueR == 1) {
      turnRight();
    }
    if (sensorValueL == 1 && sensorValueR == 0) {
      turnLeft();
    }
    if (sensorValueL == 1 && sensorValueR == 1) {
      forward();
    }
    if (sensorValueL == 0 && sensorValueR == 0) {
      stop();
    }
  } else {
    if (sensorValueL == 1 && sensorValueR == 0) {
      turnRight();
    }
    if (sensorValueL == 0 && sensorValueR == 1) {
      turnLeft();
    }
    if (sensorValueL == 0 && sensorValueR == 0) {
      forward();
    }
    if (sensorValueL == 1 && sensorValueR == 1) {
      stop();
    }
  }
}

void turnLeft() {
  analogWrite(motorPinL, 0);  
  analogWrite(motorPinR, speed);
}

void turnRight() {
  analogWrite(motorPinL, speed);
  analogWrite(motorPinR, 0);
}

void forward() {
  analogWrite(motorPinL, speed);  
  analogWrite(motorPinR, speed);
}

void stop() {
  analogWrite(motorPinL, 0);  
  analogWrite(motorPinR, 0);
}

void blinkLed(int speed) {
  int differenceToCheck = abs(speed - 255);
  if (millis() - ledLastBlinkTime > differenceToCheck) {
    digitalWrite(ledPin, ledPinState);
    ledPinState = !ledPinState;
    ledLastBlinkTime = millis();
  }
}