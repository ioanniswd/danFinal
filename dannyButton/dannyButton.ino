/* 
  Date: 12 Jan 2017

  Danny's project
  
  Rotating when button is pressed.
  Stops when fully closed or button is pressed again.

*/

#include <Servo.h>

Servo myservo;

int button = 7;

int servopin = 9;

int buttonState = 0;

int angle = 0;

void setup() {
  
  // setting pin for button
  pinMode(button, INPUT);
  
  // attach pin to servo
  myservo.attach(servopin);
  
  myservo.write(angle);
  
  Serial.begin(9600);
}

void loop() {
  
  if(angle == 180) {
    // rotating the servo back to starting point, closing hand
   for(angle = 180; angle > 0; angle--) {
   
     // syntax: servo.write(angle). Rotate servo to the angle specified
     myservo.write(angle);
     
     // delay to give servo enough time to rotate
     delay(50);
   
   }
  }
  
  // read state of button pin
  buttonState = digitalRead(button);
  
  Serial.println(buttonState);
  
  // check if button is pressed
  if(buttonState == 1) {
    
    angle++;
    myservo.write(angle);
    delay(30);
  }
  
}
