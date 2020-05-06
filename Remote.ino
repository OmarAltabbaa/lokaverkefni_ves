#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

long duration; // variable for the duration of sound wave travel
int distance_cm; // variable for centimeters measurement
int distance_inch; 

int switchPin = 7;
int potPin = 0;


int x=0;


Servo myservo;
int value;
double angle;
 
void setup()
{
  
  Wire.begin(); 
  
  Serial.begin(9600);
  myservo.attach(6);
 
 
  pinMode(switchPin, INPUT_PULLUP);
  
  lcd.begin(16, 2); // lcd starts with resolution 16x2

  
}
 
void loop()
{
  
  distance_cm = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  distance_inch = duration * 0.0133 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance_cm);
  lcd.println(" cm");
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.print(distance_inch);
  lcd.println(" inch");
  
  Wire.beginTransmission(6);
  
  #9
  Wire.write(100);              // sends x 
  Wire.endTransmission();    // stop transmitting
   
  
  value = analogRead(A1);
  angle = map(value, 0, 1023, 0, 180); 
  //Serial.println(angle);
  myservo.write(angle);                 
  delay(15);
 
  
 
   
}
