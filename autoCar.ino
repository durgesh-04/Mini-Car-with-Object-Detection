//Comandos por Serial Monitor
int incomingByte = 0;
//Sensores de emergência
int buttonPin1 = 22;
int buttonPin2 = 24;
int buttonPin3 = 26;
//Servo
const int servo = 8;
//Ultrassom
const int echoPin = 13;
const int trigPin = 12;
//Motores
//Motor A – direita
int in1 = 6;
int in2 = 5;
int ena = 7;
//Motor B – esquerda
int in3 = 4;
int in4 = 3;
int enb = 2;
long duration = 0;
long distanciaFrente = 0;
long distanciaEsquerda = 0;
long distanciaDireita = 0;
void setup ()
{
//Comandos por Serial Monitor
Serial.begin(9600);
//Sensores de emergência
pinMode(buttonPin1,INPUT);
//Servo
pinMode(servo, OUTPUT);
//Ultrassom
Serial.begin(9600);
pinMode(echoPin, INPUT);
pinMode(trigPin, OUTPUT);
//Motores
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(ena, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(enb, OUTPUT);
}
//Motores
// ***** MOTOR *****
//função de nível 1 para movimentação do motor da direita
void nv1_motor_direita(int p_velocidade)
{
int v_in1;
int v_in2;
int t_ena;
int v_velocidade = abs(p_velocidade);
if (p_velocidade>0) { v_in1 = HIGH; v_in2 = LOW; } else { v_in1 = LOW; v_in2 = HIGH; }
if (v_velocidade == 255 || v_velocidade == 0) { t_ena = 1; } else {t_ena = 0 ; }
//aciona motor
digitalWrite(in1, v_in1);
digitalWrite(in2, v_in2);
if (t_ena == 1) { digitalWrite(ena, v_velocidade); } else { analogWrite(ena, v_velocidade); }
}
//função de nível 1 para movimentação do motor da esquerda
void nv1_motor_esquerda(int p_velocidade)
{
int v_in3;
int v_in4;
int t_enb;
int v_velocidade = abs(p_velocidade);
if (p_velocidade>0) { v_in3 = LOW; v_in4 = HIGH; } else { v_in3 = HIGH; v_in4 = LOW; }
if (v_velocidade == 255 || v_velocidade == 0) { t_enb = 1; } else {t_enb = 0 ; }
//aciona motor
digitalWrite(in3, v_in3);
digitalWrite(in4, v_in4);
if (t_enb == 1) { digitalWrite(enb, v_velocidade); } else { analogWrite(enb, v_velocidade); }
}
//***** FIM ACIONAMENTO MOTOR *****
void loop ()
{
incomingByte = 0;
//*****ACIONAMENTO SERVO E ULTRASSOM*****
//*****Esquerda*****
digitalWrite(servo, HIGH);
delayMicroseconds(2000);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(servo, HIGH);
delayMicroseconds(2000);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(servo, HIGH);
delayMicroseconds(2000);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanciaEsquerda = duration /29 /2 ;
Serial.print(“Esquerda: “);
Serial.println(distanciaEsquerda);
//*****Frente*****
digitalWrite(servo, HIGH);
delayMicroseconds(1500);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(servo, HIGH);
delayMicroseconds(1500);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(servo, HIGH);
delayMicroseconds(1500);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = 0;
duration = pulseIn(echoPin, HIGH);
distanciaFrente = duration /29 /2 ;
Serial.print(“Frente: “);
Serial.println(distanciaFrente);
//*****Direita*****
digitalWrite(servo, HIGH);
delayMicroseconds(1000);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(servo, HIGH);
delayMicroseconds(1000);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(servo, HIGH);
delayMicroseconds(1000);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanciaDireita = duration /29 /2 ;
Serial.print(“Direita: “);
Serial.println(distanciaDireita);
//*****Frente*****
digitalWrite(servo, HIGH);
delayMicroseconds(1500);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(servo, HIGH);
delayMicroseconds(1500);
digitalWrite(servo, LOW);
delay(50);
digitalWrite(servo, HIGH);
delayMicroseconds(1500);
digitalWrite(servo, LOW);
//*****FIM DO ACIONAMENTO SERVO E ULTRASSOM*****
//*****ACIONAMENTO MOTOR *****
if ((distanciaFrente<=5) && (distanciaFrente!=0) || (distanciaEsquerda<=5) && (distanciaEsquerda!=0) || (distanciaDireita<=5) && (distanciaDireita!=0)) {
nv1_motor_direita(-255);
nv1_motor_esquerda(-255);
Serial.println(“## Re”);
}
if ((distanciaFrente>20) && (distanciaFrente!=0) && (distanciaEsquerda>20) && (distanciaEsquerda!=0) && (distanciaDireita>20) && (distanciaDireita!=0)){
nv1_motor_direita(255);
nv1_motor_esquerda(255);
Serial.println(“## Frente”);
}
if ((distanciaFrente<=20) && (distanciaFrente>5)) {
if (distanciaDireita<distanciaEsquerda){
nv1_motor_direita(255);
nv1_motor_esquerda(-255);
Serial.print(“## FrenteEsquerda”);
}
if (distanciaDireita>=distanciaEsquerda){
nv1_motor_direita(-255);
nv1_motor_esquerda(255);
Serial.print(“## FrenteDireita”);
}
}
if ((distanciaDireita<=20) && (distanciaDireita>5)) {
nv1_motor_direita(255);
nv1_motor_esquerda(-255);
Serial.println(“## Esquerda”);
}
if ((distanciaEsquerda<=20) && (distanciaEsquerda>5)) {
nv1_motor_direita(-255);
nv1_motor_esquerda(255);
Serial.println(“## Direita”);
}
//***** FIM ACIONAMENTO MOTOR *****
//***** SENSORES DE EMERGÊNCIA *****
if (digitalRead(buttonPin1)==LOW) {
nv1_motor_direita(-255);
nv1_motor_esquerda(-255);
delay(3000);
if (distanciaDireita<distanciaEsquerda){
nv1_motor_direita(255);
nv1_motor_esquerda(-255);
Serial.print(“## FrenteEsquerda”);
}
if (distanciaDireita>=distanciaEsquerda){
nv1_motor_direita(-255);
nv1_motor_esquerda(255);
Serial.print(“## FrenteDireita”);
}
}
if (digitalRead(buttonPin2)==LOW) {
nv1_motor_direita(-255);
nv1_motor_esquerda(-255);
delay(3000);
if (distanciaDireita<distanciaEsquerda){
nv1_motor_direita(255);
nv1_motor_esquerda(-255);
Serial.print(“## FrenteEsquerda”);
}
if (distanciaDireita>=distanciaEsquerda){
nv1_motor_direita(-255);
nv1_motor_esquerda(255);
Serial.print(“## FrenteDireita”);
}
}
if (digitalRead(buttonPin3)==LOW) {
nv1_motor_direita(-255);
nv1_motor_esquerda(-255);
delay(3000);
if (distanciaDireita<distanciaEsquerda){
nv1_motor_direita(255);
nv1_motor_esquerda(-255);
Serial.print(“## FrenteEsquerda”);
}
if (distanciaDireita>=distanciaEsquerda){
nv1_motor_direita(-255);
nv1_motor_esquerda(255);
Serial.print(“## FrenteDireita”);
}
}
//***** FIM SENSORES DE EMERGÊNCIA *****
//***** COMANDOS POR SERIAL MONITOR *****
if (Serial.available() > 0) {
incomingByte = Serial.read();
Serial.print(“I received: “);
Serial.println(incomingByte, DEC);
}
//r
if (incomingByte == 114){
nv1_motor_direita(-255);
nv1_motor_esquerda(-255);
delay(1000);
}
//f
if (incomingByte == 102){
nv1_motor_direita(255);
nv1_motor_esquerda(255);
delay(1000);
}
//d
if (incomingByte == 100){
nv1_motor_direita(-255);
nv1_motor_esquerda(255);
delay(1000);
}
//e
if (incomingByte == 101){
nv1_motor_direita(255);
nv1_motor_esquerda(-255);
delay(1000);
}
//s
if (incomingByte == 115){
nv1_motor_direita(0);
nv1_motor_esquerda(0);
delay(1000);
}
//R
if (incomingByte == 82){
nv1_motor_direita(-255);
nv1_motor_esquerda(-255);
delay(3000);
}
//F
if (incomingByte == 70){
nv1_motor_direita(255);
nv1_motor_esquerda(255);
delay(3000);
}
//D
if (incomingByte == 68){
nv1_motor_direita(-255);
nv1_motor_esquerda(255);
delay(3000);
}
//E
if (incomingByte == 69){
nv1_motor_direita(255);
nv1_motor_esquerda(-255);
delay(3000);
}
//S
if (incomingByte == 83){
nv1_motor_direita(255);
nv1_motor_esquerda(-255);
delay(3000);
}
}
