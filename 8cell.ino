
 
//battery numbers
//1
#define 1gatePin 10
#define 1highPin A0
#define 1lowPin A1
//2
#define 2gatePin 10
#define 2highPin A2
#define 2lowPin A3
//3
#define 3gatePin 10
#define 3highPin A4
#define 3lowPin A5
//4
#define 4gatePin 1
#define 4highPin A6
#define 4lowPin A7
//5
#define 5gatePin 10
#define 5highPin A8
#define 5lowPin A9
//6
#define 6gatePin 10
#define 6highPin A10
#define 6lowPin A11
//7
#define 7gatePin 10
#define 7highPin A12
#define 7lowPin A13
//8
#define 8gatePin 10
#define 8highPin A13
#define 8lowPin A14
// statusLED
#define 1led
#define 2led
#define 3led
#define 4led
#define 5led
#define 6led
#define 7led
#define 8led
 
boolean finished = false;
int printStart = 0;
int interval = 5000;  //Interval (ms) between measurements
 
float mAh = 0.0;
float shuntRes = 1.0;  // In Ohms - Shunt resistor resistance
float voltRef = 4.71; // Reference voltage (probe your 5V pin) 
float current = 0.0;
float 1battVolt = 0.0; float 2battVolt = 0.0; float 3battVolt = 0.0; float 4battVolt = 0.0; float 5battVolt = 0.0; float 6battVolt = 0.0; float 7battVolt = 0.0; float 8battVolt = 0.0;
float 1shuntVolt = 0.0; float 2shuntVolt = 0.0; float 3shuntVolt = 0.0; float 4shuntVolt = 0.0; float 5shuntVolt = 0.0; float 6shuntVolt = 0.0; float 7shuntVolt = 0.0; float 8shuntVolt = 0.0;
float battLow = 3.0;
 
unsigned long previousMillis = 0;
unsigned long millisPassed = 0;
 
void setup() {
 
  Serial.begin(9600);
  Serial.println("Battery Capacity Checker v1.1");
  Serial.println("battVolt   current     mAh");
 
  digitalWrite(gatePin, LOW);
 

}
 
void loop() {
 
  1battVolt = analogRead(1highPin) * voltRef / 1024.0;
  2battVolt = analogRead(2highPin) * voltRef / 1024.0;
  3battVolt = analogRead(3highPin) * voltRef / 1024.0;
  4battVolt = analogRead(4highPin) * voltRef / 1024.0;
  5battVolt = analogRead(5highPin) * voltRef / 1024.0;
  6battVolt = analogRead(6highPin) * voltRef / 1024.0;
  7battVolt = analogRead(7highPin) * voltRef / 1024.0;
  8battVolt = analogRead(8highPin) * voltRef / 1024.0;
  shuntVolt = analogRead(lowPin) * voltRef / 1024.0;
   
  if(battVolt >= battLow && finished == false)
  {
      digitalWrite(gatePin, HIGH);
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
      digitalWrite(gatePin, LOW);
      
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


//

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


//
lcd display
batt1 batt2 batt3 batt4
mah1  mah2  mah3  mah4 
batt5 batt6 batt7 batt8
mah5  mah6  mah7  mah8

//




