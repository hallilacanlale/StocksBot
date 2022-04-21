#include <LiquidCrystal.h>
int datafromUser;

const int buzzer = 10;
const int RedLED = 9;
const int GreenLED = 8;

int iByte = 6;

const int rs = 11, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

typedef struct {
  String stock; //char can also be a fixed length string like char fruit[16];
  int count;
  float price;
  int rsi[6] = {60,78,50,28,35,90};
} Stock;


typedef struct
  {
      int one;
      int two;
      int three;
  }  record_type;

Stock stock[3];

record[2] = (record_type) {1,2,3}


ledVals = [10, 20, 18, 15, 19, 20, 18];
int i = 0;
int prevVal = 0;


void setup() {
  Serial.begin(9600);
  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an out
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.clear();
}



void notificationSystem(int iByte) {
  if(iByte - '0' == 3)  {
    lcd.clear();
    lcd.print("BUY!!");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
  }

  else if(iByte - '0' == 4)  {
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


  if (prevVal > ledVals[i]) { //red 
      ledSystem(0);
  } else { //green
      ledSystem(1);
  }
  prevVal = ledVals[i];

  if (i == ledVals.size()){
    i = 0;
  } else {
    i++; 
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
