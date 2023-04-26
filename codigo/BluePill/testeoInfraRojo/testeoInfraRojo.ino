//La salida del tipo PWM va desde 0 a 65535, es decir, hay 2^16 combinaciones.

#define MOTORS_ENABLE PA4
#define MOTOR_IZQ PA3
#define MOTOR_DER PA2



#define INFRAREDS_ENABLE PA6
#define INFRARED_IZQ PA0
#define INFRARED_DER PA1

void setup() {
    pinMode(MOTOR_DER, OUTPUT);
    pinMode(MOTOR_IZQ, OUTPUT);
    pinMode(MOTORS_ENABLE, OUTPUT);
    digitalWrite(MOTORS_ENABLE, HIGH);
    Serial.begin(115200); // Ignored by Maple. But needed by boards using Hardware serial via a USB to Serial Adaptor  

     pinMode(INFRAREDS_ENABLE, OUTPUT);
     digitalWrite(INFRAREDS_ENABLE, HIGH);
  pinMode(INFRARED_IZQ, INPUT_ANALOG);
  pinMode(INFRARED_DER, INPUT_ANALOG);
} 


void loop() {

    // read the analog in value:
    int sensorValueIZQ = analogRead(INFRARED_IZQ);
    int sensorValueDER = analogRead(INFRARED_DER);
    // map it to the range of the analog out:
    int outputValueIZQ = map(sensorValueIZQ, 0, 4096, 0, 65535);
    int outputValueDER = map(sensorValueDER, 0, 4096, 0, 65535);
    // change the analog out value:
    analogWrite(PA2, outputValueIZQ);
    analogWrite(PA3, outputValueDER);
    delay(1000);

    // print the results to the serial monitor:
    Serial.print("sensorIZQ = " );
    Serial.print(sensorValueIZQ);
    Serial.print("\t outputIZQ = ");
    Serial.println(outputValueIZQ);
    Serial.print("sensorDER = " );
    Serial.print(sensorValueDER);
    Serial.print("\t outputDER = ");
    Serial.println(outputValueDER);
}
