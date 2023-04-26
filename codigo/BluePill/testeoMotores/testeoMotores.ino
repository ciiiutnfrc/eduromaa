
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

#define MOTORS_ENABLE PA4
#define MOTOR_IZQ PA3
#define MOTOR_DER PA2

#define INFRAREDS_ENABLE PA6
#define INFRARED_IZQ PA0
#define INFRARED_DER PA1


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
//  pinMode(LED_ROJO, PWM);
  pinMode(LEDRGB_ROJO, OUTPUT);
  pinMode(LEDRGB_VERDE, OUTPUT);
  pinMode(LEDRGB_AZUL, OUTPUT);
  //pinMode(LEDRGB_AZUL, PWM);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);

  pinMode(PARAGOLPE_IZQ, INPUT);
  pinMode(PARAGOLPE_DER, INPUT);

  pinMode(BOCINA, OUTPUT);

  pinMode(MOTOR_IZQ, OUTPUT);
  pinMode(MOTOR_DER, OUTPUT);
  pinMode(MOTORS_ENABLE, OUTPUT);

  pinMode(INFRAREDS_ENABLE, OUTPUT);
  pinMode(INFRARED_IZQ, INPUT);
  pinMode(INFRARED_DER, INPUT);
  digitalWrite(MOTORS_ENABLE, HIGH);
}


// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second

 
 digitalWrite(INFRAREDS_ENABLE, HIGH);
 int INFRARED_IZQ_value = analogRead(INFRARED_IZQ);
 int INFRARED_DER_value = analogRead(INFRARED_DER);
 
 int dutyCycle_ledAzul = map(INFRARED_IZQ_value, 0, 4095, 0, 65535);
 int dutyCycle_ledRojo = map(INFRARED_DER_value, 0, 4095, 0, 65535);
 
 //analogWrite(LEDRGB_AZUL, dutyCycle_ledAzul);
 //analogWrite(LED_ROJO, dutyCycle_ledRojo);

// pwmWrite(LEDRGB_AZUL, dutyCycle_ledAzul);
// pwmWrite(LED_ROJO, dutyCycle_ledRojo);

int velocidad = 0;
for (velocidad =0; velocidad <= 65535; velocidad++){
   analogWrite(MOTOR_IZQ, velocidad);
   analogWrite(MOTOR_DER, velocidad);
   delay(50);
}
   //analogWrite(MOTOR_IZQ, dutyCycle_ledAzul);
   //analogWrite(MOTOR_DER, dutyCycle_ledRojo);
}
