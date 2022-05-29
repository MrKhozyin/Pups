#include <SoftwareSerial.h>
#define MOTORS_IN1 11
#define MOTORS_IN2 10
#define MOTORS_IN3 5
#define MOTORS_IN4 6
#define SPEED 255
#define ANGLE 1.0
//#define SERVO_PIN
//Servo servo;
byte outPutMotorIn1 = LOW;
byte outPutMotorIn2 = LOW;
byte outPutMotorIn3 = LOW;
byte outPutMotorIn4 = LOW;
SoftwareSerial mySerial(2, 3); // RX, TX
void setup() {
  // p  ut your setup code here, to run once:
  pinMode(MOTORS_IN1, OUTPUT);
  pinMode(MOTORS_IN2, OUTPUT);
  pinMode(MOTORS_IN3, OUTPUT);
  pinMode(MOTORS_IN4, OUTPUT);
  //  servo.attach(SERVO_PIN);
  mySerial.begin(9600);
  Serial.begin(9600);
}
char c;
void loop() {
  // put your main code here, to run repeatedly:

  if (mySerial.available()) {
    Serial.println(c);
    c = mySerial.read();
    if (c == 'F') {
      c = mySerial.read();
      outPutMotorIn1 = SPEED;
      outPutMotorIn2 = LOW;
      outPutMotorIn3 = SPEED;
      outPutMotorIn4 = LOW;
      //analogWrite(MOTORS_IN1, HIGH*SPEED+128;
      //analogWrite(MOTORS_IN2, LOW);
      //analogWrite(MOTORS_IN3, HIGH*SPEED+128;
      //analogWrite(MOTORS_IN4, LOW);
    } else if (c == 'B') {
      /*analogWrite(MOTORS_IN1, LOW);
        analogWrite(MOTORS_IN2, HIGH*SPEED);
        analogWrite(MOTORS_IN3, LOW);
        analogWrite(MOTORS_IN4, HIGH*SPEED);*/
      outPutMotorIn1 = LOW;
      outPutMotorIn2 = SPEED;
      outPutMotorIn3 = LOW;
      outPutMotorIn4 = SPEED;
    } else if (c == 'I') {
      /*analogWrite(MOTORS_IN1, LOW);
        analogWrite(MOTORS_IN2, LOW);
        analogWrite(MOTORS_IN3, LOW);
        analogWrite(MOTORS_IN4, LOW);*/
      outPutMotorIn1 = LOW;
      outPutMotorIn2 = LOW;
      outPutMotorIn3 = LOW;
      outPutMotorIn4 = LOW;
    } else if (c == 'S') {
      /*analogWrite(MOTORS_IN1, HIGH*SPEED);
        analogWrite(MOTORS_IN2, HIGH*SPEED);
        analogWrite(MOTORS_IN3, HIGH*SPEED);
        analogWrite(MOTORS_IN4, HIGH*SPEED);*/
      outPutMotorIn1 = HIGH;
      outPutMotorIn2 = HIGH;
      outPutMotorIn3 = HIGH;
      outPutMotorIn4 = HIGH;
    }
    /*else if(c == 'a'){
      servo.write(10);
      } else if(c == 'A') {
      servo.write(80);
      }*/
    analogWrite(MOTORS_IN1, outPutMotorIn1);
    analogWrite(MOTORS_IN2, outPutMotorIn2);
    analogWrite(MOTORS_IN3, outPutMotorIn3);
    analogWrite(MOTORS_IN4, outPutMotorIn4);
  }
}
