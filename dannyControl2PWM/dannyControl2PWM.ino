/*
  Date: 20 Jan 2017

  Danny's project

  Controlled rotation of 2 servos according to pressure input for 2 fsr
  The servos could be used independetly in the future, each controlled by its respective fsr

*/

// include the libraries to control the servos
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


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

uint16_t pulselen0 = SERVOMIN;
uint16_t pulselen1 = SERVOMIN;

// for ease, we declare and assign values for pins here

// fsr: force sensitive resistor
int fsr0 = A0;
int fsr1 = A1;


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
int light = 100;

// fixed delay
int time = 170;

// boolean for while loop
boolean keepClosing = true;

void setup() {
  // setup code

  // delay to give enough time to complete
  delay(2000);

  // no need to pinMode analog in, it is input by default

  pinMode(button, INPUT);

  // initialize serial communication at 9600 bps(by convention)
  Serial.begin(9600);
}

void loop() {
  // loop code here

  int i;

  int buttonState = digitalRead(button);

  if (buttonState == HIGH) {


    // initialize sensorValue to find mean of measurements
    sensorValue0 = 0;
    sensorValue1 = 0;

    // rotating according to pressure

    // if you are not touching anything and hand is not closed
    while (keepClosing) {

      // hand is open when servo is at 10 degrees and closed when servo is at 170 degrees
      if (sensorValue0 <= light && pulselen0 <= SERVOMAX) {
        // keep closing hand
        servonum = 0;
        pulselen0++;
        pwm.setPWM(servonum, 0, pulselen0);
      }

      // hand is open when servo is at 10 degrees and closed when servo is at 170 degrees
      if (sensorValue1 <= light && pulselen1 <= SERVOMAX) {
        // keep closing hand
        servonum = 1;
        pulselen1++;
        pwm.setPWM(servonum, 0, pulselen1);
      }

      delay(10);

      sensorValue0 = analogRead(fsr0);
      sensorValue1 = analogRead(fsr1);
      // print the value read
      Serial.println(sensorValue0);
      Serial.println(sensorValue1);

      if (sensorValue0 > light || sensorValue1 > light || pulselen0 >= SERVOMAX || pulselen1 >= SERVOMAX) {
        keepClosing = false;
      }

    }

    // pause for a fixed time set as variable pause
    delay(pause);

    servonum = 0;
    for (pulselen0; pulselen0 > SERVOMIN; pulselen0--) {
      pwm.setPWM(servonum, 0, pulselen0);
    }

    servonum = 1;
    for (pulselen1; pulselen1 > SERVOMIN; pulselen1--) {
      pwm.setPWM(servonum, 0, pulselen1);
    }


    keepClosing = true;
    delay(500);
  }

}
