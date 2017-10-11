#include<Servo.h>
#include<SoftwareSerial.h>

#define SERVO_PIN 5 // The digital pin to which the Servo is attached
#define BT_PINTX 4 // The digital pin to which the HC05 TX module is connected - TX
#define BT_PINRX 5 // The digital pin to which the HC05 RX module is connected - RX
#define BT_BAUD_RATE  115200 // The baud rate at which the HC05 module is operating. Default is 9600 (May be :-P)
#define IN_1 = 6 ;
#define IN_2 = 7 ;


/*
  DIRECTIONAL LOGIC
  the 'dir' variable is for the direction being received
  values : Inference
  0 : Center / No touch / Straight
  1 : North
  2 : North-east
  3 : East
  4 : South-east
  5 : South
  6 : South-west
  7 : West
  8 : North-west
*/

/* The global variable that have been defined for the whole code*/
int throttle; // Decides the speed of the motors
int dir; // The direction in which the car has to move (The angles for the servo)
unsigned char val_received;
int SPEED = 0;

SoftwareSerial BT(BT_PINTX, BT_PINRX); // The BT object. A reference to the HC05 Serial module
Servo myservo; // This is the motor connected to the steering

void refresh(); // This function re-syncs the global values to the whole system

void setup() {
  Serial.begin(9600);
  Serial.println("Setup() called");

  myservo.attach(SERVO_PIN);
  BT.begin(BT_BAUD_RATE);
  
  Serial.println("Setup() end");
}

void loop() {
  if(BT.available())
  {
     val_received = BT.read();
     Serial.print("Value received : ");
     Serial.println(val_received);
     if(val_received>=0 && val_received<=8)
     {
        // Code for changing the direction;
        dir = val_received;
     }
     else if(val_received>=9 && val_received<=109)
     {
        // Code for changing the thrust
        // The received value is in range 9 - 109
        // To decipher it to a valid range of 0 - 100
        throttle = ((int)(val_received)) - 9; 
     }
     refresh(); // Called everytime when a value is received
  }
}

void stop();
void front();
void front_right();
void right();
void back_right();
void back();
void back_left();
void left();
void front_left();

void setDirections()
{
  switch(dir)
  {
    case 0:stop();break;
    case 1:front();break;
    case 2:front_right();break;
    case 3:right();break;
    case 4:back_right();break;
    case 5:back();break;
    case 6:back_left();break;
    case 7:left();break;
    case 8:front_left();break;
  }
}

void setSpeed()
{
  // Code to set the speed using the "val_received" variable
  SPEED = (throttle*255)/100;
}

void refresh()
{
  setSpeed();
  setDirections();
}

void stop(){
  myservo.write(90);
  digitalWrite(IN_1,LOW) ;
  digitalWrite(IN_2,LOW) ;
}

void front(){
  myservo.write(90);
  digitalWrite(IN_1,SPEED) ;
  digitalWrite(IN_2,LOW) ;
}

void front_right(){
  myservo.write(135);
  digitalWrite(IN_1,SPEED) ;
  digitalWrite(IN_2,LOW) ;
}

void right(){
  myservo.write(180);
  digitalWrite(IN_1,SPEED) ;
  digitalWrite(IN_2,LOW) ;
}

void back_right(){
  myservo.write(135);
  digitalWrite(IN_1,LOW) ;
  digitalWrite(IN_2,SPEED) ;
}

void back(){
  myservo.write(90);
  digitalWrite(IN_1,LOW) ;
  digitalWrite(IN_2,SPEED) ;
}

void back_left(){
  myservo.write(45);
  digitalWrite(IN_1,LOW) ;
  digitalWrite(IN_2,SPEED) ;
}

void left(){
  myservo.write(0);
  digitalWrite(IN_1,SPEED) ;
  digitalWrite(IN_2,LOW) ;
}

void front_left(){
  myservo.write(45);
  digitalWrite(IN_1,SPEED) ;
  digitalWrite(IN_2,LOW) ;
}