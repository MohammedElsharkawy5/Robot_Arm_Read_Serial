/* 6DOF  Manipulator
 serial code
 */

//used libraries
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h>
//#define MAXX 20  //20
//#define minn 135  //130
Servo myservo;  // create servo object to control a servo

//global variables
int   rec_data[12];

#define M1_Min_Limit -23950
#define M1_Max_Limit +23950
#define M2_Min_Limit -33480
#define M2_Max_Limit +14570
#define M3_Min_Limit -3720
#define M3_Max_Limit +52700
#define M4_Min_Limit -1270
#define M4_Max_Limit +1270
#define M5_Min_Limit -140
#define M5_Max_Limit 1043
#define M6_Min_Limit -1270
#define M6_Max_Limit 1270
//define motor pins
const int PUL1=24; //Motor 1 Pulse Pin
const int DIR1=30;//Motor  1  Direction Pin 
const int PUL2=25; //Motor 2 Pulse Pin
const int DIR2=31;//Motor  2  Direction Pin 
const int PUL3=26; //Motor 3 Pulse Pin
const int DIR3=32;//Motor  3  Direction Pin 
const int PUL4=4; //Motor  4 Pulse Pin
const int DIR4=7;//Motor   4  Direction Pin 
const int PUL5=3; //Motor  5 Pulse Pin
const int DIR5=6;//Motor   5  Direction Pin 
const int PUL6=2; //Motor  6 Pulse Pin
const int DIR6=5;//Motor   6  Direction Pin 
const int def_mots_speed[6]={1200,530,730,2000,1500,2000};

//define motor object
AccelStepper stepper1(AccelStepper::DRIVER, PUL1, DIR1);
AccelStepper stepper2(AccelStepper::DRIVER, PUL2, DIR2);
AccelStepper stepper3(AccelStepper::DRIVER, PUL3, DIR3);
AccelStepper stepper4(AccelStepper::DRIVER, PUL4, DIR4);
AccelStepper stepper5(AccelStepper::DRIVER, PUL5, DIR5);
AccelStepper stepper6(AccelStepper::DRIVER, PUL6, DIR6);

void setup() {
  
// define serial && user interface 
  Serial.begin(115200);

// Input&Output Pins
  pinMode (PUL1, OUTPUT);//Set Pulse Pin as Ouput
  pinMode (DIR1, OUTPUT);//Set Direction Pin as Ouput
  pinMode (PUL2, OUTPUT);//Set Pulse Pin as Ouput
  pinMode (DIR2, OUTPUT);//Set Direction Pin as Ouput
  pinMode (PUL3, OUTPUT);//Set Pulse Pin as Ouput
  pinMode (DIR3, OUTPUT);//Set Direction Pin as Ouput
  pinMode (PUL4, OUTPUT);//Set Pulse Pin as Ouput
  pinMode (DIR4, OUTPUT);//Set Direction Pin as Ouput
  pinMode (PUL5, OUTPUT);//Set Pulse Pin as Ouput
  pinMode (DIR5, OUTPUT);//Set Direction Pin as Ouput
  pinMode (PUL6, OUTPUT);//Set Pulse Pin as Ouput
  pinMode (DIR6, OUTPUT);//Set Direction Pin as Ouput

//initial parameters

    stepper1.setCurrentPosition(0);  // Set the current position as zero for now
    stepper1.setMaxSpeed(def_mots_speed[0]);
    stepper1.setAcceleration(2000.0);
    stepper1.setPinsInverted(true, false, false); 
 
    
    stepper2.setCurrentPosition(0);  // Set the current position as zero for now 
    stepper2.setMaxSpeed(def_mots_speed[1]);
    stepper2.setAcceleration(800.0);
    stepper2.runToNewPosition(-45*25);//3
    stepper2.setCurrentPosition(0);
    stepper2.runToNewPosition(45*25);
 
    
    stepper3.setCurrentPosition(0);  // Set the current position as zero for now
    stepper3.setMaxSpeed(def_mots_speed[2]);
    stepper3.setAcceleration(1400.0);
    stepper3.runToNewPosition(19*25);
    stepper3.setCurrentPosition(0);
    stepper3.runToNewPosition(-19*25);

   
    stepper4.setCurrentPosition(0);  // Set the current position as zero for now
    stepper4.setMaxSpeed(def_mots_speed[3]);
    stepper4.setAcceleration(1500.0);

    stepper5.setPinsInverted(true, false, false); 
    stepper5.setMaxSpeed(def_mots_speed[4]);
    stepper5.setAcceleration(1000.0);
    stepper5.runToNewPosition(15*6.67);
    stepper5.setCurrentPosition(0);
    stepper5.runToNewPosition(-15*6.67);
    
    stepper6.setCurrentPosition(0);  // Set the current position as zero for now
    stepper6.setMaxSpeed(def_mots_speed[5]);
    stepper6.setAcceleration(2200.0);
    

        myservo.attach(9);  // attaches the servo on pin 9 to the servo object
        myservo.write(20);              // tell servo to go to position in variable 'pos'
        delay(500);
        myservo.write(135);  
        delay(500); 
 //homing_cycle();
rec_data[0]=1;
rec_data[1]=1;
rec_data[2]=1;
rec_data[3]=1;
rec_data[4]=1;
rec_data[5]=1;
}

