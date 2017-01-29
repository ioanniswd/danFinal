/*
  Date: 20 Jan 2017
  
  Danny's project
  
  Controlled rotation of 2 servos according to pressure input for 2 fsr
  The servos could be used independetly in the future, each controlled by its respective fsr

*/

// include the Servo library to control the motors
#include <Servo.h>
 
 // for ease, we declare and assign values for pins here
 
 // fsr: force sensitive resistor
 int fsr0 = A0;
 int fsr1 = A1;
 
 // the pins to be later assigned to the servo motors.
 // the library supports only two pins: 9 and 10
 int servoPin9 = 9;
 int servoPin10 = 10;
 
 // create servo objects from library Servo to control servo motors
 Servo myservo9;
 Servo myservo10;
 
  // the variable to store the angle of the servos
  // we use two different variables in case the servos move independently
  int angle9 = 10;
  int angle10 = 10;
  
  // the current angle of servo
  // we use two different variables in case the servos move independently
  int currAngle9;
  int currAngle10;

  // the variable to store the input from the fps
  double sensorValue0;
  double sensorValue1;
  
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
  
  // boolean for while loop
  boolean keepClosing = true;
  
  int closedAngle = 170;
  int openAngle = 10;
   
 void setup() {
   // setup code
   
   // attach pin to servo object
   myservo9.attach(servoPin9);
   myservo10.attach(servoPin10);
   
   // set servo to starter position at 10 degrees
   myservo9.write(angle9);
   myservo10.write(angle10);
   
   // delay to give enough time to complete
   delay(4000);
   
   // no need to pinMode analog in, it is input by defaul
   
   // the current angle
   currAngle9 = angle9;
   currAngle10 = angle10;
   
   pinMode(button, INPUT);
   
   
   // initialize serial communication at 9600 bps(by convention)
   Serial.begin(9600);
 }
 
 void loop() {
   // loop code here
   
   int i;
   
   currAngle10 = 10;
   currAngle9 = 10;
   
   int buttonState = digitalRead(button);
   
   if(buttonState == HIGH) {
     // initialize sensorValue to find mean of measurements
     sensorValue0 = 0;
     sensorValue1 = 0;
     
     // rotating according to pressure
     
     // if you are not touching anything and hand is not closed
     while(keepClosing) {
       
       // hand is open when servo is at 10 degrees and closed when servo is at 170 degrees
       if(sensorValue0 <= light && currAngle9 <= closedAngle) {
         // keep closing hand
         currAngle9++;
         myservo9.write(currAngle9);
       }
       
       // hand is open when servo is at 10 degrees and closed when servo is at 170 degrees
       if(sensorValue1 <= light && currAngle10 <= closedAngle) {
         // keep closing hand
         currAngle10++;
         myservo9.write(currAngle10);
       }
       
       delay(10);
       
       sensorValue0 = analogRead(fsr0);
       sensorValue1 - analogRead(fsr1);
       // print the value read
       Serial.println(sensorValue0);
       Serial.println(sensorValue1);
       
     }
        
     // pause for a fixed time set as variable pause
     delay(pause);
     
     myservo9.write(10);
     myservo10.write(10);
     int time9 = calcTime(currAngle9);
     int time10 = calcTime(currAngle10);
     time = (time9 > time10) ? time9 : time10;
     delay(time);
   }
      
 }
 
 int calcTime(int currAngle) {
   
   int result;
   
   result = (currAngle - 10) * 10;
   
   return result;
 }
