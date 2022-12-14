#ifndef Blower_h
#define Blower_h

#include "Arduino.h"
#include "util.h"


//ARDUINO CODE
//#define PIN_PWM1 9
//#define PIN_PWM2 10
#define PIN_PWM1 PB9
#define PIN_PWM2 PB8

float setPoint = 1;
//PI VALUES WITH PLUGGED HOLE and setpoint 1
//float Kp = 700;
//float Ki = 0.05;
float Kp = 100;
float Ki = 0.005;
float Kd = 20000;
float currentTime;
float previousTime;
float cumError;
float rateError;
float firstTime;
float error = 0;
void spinBlower(int b1, int b2){
  analogWrite(PIN_PWM1, b1);
  analogWrite(PIN_PWM2, b2);
}

void setupBlower(){
  PRINT1("Setting up blower");
  pinMode(PIN_PWM1, OUTPUT);
  pinMode(PIN_PWM2, OUTPUT);
  pinMode(PB15, OUTPUT);
  pinMode(PB4, OUTPUT);
  pinMode(PA8, INPUT);
  pinMode(PB5, INPUT);

  digitalWrite(PB15, HIGH);
  digitalWrite(PB4, HIGH);
  
  PRINT1("blower 1");
  spinBlower(255,0);
  delay(3000);
  PRINT1("blower 2");
  spinBlower(0,255);
  delay(3000);
  PRINT1("stop");
  spinBlower(0,0);
  PRINT1("done");
  firstTime = millis();
  float currentTime = millis() - firstTime;
  float previousTime = currentTime;
  float cumError = 0;
}
void updateSetPoint(float newSetPoint){
  setPoint = newSetPoint;
}
void loopBlower(float flow){
  flow *= -1;
  previousTime = currentTime;
  currentTime = millis() - firstTime;
  float elapsedTime = currentTime - previousTime;
  float lastError = error;
  error = setPoint - flow;
  cumError += error * elapsedTime;
  rateError = (error - lastError)/elapsedTime;
  float output = (Kp * error) + (Ki * cumError) + (Kd * rateError);
  
  if(output < 0){
    output = 0;
  }
  else if(output > 255){
    output = 255;
  }
  //Serial.println(setPoint);
  //PRINT4("output ", output, "prop. ", Kp*error);
  //PRINT4("int. ", Ki * cumError, "der. ", Kd * rateError);
  spinBlower(output,0);
}

void checkInput() {
  static String input = ""; // change to char[] to increase speed
  while (Serial.available()) {
    char c = Serial.read();
    input += c;
  }
  if(input != ""){
    setPoint = input.toFloat();
  }
  input = "";
}

#endif
