#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define dht_apin 4

#define vibrationPin 3
#define methanMQ4 A0
#define carbonMonoMQ7 A1
#define airQualityMQ135 A2

#define DHTTYPE DHT11
DHT dht(dht_apin, DHTTYPE);

int buzzer = 6;
int vibrationData = 0;
int methaneData = 0;
int carbonmonoData = 0;
int airqualityData = 0;
float temp = 0;


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  dht.begin();
  pinMode(carbonMonoMQ7,INPUT);
  pinMode(airQualityMQ135,INPUT);
  pinMode(vibrationPin,INPUT);
  pinMode(methanMQ4,INPUT);
  pinMode(buzzer,OUTPUT);
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

void SendBT(){
    Serial.print(carbonmonoData);
    Serial.print("|");
    Serial.print(methaneData);
    Serial.print("|");
    Serial.print(airqualityData);
    Serial.print("|");
    Serial.print(temp);
  }
  
void humid()
{

    temp = dht.readTemperature();

    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Temperature");
    lcd.setCursor(7,1);
    lcd.print(temp);

    delay(2000);
}

void buzzerFun()
{

  
if( vibrationData == 1 )
  {
    tone(buzzer,500, 500);
    delay(800);
  }
  else{
    noTone(buzzer);
    }

  if( methaneData > 80 )
  {
    tone(buzzer,1000, 500);
    delay(1000);
  }
  else
  {
    noTone(buzzer);
  }

  if( carbonmonoData > 350 )
  {
    tone(buzzer,1000, 500);
    delay(1000);
  }
  else
  {
    noTone(buzzer);
  }
  
}

void loop()
{
  humid();
  buzzerFun();
  
  vibrationData = digitalRead(vibrationPin);
  
  carbonmonoData = analogRead(carbonMonoMQ7);
  carbonmonoData = map(carbonmonoData, 0, 1024, 0, 500);
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("CarbonMonoxide");
  lcd.setCursor(7,1);
  lcd.print(carbonmonoData);
  delay(1000);
 
   
  methaneData = analogRead(methanMQ4);
  methaneData  = map(methaneData, 0, 1024, 0, 500);
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Methane Gas");
  lcd.setCursor(7,1);
  lcd.print(methaneData);
  delay(1000);

  airqualityData = analogRead(airQualityMQ135);
  airqualityData = map(airqualityData, 0, 1024, 0, 500);
  
  SendBT();
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Air Quality");
  lcd.setCursor(7,1);
  lcd.print(airqualityData);
  delay(1000);
  
}
