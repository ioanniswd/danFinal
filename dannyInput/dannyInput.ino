/* Date: 12 Jan 2017
  
  Danny's project
  
  Rotation by user input
  
*/


int input = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  
  if(Serial.available() > 0) { 
    
    // get input
    input = Serial.read();
    
    // note: [0, 180], (0, 180], [0, 180) or (0, 180)
    if(input > 1 && input < 179) {
      Serial.println(input, DEC);
    } else {
      Serial.println("Cannot accept value");
    }
    
    delay(2000);
    
  }
  
}
