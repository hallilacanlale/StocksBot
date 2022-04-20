// 1- Sarah Athar - 653568210
// 2- Lab 3 - Scrolling Output
// 3- Display Namme and Quote on a 16X2 LCD screen and make sure that the quote has a scrolling output
// 4- It is important to make sure the brightness is adjusted in order to see the output correctly
// 5- Used Arduino's Demo Link provided in the lab, as starter code for the Lab
// 6- Office Hours demonstration 2/8/2022,

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.   
}

void loop() {
  // set the cursor to column 0, line 1
  lcd.print("Sarah Athar")
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("My favorite quote")
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
