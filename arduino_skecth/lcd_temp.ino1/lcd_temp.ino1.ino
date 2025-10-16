#include <LiquidCrystal.h>


LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);


const int sensorPin = A0;   
const int ledPin = 13;       
const int motorPin = 10;     

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  lcd_1.begin(16, 2);      
  Serial.begin(9600);

  lcd_1.print("Temp Sistema");
  delay(1500);
  lcd_1.clear();
}

void loop() {
 
  int lectura = analogRead(sensorPin);
  float voltaje = lectura * (5.0 / 1023.0);
  float temperatura = (voltaje - 0.5) * 100.0; 

  lcd_1.setCursor(0, 0);
  lcd_1.print("Temp: ");
  lcd_1.print(temperatura);
  lcd_1.print(" C  ");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");



 
  if (temperatura <= 10) {
    digitalWrite(motorPin, LOW);      

    digitalWrite(ledPin, HIGH);       
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }

  
  else if (temperatura >= 11 && temperatura <= 25) {
    digitalWrite(ledPin, LOW);       
    digitalWrite(motorPin, LOW);      
    delay(500);
  }


  else if (temperatura >= 26) {
    digitalWrite(ledPin, HIGH);      
    digitalWrite(motorPin, HIGH);    
    delay(500);
  }
}
