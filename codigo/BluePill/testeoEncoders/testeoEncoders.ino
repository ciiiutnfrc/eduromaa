

#define MOTORS_ENABLE PA4
#define MOTOR_IZQ PA3
#define MOTOR_DER PA2

#define ENCODERS_ENABLE PB6
#define ENC_DER PB5
#define ENC_IZQ  PB4

volatile unsigned int counter1;
volatile unsigned int counter2;
int rpm1;
int rpm2;
 
void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
    pinMode(MOTOR_DER, OUTPUT);
    pinMode(MOTOR_IZQ, OUTPUT);
    pinMode(MOTORS_ENABLE, OUTPUT);
    digitalWrite(MOTORS_ENABLE, HIGH);
    Serial.begin(115200); // Ignored by Maple. But needed by boards using Hardware serial via a USB to Serial Adaptor 
  
  pinMode(ENC_DER, INPUT);
  pinMode(ENC_IZQ, INPUT);
  pinMode(ENCODERS_ENABLE, OUTPUT);
  digitalWrite(ENCODERS_ENABLE, HIGH);
 
 
  attachInterrupt(digitalPinToInterrupt(ENC_DER),countpulse1,RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IZQ),countpulse2,RISING);
}
 
void countpulse1(){
        counter1++;
}

void countpulse2(){
        counter2++;
}
 
void loop() {
  static uint32_t previousMillis1;
  if (millis() - previousMillis1 >= 1000) {
            rpm1 = (counter1/20)*60;          
            counter1 = 0;
            previousMillis1 += 1000;
  }
 static uint32_t previousMillis2;
  if (millis() - previousMillis2 >= 1000) {
            rpm2 = (counter2/20)*60;          
            counter2 = 0;
            previousMillis2 += 1000;
  }
 

  Serial.print("Velocidad 1: ");
  Serial.print(rpm1);      //Enviamos serialmente el valor de la distancia
  Serial.print(" rps");
  Serial.println();
  Serial.print("Velocidad 2: ");
  Serial.print(rpm2);      //Enviamos serialmente el valor de la distancia
  Serial.print(" rps");
  Serial.println();
  delay(1);
}
