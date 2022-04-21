#include <LiquidCrystal.h>
int datafromUser;

const int buzzer = 10;
const int RedLED = 9;
const int GreenLED = 8;

int iByte = 6;

const int rs = 11, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

struct Stock {
  String stock; //char can also be a fixed length string like char fruit[16];
  int count;
  float price;
  int rsi[6];
  int ledVals[6];
};
Stock stocks[3];

//Stock stocks[3] = {
//  {"AAPL", 2, 140.97, [60,78,50,28,35,90],  [10, 20, 18, 15, 19, 20, 18]},
//  {"TSLA",6, 744.12, [60,78,50,28,35,90],  [10, 20, 18, 15, 19, 20, 18]};
//  {"MSFT",3,64.75, [60,78,50,28,35,90],  [10, 20, 18, 15, 19, 20, 18]};
//};




int stockIndex = 0, index = 0;
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

  
  
  stocks[0].stock = "AAPL";
  stocks[0].count = 2;
  stocks[0].price = 3;
  int temp[6] = {60,78,50,28,35,90};
  stocks[0].rsi = temp;
//  stocks[0].ledVals =[10, 20, 18, 15, 19, 20, 18];
}



void notificationSystem(int val) {
  if(val == 1)  { // buy
    lcd.clear();
    lcd.print("BUY!!");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
  }

  else if(val == 0)  { // sell
    lcd.clear();
    lcd.print("SELL!!");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
  }
  
  
}

void ledSystem(int val) {
  if(val == 1)  {
      digitalWrite(RedLED, LOW);
      lcd.clear();
      lcd.print("AAPL went up");
      digitalWrite( GreenLED , HIGH );
      delay(800); 
      digitalWrite(GreenLED, LOW);    // turn the LED off by making the voltage LOW
      delay(800); 
    }
    else if(val == 0)  {
      digitalWrite( GreenLED, LOW);
      lcd.clear();
      lcd.print("AAPL went down");
      digitalWrite(RedLED, HIGH);
      delay(800);                       // wait for a second
      digitalWrite(RedLED, LOW);    // turn the LED off by making the voltage LOW
      delay(800); 
    }
}

const int length = 12;

void loop() {
  static char message[length];
  static int message_pos = 0;
  while (Serial.available() > 0){
    char inByte = Serial.read();
    if (inByte != ';' && (message_pos < length -1) ) {
      message[message_pos] = inByte;
      message_pos++;    
    } else {
      message[message_pos] = '\0';
      message_pos = 0;
    }
  }
  Serial.print(message);

//typedef struct {
//  String stock; //char can also be a fixed length string like char fruit[16];
//  int count;
//  float price;
//  int rsi[6];
//  int ledVals[6];
//} Stock;


//Stock stock[3] = {
//  {"AAPL",2, 140.97, [60,78,50,28,35,90],  [10, 20, 18, 15, 19, 20, 18]},
//  {"TSLA",6, 744.12, [60,78,50,28,35,90],  [10, 20, 18, 15, 19, 20, 18]};
//  {"MSFT",3,64.75, [60,78,50,28,35,90],  [10, 20, 18, 15, 19, 20, 18]};
//};
//
//int stockIndex = 0, rsiIndex = 0, ledIndex = 0;
//int prevLEDVal = 0;
//int prevRSIVal = 0;


 //led output
 if (prevLEDVal > stocks[stockIndex].ledVals[index]) { //red 
      ledSystem(0);
  } else { //green
      ledSystem(1);
  }
  prevLEDVal = stocks[stockIndex].ledVals[index];

  

  //RSI output
  if (stocks[stockIndex].rsi[index] >= 30) { //red 
      //buy
      notificationSystem(1);
  } else if (stocks[stockIndex].rsi[index] >= 70) { //green
     notificationSystem(0);
  }

  //index validations
  if (stockIndex == 3){
    stockIndex = 0;
  } else {
    stockIndex++; 
  }
  if (index == 5){
    index = 0;
  } else {
    index++; 
  }
  

  //portfolio
  if (<insert condition>) {
    for (int i = 0; i < stocks.size(); i++) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(stocks[i].stocks);
      lcd.setCursor(0,1);
      lcd.print(stocks[i].count, stocks[i].price);
    }
  }

  delay(5);
  
//
//  if (strcmp(message, "red") == 0) {
//    lcd.clear();
//    lcd.print("yo");
  
//    if(Serial.available() > 0)  {
//      iByte = Serial.read();
//    }
//    ledSystem(iByte);
//    notificationSystem(iByte);
}
