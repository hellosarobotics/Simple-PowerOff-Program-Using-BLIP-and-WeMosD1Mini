/*
 * ESP8266 BLIP project
 * Andrea Santopietro 2020
 * // mail: hellosarobotics@gmail.com
 * http://www.sa-robotics.com/it/auto-power-off-circuit/
 * 
 * You can use this software as you want. But please don't delete the info above.
 */
#include <ESP8266WiFi.h>

  // This pin in the WeMos D1 Mini is the D2
  int latch_pin = 4;

  /*
   * LED_BUILTIN is replaced by the number 2 to avoid error in Visual Studio Code
   */
  int ledBuiltIn = 2;

  /*
   * Setup method. In this method we set the latch_pin as output and in the poweronTask we set it to HIGH level to maintain the circuit on until all task are done.
   */
  void setup() {
    Serial.begin(115200); 
    Serial.println();
    pinMode(ledBuiltIn, OUTPUT); // Set the LED_BUILTIN as output
    pinMode(latch_pin, OUTPUT); // Latch pin
    // Leave the D1 Mini powered on untill all the jobs are done
    poweronTask(latch_pin, ledBuiltIn);      

    // HERE YOU CAN DO ANY STUFF YOU WANT
    builtinLedBlinkXTimes(ledBuiltIn, 5);
    delay(2000);
    
    // Than switch off the D1 Mini
    shutdownTask(latch_pin, ledBuiltIn);
    // After the shutdown the embedded led will power off. 
  }

  void loop() {
    // Here you can do nothing
    yield();
  }

  /*
   * Enable latch pin to maintain this device powered on
   */
  void poweronTask(int latch_pin, int ledBuiltIn){
    digitalWrite(latch_pin, HIGH);
    digitalWrite(ledBuiltIn, LOW); // YES! The LOW value POWER ON the embedded led on the ESP8266.
    Serial.println("Keep the power connection on");
    delay(10);
  }

  /*
   * Disable latch pin to shutdown this device 
   */
  void shutdownTask(int latch_pin, int ledBuiltIn){
    Serial.println("Auto power off");
    digitalWrite(latch_pin, LOW);
    delay(10);
  }


/*
* Function used to have an hardware feedback
*/
void  builtinLedBlinkXTimes(int  ledBuiltIn, int n){
    n *= 2;
    while(n>0){
        digitalWrite(ledBuiltIn, !digitalRead(ledBuiltIn));
        delay(150);
        n--;
    }
}