void loop() {

float speeds[6]={1,1,1,1,1,1};
//read serial and move motors depend on it
if(Serial.available() >= 5) {

    for(int i = 0; i < 6; i ++) {

        rec_data[i] = Serial.parseFloat();
    }
    Serial.flush();
       
}

    


   //motor 1    
  if(rec_data[0]!=1 ){
 if( rec_data[0]>=stepper1.currentPosition()) stepper1.moveTo(rec_data[0]);
 else if( rec_data[0]<stepper1.currentPosition()) stepper1.move(rec_data[0]-stepper1.currentPosition());
 stepper1.setSpeed(rec_data[6]);
}
  //motor 2     
  if(rec_data[1]!=1 ){
 if( rec_data[1]>=stepper2.currentPosition()) stepper2.moveTo(rec_data[1]);
 else if( rec_data[1]<stepper2.currentPosition())  stepper2.move(rec_data[1]-stepper2.currentPosition());
 stepper2.setSpeed(rec_data[7]);

}
   //motor 3    
  if(rec_data[2]!=1 ){
 if( rec_data[2]>=stepper3.currentPosition()) stepper3.moveTo(rec_data[2]);
 else if( rec_data[2]<stepper3.currentPosition()) stepper3.move(rec_data[2]-stepper3.currentPosition());
 stepper3.setSpeed(rec_data[8]);

}
//   //motor 4 
  if(rec_data[3]!=1){
 if( rec_data[3]>=stepper4.currentPosition()) stepper4.moveTo(rec_data[3]);
 else if( rec_data[3]<stepper4.currentPosition()) stepper4.move(rec_data[3]-stepper4.currentPosition());
 stepper4.setSpeed(rec_data[9]);
}
//   //motor 5
if(rec_data[4]!=1 ){
 if( rec_data[4]>=stepper5.currentPosition()) stepper5.moveTo(rec_data[4]);
 else if( rec_data[4]<stepper5.currentPosition()) stepper5.move(rec_data[4]-stepper5.currentPosition());
 stepper5.setSpeed(rec_data[10]);
}
//   //motor 6
if(rec_data[5]!=1  ){
 if( rec_data[5]>=stepper6.currentPosition()) stepper6.moveTo(rec_data[5]);
 else if( rec_data[5]<stepper6.currentPosition()) stepper6.move(rec_data[5]-stepper6.currentPosition());
 stepper6.setSpeed(rec_data[11]);
}
  {
   stepper1.runSpeedToPosition(); 
   stepper2.runSpeedToPosition();
   stepper3.runSpeedToPosition();
   stepper4.runSpeedToPosition();
   stepper5.runSpeedToPosition();
   stepper6.runSpeedToPosition();
  }


}
