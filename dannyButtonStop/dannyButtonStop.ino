/*
  
  Date: 14 Jan 2017
  
  Danny's project
  
  Start's rotating at the push of the button and stops when another is pressed

*/


#include <Servo.h>

Servo myservo;

int servoPin = 9;

int angle = 10;

int btnStart = 7;

int btnStop = 5;

// boolean to see if you should run or not, pressing a button makes it true, pressing another makes it false
boolean run = false;

// boolean to check if hand is closing or opening
boolean closing = true;

void setup() {
  
  myservo.attach(servoPin);
  
  pinMode(btnStart, INPUT);
  pinMode(btnStop, INPUT);
  
  myservo.write(angle);
  
  delay(4000);
  
  Serial.begin(9600);
}

void loop() {
  
  int btnStartState = digitalRead(btnStart);
  int btnStopState = digitalRead(btnStop);
    
  if(btnStartState == HIGH && btnStopState == HIGH) {
    Serial.println("Do not press both buttons at the same time");
  }
  else
  {
    if(btnStopState == HIGH) {
      run = false;
    }
    
    if(btnStartState == HIGH) {
      run = true;
    }
    
    if(run) {
      
      Serial.println(angle);
      
      if(angle == 170) {
        closing = false;
        Serial.println("Now starting to open");
        delay(60);
      }
      
      if(angle == 10) {
        closing = true;
        Serial.println("Now starting to close");
        delay(60);
      }
      
      if(closing) {
        angle++;
      } else {
        angle--;
      }
      
      myservo.write(angle);
      
      delay(20);
      
      
    }
    
  }
  
  
}
