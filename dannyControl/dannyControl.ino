
/*
  Date: 12 Jan 2017
  
  Danny's project

  Controled rotation according to pressure input from fsr
  
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
 
  // the variable to store the angle of the servo
  int angle = 0;
  
  // the current angle of servo
  int currAngle;

  // the variable to store the input from the fps
  double sensorValue;
   
  // the accuracy variable for the sensor measurements
  int accur = 5;
  
  // button to start sequence
  int button = 7;
   
 void setup() {
   // setup code
   
   // attach pin to servo object
   myservo.attach(servoPin);
   
   // set servo to starter position at 0 degrees
   myservo.write(angle);
   
   // delay to give enough time to complete
   delay(4000);
   
   // no need to pinMode analog in, it is input by defaul
   
   // the current angle
   currAngle = 0;
   
   pinMode(button, INPUT);
   
   
   // initialize serial communication at 9600 bps(by convention)
   Serial.begin(9600);
 }
 
 void loop() {
   // loop code here
   
   int i;
   
   int buttonState = digitalRead(button);
   
   if(buttonState == HIGH) {
     // initialize sensorValue to find mean of measurements
     sensorValue = 0;
     
     for(i = 0; i < accur; i++) {
       // read input on analog pin 0
       sensorValue += analogRead(fps)/accur;
     }
     
     // print the value read
     Serial.println(sensorValue);
     
     // rotating according to pressure
     
     // if you are not touching anything and hand is not closed
     if(sensorValue == 0 && currAngle < 180) { // could be sensorValue < minPressure for accuracy
       
       // keep closing hand
       currAngle++;
       myservo.write(angle);
       
       // give enought time for motor
       delay(40);
       
     } else { // or if you are touching something
       
       // pause for a second
       delay(1000);
       
       // open hand
       for(angle = currAngle; angle > 0; angle--) {
         
         // syntax: servo.write(angle). Rotate servo to the angle specified
         myservo.write(angle);
         
         // delay to give servo enough time to rotate
         delay(20);
       }
     }
   }
   
     
      
 }
 
 
 
