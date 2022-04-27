#include <LiquidCrystal.h>
const int buzzer = 10;
const int RedLED = 9;
const int GreenLED = 8;
int iByte = 9;
const int rs = 11, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int length = 12;
char message2[length];


typedef struct {
  String stock; //char can also be a fixed length string like char fruit[16];
  int count;
  float price;
  int rsi[6];
  int ledVals[6];
} Stock;

Stock stocks[3] = {
  {"AAPL",2, 140.97, {60,78,50,28,35,90},  {10, 20, 18, 15, 19, 20}},
  {"TSLA",6, 744.12, {60,78,50,28,35,90},  {10, 20, 18, 15, 19, 20}},
  {"MSFT",3,64.75, {60,78,50,28,35,90},  {10, 20, 18, 15, 19, 20}}
};

int stockIndex = 0, rsiIndex = 0, ledIndex = 0;
int prevLEDVal = 0;
int prevRSIVal = 0;


void setup() {
  Serial.begin(9600);
  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an out
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.clear();
}


void notificationSystem(int val) {
  if(val == 1)  { // buy
    lcd.clear();
    lcd.print("BUY!!");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(600);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(600);        // ...for 1sec
  }

  else if(val == 0)  { // sell
    lcd.clear();
    lcd.print("SELL!!");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(600);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(600);        // ...for 1sec
  }
  
  
}

void ledSystem(int val) {
  if(val == 1)  {
      digitalWrite(RedLED, LOW);
      lcd.clear();
      lcd.print("AAPL went up");
      digitalWrite( GreenLED , HIGH );
      delay(600); 
      digitalWrite(GreenLED, LOW);    // turn the LED off by making the voltage LOW
      delay(600); 
    }
    else if(val == 0)  {
      digitalWrite( GreenLED, LOW);
      lcd.clear();
      lcd.print("AAPL went down");
      digitalWrite(RedLED, HIGH);
      delay(600);                       // wait for a second
      digitalWrite(RedLED, LOW);    // turn the LED off by making the voltage LOW
      delay(600); 
    }
}




//void performWork(message2) {
//  if (strcmp(message, "portfolio") == 0) {
//        for (int i = 0; i < 3; i++) {
//          lcd.clear();
//          lcd.setCursor(0,0);
//          lcd.print(stocks[i].stock);
//          lcd.setCursor(0,1);
//          lcd.print(stocks[i].count, stocks[i].price);
//          lcd.setCursor(4, 1);
//          lcd.print(stocks[i].price);
//          delay(500);
//        }
//   }
//  
//}

void loop() {

  while (true) {
    while (Serial.available() > 0){
      static char message[length];
      static int message_pos = 0;
      char inByte = Serial.read();
      if (inByte != '\n' && (message_pos < length -1) ) {
        message[message_pos] = inByte;
        message_pos++;    
      } else {      
        message[message_pos] = '\0';
        Serial.println(message);
        
        // do work because card was read
        if (strcmp(message, "portfolio") == 0) {
          for (int i = 0; i < 3; i++) {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(stocks[i].stock);
            lcd.setCursor(0,1);
            lcd.print(stocks[i].count, stocks[i].price);
            lcd.setCursor(4, 1);
            lcd.print(stocks[i].price);
            delay(500);
          }
          message_pos = 0;
          break;
        }


        // do work because red button clicked was read
        if (strcmp(message, "red") == 0) {

          // make sure to call green blinking lights

          // make sure to call BUY

          // make sure to call red blinking lights 

          // make sure to call SELL
          
          message_pos = 0;
          break;
        }


        // do work because yellow button clicked
        if (strcmp(message, "yellow") == 0) {
          // make sure to call BUY with notifications

          // make to call SELL with notifications

          message_pos = 0;
          break;
        }      
      }
    }
  }

//
//   
//   else {
//  
//     if (prevLEDVal > stocks[stockIndex].ledVals[ledIndex]) { //red 
//        ledSystem(0);
//    } else { //green
//        ledSystem(1);
//    }
//    prevLEDVal = stocks[stockIndex].ledVals[ledIndex];
//  
//  
//    //RSI output
//    if (stocks[stockIndex].ledVals[ledIndex] >= 30) { 
//        //buy
//        notificationSystem(1);
//    } else if (stocks[stockIndex].ledVals[ledIndex] >= 70) {
//       notificationSystem(0);
//    }
//  
//  
//    //index validations
//    if (stockIndex == 3){
//      stockIndex = 0;
//    } else {
//      stockIndex++; 
//    }
//   if (ledIndex == 5){
//      ledIndex = 0;
//    } else {
//      ledIndex++; 
//    }
//  
//  
//  
//    delay(100);
//   }
}
