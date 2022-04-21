#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
int iByte = 6;
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
#include <SoftwareSerial.h>
const int RedBUTTON = 2;
const int YellowBUTTON = 3;

int buttonState1 = 0;
int buttonState2 = 0;
SoftwareSerial portOne(11, 10);
int lastButtonState1 = 0;
int lastButtonState2 = 0;
const int length = 15;
void setup() {
  Serial.begin(9600);
  portOne.begin(9600);
  pinMode(RedBUTTON, INPUT);
  pinMode(YellowBUTTON, INPUT);
  
}

void loop() {
//  buttonState1 = digitalRead(RedBUTTON);
//  buttonState2 = digitalRead(YellowBUTTON);

//  if (buttonState1 != lastButtonState1) {
//    if (buttonState1 == HIGH) {
//      Serial.write("red;");
//    } else {
//      Serial.write("notred;");
//    }
//  }
//  
//  if (buttonState2 != lastButtonState2) {
//    if (buttonState2 == HIGH) {
//      Serial.write("yellow;");
//    } else {
//      Serial.write("notyellow;");
//    }
//    
//  }

  

  if(portOne.available() > 0)  {
      iByte = portOne.read();
      if(iByte - '0' == 0)  {
        Serial.write("profit;");    
      } else if (iByte - '0' == 1)  {
        Serial.write("loss;");  
      } else if (iByte - '0' == 3)  {
        Serial.write("buy;");
      } else if (iByte - '0' == 4)  {
        Serial.write("sell;");
      }


//      static char message[length];
//      static int message_pos = 0;
//      while (Serial.available() > 0){
//        char inByte = Serial.read();
//        if (inByte != '\n' && (message_pos < length -1) ) {
//          message[message_pos] = inByte;
//          message_pos++;    
//        } else {
//          message[message_pos] = '\0';
//          message_pos = 0;
//        }
//      }
//      Serial.write(message);
  }
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
      
  }


  
