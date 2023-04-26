//La salida del tipo PWM va desde 0 a 65535, es decir, hay 2^16 combinaciones.

#define MOTORS_ENABLE PA4
#define MOTOR_IZQ PA3
#define MOTOR_DER PA2


void setup() {
    pinMode(MOTOR_DER, OUTPUT);
    pinMode(MOTOR_IZQ, OUTPUT);
    pinMode(MOTORS_ENABLE, OUTPUT);
    digitalWrite(MOTORS_ENABLE, HIGH);
}

int Valor_PWM = 0;
void loop() {
    while(Valor_PWM<=65535)
    {
        analogWrite(MOTOR_DER, Valor_PWM);
        analogWrite(MOTOR_IZQ, Valor_PWM);
        delay(1000);
        Valor_PWM = Valor_PWM + 1000;
    }
    Valor_PWM = 0;
}
