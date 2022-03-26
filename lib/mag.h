// #include <MadgwickAHRS.h>
#include <Wire.h>
#include <DFRobot_QMC5883.h>
#include <Servo.h>
// Servo myservo;
// const int motor11 = 2;
// const int motor12 = 3;
// const int motor21 = 6;
// const int motor22 = 5;
// const int pinA = 7;
// const int pinB = 8;
// const int SV_PIN = 9;
// const int PWM = A5;
int minX = 0;
int maxX = 0;
int minY = 0;
int maxY = 0;
int offX = 0;
int offY = 0;
int i = 0;

DFRobot_QMC5883 compass;

// void setup_servo() {
//   myservo.attach(SV_PIN, 500, 2400);  // サーボの割当(パルス幅500~2400msに指定)
// }

void setup_qmc5883() {
  compass.begin();
  if (compass.isQMC()) {
    compass.setRange(QMC5883_RANGE_2GA);
    compass.setMeasurementMode(QMC5883_CONTINOUS);
    compass.setDataRate(QMC5883_DATARATE_50HZ);
    compass.setSamples(QMC5883_SAMPLES_8);
  }
}

int qmc5883() {
  double X = 0;
  double Y = 0;
  for (int i = 0; i < 5; i++) {
    Vector mag = compass.readRaw();
    X += mag.XAxis * 0.000105862 + 0.319926492;
    Y += mag.YAxis * 0.000113317 - 0.21266429 + 0.0000000000000001;
  }
  int theta;
  theta =  atan2 ( Y, X ) * 57.2958;
  return theta;
}

// void setup_motor() {
//   pinMode(motor11, OUTPUT);
//   pinMode(motor12, OUTPUT);
//   pinMode(motor21, OUTPUT);
//   pinMode(motor22, OUTPUT);
//   pinMode (pinA, INPUT);
//   pinMode (pinB, INPUT);
//   Serial.println("setup done");
// }

void right_rotate( int kakudo ) {
  unsigned long microt = 0;
  microt = millis();
  int theta0 = qmc5883();
  int theta = theta0;
  analogWrite( PWM, 249 );
  digitalWrite(motor11, HIGH);
  digitalWrite(motor22, LOW);
  digitalWrite(motor12, LOW);
  digitalWrite(motor21, HIGH);
  Serial.println("motor done");

  while (theta - theta0 < kakudo) {
    if (qmc5883() < theta0) {
      theta = qmc5883() + 360;
      Serial.println(theta);
    }
    else {
      theta = qmc5883();
      Serial.println(theta);
    }
  }
  digitalWrite(motor11, LOW);
  digitalWrite(motor21, LOW);
  double omega = (theta - theta0) / microt;
  theta = qmc5883();
  int difference = theta - theta0 - kakudo;
  int t = difference / omega;

  while (abs(theta - theta0 - kakudo) > 5) {

    if ( theta - theta0 - kakudo > 0) {
      digitalWrite(motor11, LOW);
      digitalWrite(motor22, HIGH);
      digitalWrite(motor12, HIGH);
      digitalWrite(motor21, LOW);
      analogWrite( PWM, 249 );
      delay(t);

      digitalWrite(motor12, LOW);
      digitalWrite(motor22, LOW);
    }
    else {
      digitalWrite(motor11, HIGH);
      digitalWrite(motor22, LOW);
      digitalWrite(motor12, LOW);
      digitalWrite(motor21, HIGH);
      analogWrite( PWM, 249 );
      delay(t);

      digitalWrite(motor11, LOW);
      digitalWrite(motor21, LOW);

    }
  }
}

void left_rotate( int kakudo ) {
  int theta0 = qmc5883();
  int theta = theta0;
  unsigned long microt = 0;
  microt = millis();

  digitalWrite(motor11, LOW);
  digitalWrite(motor22, HIGH);
  digitalWrite(motor12, HIGH);
  digitalWrite(motor21, LOW);
  analogWrite( PWM, 249 );
  while (theta0 - theta < kakudo) {
    if (qmc5883() > theta0) {
      theta = qmc5883() - 360;
    }
    else {
      theta = qmc5883();
    }
  }
  digitalWrite(motor12, LOW);
  digitalWrite(motor22, LOW);


  while (abs(theta - theta0 - kakudo) > 5) {
    double omega = (theta - theta0) / microt;
    theta = qmc5883();
    int difference = theta - theta0 - kakudo;
    int t = difference / omega;
    if ( theta - theta0 - kakudo > 0) {
      digitalWrite(motor11, LOW);
      digitalWrite(motor22, HIGH);
      digitalWrite(motor12, HIGH);
      digitalWrite(motor21, LOW);
      analogWrite(PWM, 249);
      delay(t);

      digitalWrite(motor12, LOW);
      digitalWrite(motor22, LOW);
    }
    else {
      digitalWrite(motor11, HIGH);
      digitalWrite(motor22, LOW);
      digitalWrite(motor12, LOW);
      digitalWrite(motor21, HIGH);
      analogWrite( PWM, 249 );
      delay(t);

      digitalWrite(motor11, LOW);
      digitalWrite(motor21, LOW);

    }
  }
}