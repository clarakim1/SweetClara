#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h> 


#define Relay 7
#define Water A0 

SoftwareSerial mySerial(0,1);   //RX TX
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display 
String readString; 

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(Relay, OUTPUT);

     // put your setup code here, to run once: 
  pinMode(Relay, OUTPUT); 
  Serial.begin(9600); 
  lcd.init();                      // initialize the lcd 
  lcd.init(); 
  // Print a message to the LCD. 
  lcd.backlight(); 
  lcd.setCursor(0, 0); 
  lcd.print("Hello, world!"); 
  lcd.setCursor(0, 1); 
  lcd.print("Happy Jeju"); 
  delay(5000); 
  
}

void RelayOff() {
  if (readString == "b") {   
    digitalWrite(Relay, LOW);
  }
 
}

bool RelayOn;

void MyDelay(int ms) {
   for(int i=0;i<ms;i++){
      if (Serial.available())
      {
        RelayOff();
        RelayOn = false;
        break;
      }
      delay(1);
   }
}

void RelayON() {

    char c = Serial.read(); 
    readString += c; 


   if (readString.length() > 0)
       { 
    if (readString == "a") { 
    digitalWrite(Relay, HIGH);
    MyDelay(5000);
      if (readString == "b") { 
     digitalWrite(Relay,LOW);}
         
    //if(! RelayOn) return;
    //digitalWrite(Relay, LOW);
   // MyDelay(1000);
    }  
}
}
void loop() {

   int Water_Value = analogRead(Water); 
   int Water_Content = map(Water_Value, 1023, 165, 0, 100);  //map(value, fromLow, fromHigh, toLow, toHigh)

 lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Sensor Value="); 
  lcd.print(Water_Value); 
  lcd.setCursor(0, 1); 
  lcd.print("Water Con.="); 
  lcd.print(Water_Content); 
  lcd.print("%");    
  delay(1000); 

  if (Water_Value <= 400) { 
    digitalWrite(Relay, HIGH); 
    delay(1000); 
                          } 
  else { 
    digitalWrite(Relay, LOW); 
    delay(1000); 
  } 


  readString = ""; 
  String data = String(Water_Value) +","+String(Relay) +","+String(Water_Content)+",";  
  Serial.println(data); 



  RelayOn = true;
  RelayON();
 if(Serial.available())
  {
    RelayOff();
    RelayOn = false;
  }
}
