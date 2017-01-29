/*
  Date: 13 Jan 2017
  
  Danny's project
  
  Pressing one button closes hand, pressing another opens the hand

*/

#include <Servo.h>

Servo myservo;

int openbtn = 7;

int closebtn = 5;

int servopin = 9;

int currangle = 0;


void setup() {
  pinMode(openbtn, INPUT);
  pinMode(closebtn, INPUT);
  
  myservo.attach(servopin);
  
  myservo.write(currangle);
  
  Serial.begin(9600);
  
}

void loop() {
  int openbtnState = digitalRead(openbtn);
  int closebtnState = digitalRead(closebtn);
  
  if(openbtnState == HIGH && closebtnState == HIGH) {
    Serial.println("Don't press both buttons at the same time");
  } else if(openbtnState == HIGH) {
    // open hand, if not fully open
    if(currangle < 180) {
      while(openbtnState == HIGH && currangle < 180) {
        currangle++;
        myservo.write(currangle);
        delay(40);
        // to open fully once pressed, comment the following line ------------------------
        openbtnState = digitalRead(openbtn);
      }
      Serial.println("The hand is now fully open");
    } else {
      Serial.println("The hand is already fully open");
    }
  } else if(closebtnState == HIGH) {
    // close hand, if not fully closed
    if(currangle > 0) {
      while(closebtnState == HIGH && currangle > 0) {
        currangle--;
        myservo.write(currangle);
        delay(40);
        // to close fully once pressed, comment the following line ------------------------
        closebtnState = digitalRead(closebtn);
      }
      Serial.println("The hand is now fully closed");
    }else {
      Serial.println("The hand is already fully closed");
    }
  }
}
