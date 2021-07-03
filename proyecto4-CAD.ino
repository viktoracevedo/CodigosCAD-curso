#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 4, 3, 2, 1, 0);
const int in = 7, out = 6;
int thisChar = 'a';

void setup() {
  lcd.begin(16, 2);
  lcd.cursor();
  pinMode(in,INPUT);
  pinMode(out,OUTPUT);
}

void loop() {
  if(digitalRead(in)==HIGH){
    lcd.setCursor(0, 1);
    lcd.leftToRight();
    lcd.print("BOTON PULSADO");
    for(int i=0;i<=10;i++){
      digitalWrite(out,HIGH);
      delay(10);
      digitalWrite(out,LOW);
      delay(10);
      lcd.home();
    }
  }
  if (thisChar == 'p') {
    lcd.rightToLeft();
  }
  if (thisChar > 'z') {
    thisChar = 'a';
    lcd.leftToRight();
    lcd.clear();
  }
  lcd.write(thisChar);
  delay(10);
  thisChar++;
}
