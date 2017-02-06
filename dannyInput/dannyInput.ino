/* Date: 12 Jan 2017
  
  Danny's project
  
  Rotation by user input
  
*/


#include <Servo.h>

Servo myservo;

int input = 10;

int time = 2000;

int currAngle = 10;

void setup() {
  
  myservo.attach(9);
  
  myservo.write(currAngle);
  
  delay(time);
  
  Serial.begin(9600);
}

void loop() {
  
  
  if(Serial.available() > 0) {
    
    // get input
    input = Serial.parseInt();
    
    // note: [10, 170]
    if(input >= 10 && input <= 170) {
      Serial.print("Input is: ");
      Serial.print(input);
      Serial.println(" degrees");
      
      time = calcTime(currAngle);
      
      Serial.print("Delay is: ");
      Serial.print(time);
      Serial.println(" ms");
      
      delay(150);
      
      myservo.write(input);
      currAngle = input;
      delay(time);
      
    } else {
      Serial.println("Cannot accept value");
    }
    
  }
  
  
}

int calcTime(int currAngle) {
  int result;
 
  result = abs((currAngle - input) * 10);
  
  return result;
}
