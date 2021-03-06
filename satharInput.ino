#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
const int RedBUTTON = 2;
const int YellowBUTTON = 3;

int buttonState1;
int buttonState2;
int buttonLast1;
int buttonLast2;

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(RedBUTTON, INPUT);
  pinMode(YellowBUTTON, INPUT);
}

void loop() {
  buttonState1 = digitalRead(RedBUTTON);
  
  if (buttonState1 && !buttonLast1) {
      Serial.write("red\n");
  }
  
  buttonState2 = digitalRead(YellowBUTTON);

  if (buttonState2 && !buttonLast2) {
      Serial.write("yellow\n");
    } 

  buttonLast1  = buttonState1;
  buttonLast2 = buttonState2;

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  if (content.substring(1) == "70 60 48 A8") // Make sure you change this with your own UID number
  {
    Serial.write("portfolio\n");
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
}


  
