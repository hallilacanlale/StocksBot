#include <LiquidCrystal.h>
const int buzzer = 10;
const int RedLED = 9;
const int GreenLED = 8;
int iByte = 9;
const int rs = 11, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int length = 12;
char message2[length];
bool AAPLval = true;

bool BABAval = false;


typedef struct {
  String stock; //char can also be a fixed length string like char fruit[16];
  int count;
  float price;
  int rsi[6];
  int ledVals[6];
} Stock;


int AAPLarray[8] = {1, 0, 1, 0, 0, 0, 1, 1};
int AAPLrsi[8] = {60,18,10,50,35,88,40,85};

//BABAarray[8} = {0, 0, 1, 0, 0, 0, 1, 1};
//BABArsi[7} = {75,76,32,50,77,79,78};
//
//
//



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


void notificationSystem(int val, bool notify) {
  if(val >= 70 )  { // buy
    lcd.clear();
    lcd.print("BUY AAPL!!");
  } else if (val <= 30) {
      lcd.clear();
      lcd.print("SELL AAPL!!");
  }    
    if (notify == true) {
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(600);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(600);        // ...for 1sec
    }

}

void ledSystem(int val) {
  if(val == 1)  { //blink green
      digitalWrite(RedLED, LOW);
      lcd.clear();
      lcd.print("AAPL went up");
      digitalWrite( GreenLED , HIGH );
      delay(300); 
      digitalWrite(GreenLED, LOW);    // turn the LED off by making the voltage LOW
      delay(300); 
    }
    else if(val == 0)  { /// blink red
      digitalWrite( GreenLED, LOW);
      lcd.clear();
      lcd.print("AAPL went down");
      digitalWrite(RedLED, HIGH);
      delay(600);                       // wait for a second
      digitalWrite(RedLED, LOW);    // turn the LED off by making the voltage LOW
      delay(600); 
    }
}


void printPortfolio() {
  for (int i = 0; i < 3; i++) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(stocks[i].stock);
      lcd.setCursor(0,1);
      lcd.print(stocks[i].count, stocks[i].price);
      lcd.setCursor(4, 1);
      lcd.print(stocks[i].price);
      delay(800);
  }
}

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
            delay(800);
        }
          message_pos = 0;
          break;
        }


        // do work because red button clicked was read
        if (strcmp(message, "red") == 0) {
            for (int j = 0; j < 7; j++){
              ledSystem(AAPLarray[j]);
              delay(700);
              // make sure to call BUY
              notificationSystem(AAPLrsi[j], false);
              delay(700);
            }
            message_pos = 0;
            break;
        }


        // do work because yellow button clicked
        if (strcmp(message, "yellow") == 0) {
            for (int j = 0; j < 7; j++){
              ledSystem(AAPLarray[j]);
              delay(700);
              // make sure to call BUY
              notificationSystem(AAPLrsi[j], true);
              delay(700);
            }
          message_pos = 0;
          break;
        }      
      }
    }
  }

}
