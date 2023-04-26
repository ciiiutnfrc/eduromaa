/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#define LED_BUILTIN PC13

//Defines de la placa
#define LED_ROJO PB12
#define LEDRGB_ROJO PA10
#define LEDRGB_VERDE PA9
#define LEDRGB_AZUL PA8

#define SW1 PB15
#define SW2 PB14
#define SW3 PB13

//Defines del EDU-RoMAA

#define PARAGOLPE_IZQ PA15
#define PARAGOLPE_DER PB3
#define BOCINA PA5

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LEDRGB_ROJO, OUTPUT);
  pinMode(LEDRGB_VERDE, OUTPUT);
  pinMode(LEDRGB_AZUL, OUTPUT);
  
  pinMode(PARAGOLPE_IZQ, INPUT);
  pinMode(PARAGOLPE_DER, INPUT);
  
  pinMode(BOCINA, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
 
  int SW3_state = digitalRead(SW3);
  
  if (SW3_state == LOW){
    digitalWrite(BOCINA, HIGH);
  }else {
    digitalWrite(BOCINA, LOW);
  }

}
