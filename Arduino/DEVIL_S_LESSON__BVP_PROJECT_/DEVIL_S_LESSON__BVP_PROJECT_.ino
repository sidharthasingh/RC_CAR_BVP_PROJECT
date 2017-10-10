#include<Servo.h>
#include<SoftwareSerial.h>

#define SERVO_PIN 10 // The digital pin to which the Servo is attached
#define BT_PINTX 4 // The digital pin to which the HC05 TX module is connected - TX
#define BT_PINRX 5 // The digital pin to which the HC05 RX module is connected - RX
#define BT_BAUD_RATE  115200 // The baud rate at which the HC05 module is operating. Default is 9600 (May be :-P)
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

SoftwareSerial BT(BT_PINTX, BT_PINRX); // The BT object. A reference to the HC05 Serial module
Servo serv; // This is the motor connected to the steering

void refresh(); // This function re-syncs the global values to the whole system

void setup() {
  Serial.begin(9600);
  Serial.println("Setup() called");

  serv.attach(SERVO_PIN);
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

void refresh()
{
  
}
