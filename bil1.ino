#include <Servo.h>
#include <Wire.h>

int x=0;
int trig= A3;
int echo= A2;
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int switchPin = 7;
int potPin = 0;

int duration =0;
int distance=0;


Servo myservo;
int value;
double angle;
 
void setup()
{
  Serial.begin(9600);
  myservo.attach(6);
  
  Wire.begin(6);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent);
 
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  
}
 
void loop()
{
  value = analogRead(A1);
  angle = map(value, 0, 1023, 0, 180); 
  //Serial.println(angle);
  myservo.write(angle);                 
  delay(15);
  
  int speed = analogRead(potPin) / 4;
  boolean reverse = digitalRead(switchPin);
  setMotor(speed, reverse);
   
  digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);


  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);
  

  if ( distance < 50)
  {
    digitalWrite(in1Pin , LOW);
    digitalWrite(enablePin , HIGH);
    digitalWrite(in2Pin , HIGH);
    digitalWrite(switchPin , LOW);
    delay(100);
  }
  else
  {
    digitalWrite(in1Pin , HIGH);
    digitalWrite(enablePin , LOW);
    digitalWrite(in2Pin , LOW);
    digitalWrite(switchPin , HIGH);
  }
}
 
void setMotor(int speed, boolean reverse)
{
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, ! reverse);
  digitalWrite(in2Pin, reverse);
}
void receiveEvent(int bytes) {
  x = Wire.read();  
}
