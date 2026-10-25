#include "arduino_secrets.h"

//Arduino #1
//Arduino for controlling 2 dimensional motion with the joystick

#include <AccelStepper.h>

//Setup for steppers (defaults to a 4 wire stepper with pins on 2,3,4,5 if no information is called)
AccelStepper m_stepperY;
AccelStepper m_stepperX(AccelStepper::FULL4WIRE, 6, 7, 8, 9);

//On and Offs for running and not running in the x and y directions
bool runY = false;
bool runX = false;

void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);

  //Setup for the joystick inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  //Required for accelStepper to function properly when running at a constant speed
  m_stepperY.setMaxSpeed(10000);
  m_stepperX.setMaxSpeed(10000);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Get the joystick inputs and apply a deadband if they're below a certain threshold to prevent stuff from running on joystick drift
  int X = analogRead(A1);
  X = map(X, 0, 1023, -640, 640);
  if(X < 100 && X > -100) {X = 0;}

  int Y = analogRead(A0);
  Y = map(Y, 0, 1023, -640, 640);
  if(Y < 100 && Y > -100) {Y = 0;}


  //If the stepper is not running and they should be moving forward, set the speed to 640 and run the motors
  if(!runY && Y > 100) {
    m_stepperY.setSpeed(640);
    runY = true;
  }

  //If the stepper is not running and they should be moving backward, set the speed to -640 and run the motors
  if(!runY && Y < -100) {
    m_stepperY.setSpeed(-640);
    runY = true;
  }
  
  //If the motors should be running, run the motors, if not, stop the motors and turn the pins off to prevent overheating
  if(runY) {
    m_stepperY.runSpeed();
    //This keeps the motor running until the joytick returns to normal
    if(Y < 100 && Y > -100) {
      runY = false;
    }
  }
  else {
    m_stepperY.stop();
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }

  //If the stepper is not running and they should be moving forward, set the speed to 640 and run the motors
  if(!runX && X > 100) {
    m_stepperX.setSpeed(640);
    runX = true;
  }

  //If the stepper is not running and they should be moving backward, set the speed to -640 and run the motors
  if(!runX && X < -100) {
    m_stepperX.setSpeed(-640);
    runX = true;
  }
  
  //If the motors should be running, run the motors, if not, stop the motors and turn the pins off to prevent overheating
  if(runX) {
    m_stepperX.runSpeed();
    //This keeps the motor running until the joytick returns to normal
    if(X < 100 && X > -100) {
      runX = false;
    }
  }
  else {
    m_stepperX.stop();
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
}
