#include "SoftwareSerial.h"    // подключаем библиотеку

#define ZERO_LVL_SPEED 127

#define COD_FOR_FORWARD 'F'
#define COD_FOR_REVERSE 'R'
#define COD_FOR_STOP 'S'
#define COD_FOR_IDLING 'I'

SoftwareSerial mySerial(2,3);  // указываем пины tx и rx
class Motor{
   private:
    byte portIn1;
    byte portIn2;
    byte speed=128;
    const byte nullSpeed=LOW, highSpeed=255;
    byte* valueOnPortIn1 = &nullSpeed;
    byte* valueOnPortIn2 = &nullSpeed;
   public:
   void Init(byte portIn1, byte portIn2){
      this -> portIn1 = portIn1;
      this -> portIn2 = portIn2;
   }
   void setup(){
      pinMode(portIn1, OUTPUT);
      pinMode(portIn2, OUTPUT); 
   }
   void SetSpeed(byte speed){
    this -> speed = speed;
   }
   void Stop(){
     valueOnPortIn1 = &nullSpeed;
     valueOnPortIn2 = &nullSpeed;
   }
   void ForwardStroke(){
    valueOnPortIn1 = &speed;
    valueOnPortIn2 = &nullSpeed;
   }
   void BackwardStroke(){
    valueOnPortIn1 = &nullSpeed;
    valueOnPortIn2 = &speed;
   }
   void Idling(){
    valueOnPortIn1 = &highSpeed;
    valueOnPortIn2 = &highSpeed;
   }
   void Realise(){
     analogWrite(portIn1, valueOnPortIn1);
     analogWrite(portIn2, valueOnPortIn2);
   }
};
class Motors{
  private:
    Motor left, right;
    
    byte speed=128;
    
    double reduceOnLeft=1.0;
    double reduceOnRight=1.0;
    
   public:
    //void (Motors::*RotationState)() = &Motors::Stop;
    Motors(byte portIn1,byte portIn2, byte portIn3, byte portIn4){
      left.Init(portIn1, portIn2);
      right.Init(portIn3, portIn4);
    }
    void setup(){
        left.setup();
        right.setup();
    }
    void SetTurn(int percent){
      if (percent != 50){
        reduceOnLeft = (((int)percent/50 == 1)? ((75 - percent)/25.0):1.0);
        reduceOnRight = (((int)percent/50 != 1)? ((percent - 25)/25.0):1.0);
      } else {
        reduceOnLeft = 1.0;
        reduceOnRight = 1.0;
      }
    }
    void SetSpeed(byte speed){
      this -> speed = ((float)speed) * 1.28;
    }
    
    void FowardStroke(){
       valueOnPortIn1 = ZERO_LVL_SPEED + speed*reduceOnLeft;
       valueOnPortIn2 = ZERO_LVL_SPEED - speed*reduceOnLeft;
       valueOnPortIn3 = ZERO_LVL_SPEED + speed*reduceOnRight;
       valueOnPortIn4 = ZERO_LVL_SPEED - speed*reduceOnRight;
    }
    void ReverseStroke(){
       valueOnPortIn1 = ZERO_LVL_SPEED - speed*reduceOnLeft;
       valueOnPortIn2 = ZERO_LVL_SPEED + speed*reduceOnLeft;
       valueOnPortIn3 = ZERO_LVL_SPEED - speed*reduceOnRight;
       valueOnPortIn4 = ZERO_LVL_SPEED + speed*reduceOnRight;
    }
    void Stop(){
       valueOnPortIn1 = HIGH;
       valueOnPortIn2 = HIGH;
       valueOnPortIn3 = HIGH;
       valueOnPortIn4 = HIGH;
    }
    void Idling(){
       valueOnPortIn1 = LOW;
       valueOnPortIn2 = LOW;
       valueOnPortIn3 = LOW;
       valueOnPortIn4 = LOW;
    }

    void Realise(){
      analogWrite(portIn1, valueOnPortIn1);
      analogWrite(portIn2, valueOnPortIn2);
      analogWrite(portIn3, valueOnPortIn3);
      analogWrite(portIn4, valueOnPortIn4);
    }
};
Motors motors(11, 10, 6, 5);
void setup() {
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  
  Serial.begin(9600);    // включаем hardware-порт
  mySerial.begin(9600);  // включаем software-порт
  motors.setup();
  Serial.println("start setting");
}

void loop() {
    static char c='N';
    if (mySerial.available()){
        c = mySerial.read();
        Serial.println(c);
        if(c == 'F'){
          int input_speed;
          input_speed = mySerial.parseInt();
          int input_angle;
          input_angle = mySerial.parseInt();
          motors.SetTurn(input_angle);
          motors.SetSpeed(input_speed);
          Serial.println(input_speed);
          motors.FowardStroke();
        }
        else if(c == 'A'){
          int input_angle;
          input_angle = mySerial.parseInt();
          motors.SetTurn(input_angle);
          Serial.println(input_angle);
        }
        else if(c == 'B'){
          int input_speed;
          input_speed = mySerial.parseInt();
          int input_angle;
          input_angle = mySerial.parseInt();
          motors.SetTurn(input_angle);
          motors.SetSpeed(input_speed);
          motors.ReverseStroke();
        }
        else if(c == 'I'){
          motors.Idling();
        }
        else if(c == 'S'){
          int input_speed;
          input_speed = mySerial.parseInt();
          motors.SetTurn(input_angle);
        }
        /*while(mySerial.available()){
          Serial.println(mySerial.parseInt());
        }
        //Serial.print((char)'\n');// пишем в hardware-порт
        if(c == 'F'){
          char str[4] = {};
          //Serial.print(mySerial.read());
          int size_str=0;
          while((str[size_str] = Serial.read()) != '\n' && size_str < 3) size_str++;
          str[size_str] = '\0';
          Serial.print(str);
        }*/
    }
    /*if (Serial.available()) {
        char c = Serial.read();      // читаем из hardware-порта
        mySerial.write(c);            // пишем в software-порт
    }*/
    motors.Realise();
}
