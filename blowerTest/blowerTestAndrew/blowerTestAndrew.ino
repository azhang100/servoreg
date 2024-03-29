#include "Arduino.h"
#include "blower.h"
#include "util.h"
#include "flow.h"
#include "sweep.h"

float sweepNew = 1; 
  
void setup() {
  delay(1000);
  setupUtil();
  //Wire.begin();
  setupBlower();
  delay(1000);
  delay(1000);
  setupFlow();
  delay(1000);
  delay(1000);
  setupSweep();
  delay(1000);
  delay(1000);
}

void loop() {
  float flow = loopFlow();
  checkInput();
  loopBlower(flow);
//  float oldSweep = sweepNew;
//  sweepNew = loopSweep();  
//  if(oldSweep != sweepNew){
//    updateSetPoint(sweepNew);
//  }
//  Serial.println(sweepNew);
}
