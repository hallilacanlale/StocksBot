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


void setup() {
  Serial.begin(9600);
  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  
//  // initialize the pushbuttons pin as an input:
//  pinMode(RedBUTTON, INPUT);
//  pinMode(YellowBUTTON, INPUT);
//
//
//  SPI.begin();      // Initiate  SPI bus
//  mfrc522.PCD_Init();   // Initiate MFRC522
//  Serial.println("Approximate your card to the reader...");
}


void loop() {   
  
  if(Serial.available() > 0)  {
      iByte = Serial.read();
      Serial.write(iByte);
  }
  
//  if (iByte - '0' == 1) {
//    digitalWrite( GreenLED , HIGH );
//  }
//  
//  if (iByte - '0' == 0) {
//    digitalWrite( RedLED , HIGH );
//  }
//  delay(1000);

   
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
  
//
//    if (digitalRead(GreenLED) == HIGH) {
//      lcd.print("AAPL went up");
//    }
//
//    if (digitalRead(RedLED) == HIGH) {
//      lcd.print("AAPL went down");
//    }
//
//
//    // Look for new cards
//  if ( ! mfrc522.PICC_IsNewCardPresent()) 
//  {
//    return;
//  }
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial()) 
//  {
//    return;
//  }
//  //Show UID on serial monitor
//  Serial.print("UID tag :");
//  String content= "";
//  byte letter;
//  for (byte i = 0; i < mfrc522.uid.size; i++) 
//  {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     content.concat(String(mfrc522.uid.uidByte[i], HEX));
//  }
//  Serial.println();
//  Serial.print("Message : ");
//  content.toUpperCase();
//  if (content.substring(1) == "70 60 48 A8") //change here the UID of the card/cards that you want to give access
//  {
//    Serial.println("Authorized access");
//    Serial.println();
//    delay(3000);
//  }
// 
// else   {
//    Serial.println(" Access denied");
//    delay(3000);
//  }
}

 
