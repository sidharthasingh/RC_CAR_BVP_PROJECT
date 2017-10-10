#include<Servo.h>
#include<SoftwareSerial.h>

#define SERVO_PIN 10 // The digital pin to which the Servo is attached
#define BT_PIN1 2 // The digital pin to which the HC05 TX module is connected - TX
#define BT_PIN2 3 // The digital pin to which the HC05 RX module is connected - RX

/* The global variable that have been defined for the whole code*/
int throttle; // Decides the speed of the motors
SoftwareSerial BT(BT_PIN1, BT_PIN2); // The BT object. A reference to the HC05 Serial module
int dir; // The direction in which the car has to move (The angles for the servo)
unsigned char val_received;

void refresh(); // This function re-syncs the global values to the whole system

void setup() {
  Serial.begin(9600);
  Serial.println("Setup() called");
  Serial.println("Setup() end");
}

void loop() {
  if(BT.available())
  {
     val_received = BT.read();
     Serial.println("Value received : "+val_received);
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
