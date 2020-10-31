
/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  //Initialize serial:
  Serial.begin(9600);

  Serial.print("Ardunio Due Main\n");
}

void set_led(int state){
    if(state)
        digitalWrite(LED_BUILTIN, HIGH);
    else
        digitalWrite(LED_BUILTIN, LOW);
}
void test(void);
void loop()
{
  test();
}
