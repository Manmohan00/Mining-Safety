#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define dht_apin 4

#define vibrationPin 3
#define methanMQ4 A0
//#define buzzer 7
#define carbonMonoMQ7 A1
#define airQualityMQ135 A2

#define DHTTYPE DHT11
DHT dht(dht_apin, DHTTYPE);

int buzzer = 6;
int vibrationData = 0;
int methaneData = 0;
int carbonmonoData = 0;
int airqualityData = 0;


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  dht.begin();
  pinMode(carbonMonoMQ7,INPUT);
  pinMode(airQualityMQ135,INPUT);
  pinMode(vibrationPin,INPUT);
  pinMode(methanMQ4,INPUT);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  
  lcd.setCursor(2,0);
  lcd.print("Mining");
  lcd.setCursor(9,0);
  lcd.print("Safety");
  lcd.setCursor(4,1);
  lcd.print("Project");
  delay(2000);
  lcd.clear();
  delay(500);
}


void humid()
{
 
//    float humid = dht.readHumidity();
//    Serial.print(humid);
//    Serial.print("|");

    float temp = dht.readTemperature();
    Serial.print(carbonmonoData);
    Serial.print("|");
    Serial.print(methaneData);
    Serial.print("|");
    Serial.print(airqualityData);
    Serial.print("|");
    Serial.print(temp);
    

    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Temperature");
    lcd.setCursor(7,1);
    lcd.print(temp);

    delay(5000);
    
    
}

void buzzerFun()
{
  noTone(buzzer);
  
//if( vibrationData == 1 )
//  {
//    tone(buzzer, 1500);
//    delay(1000);
//    noTone(buzzer);
//    delay(100);
//  }
//  else
//  {
//    noTone(buzzer);
//  }

  if( methaneData > 80 )
  {
    tone(buzzer, 2000);
    delay(500);
    noTone(buzzer);
    delay(100);
  }
  else
  {
    noTone(buzzer);
  }

  if( carbonmonoData > 350 )
  {
    tone(buzzer, 2200);
    delay(500);
    noTone(buzzer);
    delay(100);
  }
  else
  {
    noTone(buzzer);
  }
  noTone(buzzer);
  
}

void loop()
{
  buzzerFun();
  
  vibrationData = digitalRead(vibrationPin);
  //Serial.print(vibrationData);
  
  carbonmonoData = analogRead(carbonMonoMQ7);
  carbonmonoData = map(carbonmonoData, 0, 1024, 0, 500);
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("CarbonMonoxide");
  lcd.setCursor(7,1);
  lcd.print(carbonmonoData);
  delay(500);
 
   
  methaneData = analogRead(methanMQ4);
  methaneData  = map(methaneData, 0, 1024, 0, 500);
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Methane Gas");
  lcd.setCursor(7,1);
  lcd.print(methaneData);
  delay(500);

  airqualityData = analogRead(airQualityMQ135);
  airqualityData = map(airqualityData, 0, 1024, 0, 500);
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Air Quality");
  lcd.setCursor(7,1);
  lcd.print(airqualityData);
  delay(500);
  Serial.print("\n");
  
  humid();

  delay(1000);
}
