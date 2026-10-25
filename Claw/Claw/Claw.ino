#include "arduino_secrets.h"

//Arduino #2
//Arduino for spool and claw mechanism

#include <AccelStepper.h>
#include <Servo.h>

//Declare the servo and the stepper on the spool
AccelStepper m_clawStepper;
Servo m_servo;

void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);

  //Setup for accelStepper to set speed and acceleration, needs both to work properly
  m_clawStepper.setMaxSpeed(640);
  m_clawStepper.setAcceleration(1000);

  //Pins for the button inputs
  pinMode(11, INPUT);
  pinMode(9, INPUT);

  //Setup for servo
  m_servo.attach(10);
  m_servo.write(120);
}

void loop() {
  //put your main code here, to run repeatedly:

  //If the red button is pressed, run blocking code that runs the sequence of grabbing something
  if(digitalRead(11)){
    m_clawStepper.runToNewPosition(-3600);
    delay(2000);
    m_servo.write(180);
    m_clawStepper.runToNewPosition(0);
  }
  //If the button is not pressed again and the sequence is finished, stop the stepper and set all the pins to low to prevent overheating
  else {
    m_clawStepper.stop();
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }

  //If the joystick is pressed down, open the claw
  if(!digitalRead(9)) {
    m_servo.write(120);
  }
}
