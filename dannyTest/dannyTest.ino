
/*
  Date: 12 Jan 2017
  
  Dany's project

  Main test 
  Testing basics for input/output, the Servo library, the force
  pressure sensors
  
  The servo rotates slowly from 0 to 180 degrees and then returns to 0 degrees.
  The pressure to fps is printed on the screen
  
 */

// include the Servo library to control the motor
#include <Servo.h>
 
 // for ease, we declare and assign values for pins here
 
 // fps: force pressure sensor
 int fps = A0;
 
 // the pin to be later assigned to the servo motor.
 // the library supports only two pins: 9 and 10
 int servoPin = 9;
 
 // create servo object from library Servo to control servo motor
 Servo myservo;
 
 // the variable to store the input from the fps
   int sensorValue;
   
   // the variable to store the angle of the servo
   int angle = 0;
 
 
 void setup() {
   // setup code
   
   // no need to pinMode analog in, it is input by defaul
   
   // attach pin to servo object
   myservo.attach(servoPin);
   
   // set servo to starter position at 0 degrees
   myservo.write(angle);
   
   // delay to give enough time to complete
   delay(4000);
   
   // initialize serial communication at 9600 bps(by convention)
   Serial.begin(9600);
 }
 
 void loop() {
   // loop code here
   
   // read input on analog pin 0
   sensorValue = analogRead(fps);
   
   // print the value read
   Serial.println(sensorValue);
   
   // rotating the servo from 0 to 180, one degree at a time
   for(angle = 0; angle < 180; angle += 1) {
     
     // syntax: servo.write(angle). Rotate servo to the angle specified
     myservo.write(angle);
     
     // delay to give servo enough time to rotate
     delay(50);
   }
   
   // rotating the servo back to starting point, closing hand
   for(angle = 180; angle > 0; angle--) {
   
     // syntax: servo.write(angle). Rotate servo to the angle specified
     myservo.write(angle);
     
     // delay to give servo enough time to rotate
     delay(50);
   
   }
   
   delay(1000);
   
 }
 
 
 
