
/*
  Date: 12 Jan 2017
  
  Danny's project

  Controlled rotation of a servo according to pressure input from an fsr
  
 */

// include the Servo library to control the motor
#include <Servo.h>
 
 // for ease, we declare and assign values for pins here
 
 // fsr: force sensitive resistor
 int fsr = A0;
 
 // the pin to be later assigned to the servo motor.
 // the library supports only two pins: 9 and 10
 int servoPin = 9;
 
 // create servo object from library Servo to control servo motor
 Servo myservo;
 
  // the variable to store the angle of the servo
  int angle = 10;
  
  // the current angle of servo
  int currAngle;

  // the variable to store the input from the fps
  double sensorValue;
   
  // the accuracy variable for the sensor measurements
  int accur = 5;
  
  // button to start sequence
  int button = 7;
  
  // fixed time to pause
  int pause = 1000;
  
  // maximum accepted pressure without stopping
  int light = 10;
  
  // fixed delay
  int time = 170;
   
 void setup() {
   // setup code
   
   // attach pin to servo object
   myservo.attach(servoPin);
   
   // set servo to starter position at 10 degrees
   myservo.write(angle);
   
   // delay to give enough time to complete
   delay(4000);
   
   // no need to pinMode analog in, it is input by defaul
   
   // the current angle
   currAngle = angle;
   
   pinMode(button, INPUT);
   
   
   // initialize serial communication at 9600 bps(by convention)
   Serial.begin(9600);
 }
 
 void loop() {
   // loop code here
   
   int i;
   
   currAngle = 10;
   
   int buttonState = digitalRead(button);
   
   if(buttonState == HIGH) {
     // initialize sensorValue to find mean of measurements
     sensorValue = 0;
     
     // rotating according to pressure
     
     // if you are not touching anything and hand is not closed
     while(sensorValue <= light && currAngle < 170) {
       
       // keep closing hand
       currAngle++;
       myservo.write(currAngle);
       
       delay(10);
       
       sensorValue = analogRead(fsr);
       
       // print the value read
       Serial.println(sensorValue);
       
     }
        
     // pause for a fixed time set as variable pause
     delay(pause);
     
     myservo.write(10);
     time = calcTime(currAngle);
     delay(time);
   }
      
 }
 
 int calcTime(int currAngle) {
   
   int result;
   
   result = (currAngle - 10) * 10;
   
   return result;
 }
 
 
 
