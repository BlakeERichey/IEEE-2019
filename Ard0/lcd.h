// include the library code:
#include <LiquidCrystal.h>

void printLCD(String msg, double val, bool typecast){
//initialize lcd
  const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

  
  lcd.clear();
  lcd.print(msg);
  lcd.setCursor(0,0);
  if(typecast){
    lcd.setCursor(0,1);
    lcd.print(int(val)%48); 
  }else{
    lcd.setCursor(0,1);
    lcd.print(val);
  }
}
