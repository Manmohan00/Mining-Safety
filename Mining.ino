

#include "dht.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define dht_apin A3

dht DHT;

int gas = A1;
int vib = 7;
int methane = A0;
int buz = 4;
int vib1 = 0;
int meth = 0;
int gas1 = 0;


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(gas,INPUT);
  pinMode(vib,INPUT);
  pinMode(methane,INPUT);
  pinMode(buz,OUTPUT);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  lcd.setCursor(4,0);
  lcd.print("Mining");
  lcd.setCursor(4,1);
  lcd.print("Project");
  delay(1000);
  lcd.clear();
  delay(500);
}


void humid()
{
  DHT.read11(dht_apin);


    Serial.print(DHT.humidity);
    Serial.print("|");

    Serial.print(DHT.temperature);
    Serial.print("|");

    delay(5000);
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print("Humid");
    //lcd.setCursor(0,1);    
    //lcd.print(DHT.humidity);

   // lcd.setCursor(6,0);
    //lcd.print("Temp");
    //lcd.setCursor(6,1);    
   // lcd.print(DHT.temperature);
    
    
}

void buzzer()
{

if( vib1 == 1 )
  {
    digitalWrite(buz,HIGH); 
    //lcd.clear();
    //lcd.setCursor(3,0);
    //lcd.print("EARTHQUAKE!!!");
    delay(1000);
  }
  else
  {
   // lcd.clear();
    digitalWrite(buz,LOW);
  }

  if( meth > 470 )
  {
    digitalWrite(buz,HIGH); 
    delay(500);
    digitalWrite(buz,LOW);
    delay(100);
  }
  else
  {
    digitalWrite(buz,LOW);
  }

  if( gas1 > 470 )
  {
    digitalWrite(buz,HIGH); 
    delay(500);
    digitalWrite(buz,LOW);
    delay(100);
  }
  else
  {
    digitalWrite(buz,LOW);
  }
  
}

void loop()
{

  buzzer();
  
  lcd.clear();
  vib1 = digitalRead(vib);
  lcd.setCursor(0,0);
  lcd.print("Quake");
  lcd.setCursor(2,1);
  lcd.print(vib1);
  
  
  gas1 = analogRead(gas);
  Serial.print(gas1);
  Serial.print("|");
  lcd.setCursor(6,0);
  lcd.print("Mono");
  lcd.setCursor(7,1);
  lcd.print(gas1);
 
  meth = analogRead(methane);
  Serial.print(meth);
  Serial.print("|");
  lcd.setCursor(11,0);
  lcd.print("Meth");
  lcd.setCursor(12,1);
  lcd.print(meth);

  humid();

  
}
