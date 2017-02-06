
/*
  Date: 12 Jan 2017

  Danny's project

  Controlled rotation of a servo according to pressure input from an fsr

*/

// include the libraries to control the servos
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// for ease, we declare and assign values for pins here


// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  550 // this is the 'maximum' pulse length count (out of 4096)
#define TOTALSERVO 2 // the number of servos used

// our servo # counter
uint8_t servonum = 0;

// fsr: force sensitive resistor
int fsr = A0;

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

  // initialize serial communication at 9600 bps(by convention)
  Serial.begin(9600);

  pinMode(button, INPUT);

  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();

}

void loop() {
  // loop code here

  int buttonState = digitalRead(button);

  if (buttonState == HIGH) {
    // initialize sensorValue to find mean of measurements
    sensorValue = 0;
    // rotating according to pressure


    // if you are not touching anything and hand is not closed
    uint16_t pulselen = SERVOMIN;
    while (sensorValue <= light && pulselen < SERVOMAX) {

      // keep closing hand
      pulselen++;
      for (servonum = 0; servonum < TOTALSERVO; servonum++) {
        pwm.setPWM(servonum, 0, pulselen);
        
      }

      sensorValue = analogRead(fsr);

      // print the value read
      Serial.println(sensorValue);

    }

    // pause for a fixed time set as variable pause
    delay(pause);

    for (pulselen; pulselen > SERVOMIN; pulselen--) {
      for (servonum = 0; servonum < TOTALSERVO; servonum++) {
        pwm.setPWM(servonum, 0, pulselen);
      }
    }

    delay(pause);
  }

}



