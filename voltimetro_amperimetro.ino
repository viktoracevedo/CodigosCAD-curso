#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
 
const float R1= 120000; //valor de R1
const float R2= 4700; //valor de R2
const float shunt= 0.100; //valor de la resistencia RS
float vin, vout, input, vin2=0, iin, iin2, potencia; //variables axiliares
float entradaV = A0, entradaI= A1; //nombres de entradas analogicas
long int ahora, antes=0; //variables para manejar el tiempo de visualizacion en pantalla
 
void setup() { 
  lcd.init(); //inicial la pantalla LCD
  lcd.backlight(); //inicia la luz de fondo de la pantalla LCD
  analogReference(INTERNAL);
  //modeo de entrada para A0 y A1
  pinMode (entradaV, INPUT);
  pinMode (entradaI, INPUT);
  //palabras que aparecen cuando se prende el arduino
  lcd.setCursor(3,0); 
  lcd.print("VOLTIMETRO");
  lcd.setCursor(3,1);
  lcd.print("AMPERIMETRO");
  delay(2000);
  lcd.clear();
}
 
void loop() {
  ahora=millis(); //funcion que retora el tiempo trascurrido en milisegundos
  if (ahora-antes>333){ //determina la frecuencia de actualización del display en milisegundos
  volt(); //funcion para obtener el voltaje y mostrarlo
  amp(); //funcion para obtener la corriente y mostrarlo
  antes=ahora; //actualiza el tiempo
  } 
}
 
void volt() {
  for(int i=1; i<=150; i++  )//bucle para tomar varias muestras
  {
  input = analogRead (entradaV); //lee el pin
  vout = (input*1.1)/1024; //operacion para transformar los valores
  vin = vout / (R2 / (R1 + R2)); //convierte los valores a su voltaje de origen
  vin2=vin2+vin; // suma las 150 muestras
  }
  vin = vin2/150;// se promedia las muestras tomadas
  vin2=0;// reseta la variable auxiliar
  //codigo para mostrarlo en el display
  if (vin<=0.001){vin = 0;}
  if (vin>=10)
  {
    lcd.setCursor (0,0);
    lcd.print (vin);
    lcd.setCursor (5,0);
    lcd.print ("V");
  }
  else
  {
    lcd.setCursor (0,0);
    lcd.print (vin);
    lcd.setCursor (4,0);
    lcd.print ("V ");
  }
}
 
void amp() {
  
  for(int i=1; i<=150; i++  )//bucle para tomar varias muestras
  {
  input = analogRead (entradaI); //lee el pin
  vout = (input*1.1)/1024;//operacion para transformar los valores
  iin = vout / shunt; //aplicacion de la ley ohm
  iin2=iin2+iin; // suma las 150 muestras
  }
  iin = iin2/150;// se promedia las muestras tomadas
  iin2=0;// reseta la variable auxiliar
  //codigo para mostrarlo en el display
  if (iin<=0.005){iin = 0;}//corriente cero
  //pone la escala correcta
  if (iin<=0.01)
  {
    lcd.setCursor (0,1);
    lcd.print (iin*1000);
    lcd.setCursor (4,1);
    lcd.print ("mA  ");
  }
  else if (iin<=0.1)
  {
    lcd.setCursor (0,1);
    lcd.print (iin*1000);
    lcd.setCursor (5,1);
    lcd.print ("mA ");
  }
  else if (iin<=1)
  {
    lcd.setCursor (0,1);
    lcd.print (iin*1000);
    lcd.setCursor (6,1);
    lcd.print ("mA");
  }
  else if (iin==0)
  {
    lcd.setCursor (0,1);
    lcd.print (iin);
    lcd.setCursor (4,1);
    lcd.print ("mA   ");
  }
  else if (iin<10)
  {
    lcd.setCursor (0,1);
    lcd.print (iin);
    lcd.setCursor (4,1);
    lcd.print ("A   ");
  }
}
 
