#include <LiquidCrystal.h>

#define NUM_BATTS 8 // The number of batteries.

int gatePins[NUM_BATTS] = {10,10,10, 1, 10, 10, 10, 10};
int highPins[NUM_BATTS] = {A0, A2, A4, A6, A8, A10, A12, A13};
int lowPins[NUM_BATTS] = {A1, A3, A5, A7, A9, A11, A13, A14};

// statusLED
/*
#define 1led
#define 2led
#define 3led
#define 4led
#define 5led
#define 6led
#define 7led
#define 8led
 */
 
 
boolean finished = false;
int printStart = 0;
int interval = 5000;  //Interval (ms) between measurements
 
float mAh = 0.0;
float shuntRes = 1.0;  // In Ohms - Shunt resistor resistance
float voltRef = 4.71; // Reference voltage (probe your 5V pin) 
float current = 0.0;
//float 1battVolt = 0.0; float 2battVolt = 0.0; float 3battVolt = 0.0; float 4battVolt = 0.0; float 5battVolt = 0.0; float 6battVolt = 0.0; float 7battVolt = 0.0; float 8battVolt = 0.0;
//float 1shuntVolt = 0.0; float 2shuntVolt = 0.0; float 3shuntVolt = 0.0; float 4shuntVolt = 0.0; float 5shuntVolt = 0.0; float 6shuntVolt = 0.0; float 7shuntVolt = 0.0; float 8shuntVolt = 0.0;
float battLow = 3.0;
 
unsigned long previousMillis = 0;
unsigned long millisPassed = 0;
 
void setup() {
 
  Serial.begin(9600);
  Serial.println("Battery Capacity Checker v1.1");
  Serial.println("battVolt   current     mAh");
 
  for (int i = 0; i < NUM_BATTS; i++)
  {
    digitalWrite(gatePins[i], LOW);
  }
 

}
 
void loop() {

  
  
  for (int i = 0; i < NUM_BATTS; i++)
  {
    int battVolt = (analogRead(highPins[i]) * voltRef) / 1024.0;
 
  
  
    int shuntVolt = analogRead(lowPins[i]) * voltRef / 1024.0;
   
  if(battVolt >= battLow && finished == false)
  {
      digitalWrite(gatePins[i], HIGH);
      millisPassed = millis() - previousMillis;
      current = (battVolt - shuntVolt) / shuntRes;
      mAh = mAh + (current * 1000.0) * (millisPassed / 3600000.0);
      previousMillis = millis();
 

       
      Serial.print(battVolt);
      Serial.print("\t");
      Serial.print(current);
      Serial.print("\t");
      Serial.println(mAh);
       
      delay(interval);
  }
  if(battVolt < battLow)
  {
      digitalWrite(gatePins[i], LOW);
      
      finished = true;
       
      if(mAh < 10) {
        printStart = 40;
      }
      else if(mAh < 100) {
        printStart = 30;
      }
      else if(mAh <1000) {
        printStart = 24;
      }
      else if(mAh <10000) {
        printStart = 14;
      }
      else {
        printStart = 0;
      }
       

      delay(interval * 2);
  }
  }
}  


//
/*

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print(1battVolt);
  lcd.setCursor(0,1);
  lcd.print(1shuntVolt);
  lcd.setCursor(0,3);
  lcd.print(5battVolt);
  lcd.setCursor(0,4);
  lcd.print(5shuntVolt);
    
  delay(8000);  

*/

//
//lcd display
//batt1 batt2 batt3 batt4
//mah1  mah2  mah3  mah4 
//batt5 batt6 batt7 batt8
//mah5  mah6  mah7  mah8

//
