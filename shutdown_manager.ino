#include "SleepyPi2.h"
#include <LowPower.h>

HANDSHAKE_IN = 7;
HANDSHAKE_OUT = 17;
RELAY = 16;
ACCPWR = 5;

void wake_arduino(){
  // just a placeholder - code then resumes following interrupt
}

void shutdown_manager_setup() {
 
  // Configure pins
  pinMode(HANDSHAKE_OUT, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(HANDSHAKE_IN, INPUT);
  pinMode(ACCPWR, INPUT);

  // Add interrupt to detect accessory power
  attachInterrupt(ACCPWR, wake_arduino, RISING);
}

void sleepnow(){
  digitalWrite(RELAY, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(ACCPWR,wake_arduino, RISING);
  sleep_mode();
  sleep_disable();
  detach_interrupt(ACCPWR);
  digitalWrite(RELAY, HIGH);
}

void shutdown_manager_loop(){
  // A start of loop we must be powered up
  if (digitalRead(ACCPWR) == LOW){
    // tell Pi to power off
    digitalWrite(HANDSHAKE_OUT, LOW);
    // give it up to 30 secs
    int count = 0;
    while (count < 30000){
      // if Pi shutdown
      if (digitalRead(HANDSHAKE_IN) == LOW){
        break;
      }
      count++;
    }
    // Go into low power mode
    sleepnow();
  }
}  