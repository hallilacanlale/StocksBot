#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#define SS_PIN 10
byte iByte;
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int datafromUser = 5;
int prevTime = 0;

const int RedLED = 9;
const int GreenLED = 8;

const int RedBUTTON = 2;     
const int YellowBUTTON = 3;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float o;
int c;
String s;

void setup() {
  Serial.begin(9600);
  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);

//    Look for new cards
  while ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
//  // Select one of the cards
//  while ( ! mfrc522.PICC_ReadCardSerial()) 
//  {
//    return;
//  }

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  String tag = content.substring(1);
  Serial.print(content.substring(1));
  if (content.substring(1) == "70 60 48 A8") 
  {
    int count = tag.length();
    byte buffer[count+1];
    tag.getBytes(buffer, count + 1);
    Serial.write('y');
  }
 
 else   {
    Serial.println(" Access denied");
  }
}


void loop() {   
  Serial.write('y');
  
  if(Serial.available() > 0)  {
    iByte = Serial.read();
    Serial.println("HELLO");

    Serial.println(iByte);
    
    if (iByte - '0' != 1 && iByte - '0' != 0)  {
      s = Serial.readStringUntil('*');
      c = Serial.read();
      o = Serial.read();
      
      
      Serial.println(s);
      Serial.println(c);
      Serial.println(o);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(s);
      lcd.setCursor(0,1);
      lcd.print(c, o);
    }
  }


  if (iByte - '0' == 1) {
    digitalWrite( GreenLED , HIGH );
  }
  
  if (iByte - '0' == 0) {
    digitalWrite( RedLED , HIGH );
  }
  delay(1000);
   
  if(iByte - '0' == 0)
  {
    lcd.clear();
    digitalWrite(RedLED, LOW);
    digitalWrite( GreenLED , HIGH );
    lcd.print("AAPL went up");
    
  }
  else if(iByte - '0' == 1)
  {
    lcd.clear();
    digitalWrite(RedLED, HIGH);
    digitalWrite( GreenLED, LOW);
    lcd.print("AAPL went down");
  }
  delay(2);
}
