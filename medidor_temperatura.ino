//Display 7 Segmentos Catodo Común
int display7c[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
//Delcaración de Los Pines del Display
byte a=2;
byte b=3;
byte c=4;
byte d=5;
byte e=6;
byte f=7;
byte g=8;
byte pt=9;
// Declaración de los Pines de los Transistores           
byte t2=10;
byte t3=11;
byte t4=12;
//Contadores para hacer el Temporizador
int tempor=0,tiempo=0;
//Función que coloca en el puerto de salida los bits comenzando
void puerto(int bits,int ini,int fin){
  for(int i=ini;i<=fin;i++)
  {
    digitalWrite(i,bitRead(bits,i-ini));
  }
}
//Función encargada de la multiplexación
void mostrar( ){
   int dig[4];   //Declarar las variables
   int mil=tempor/1000; //empieza de un valor de mil
   //Dígito Centena
   dig[0]=(tempor-mil*1000)/100;
   //Dígito Decena
   dig[1]=(tempor-mil*1000-dig[0]*100)/10;
   //Dígito Unidad
   dig[2]=(tempor-mil*1000-dig[0]*100-dig[1]*10);
   //Multiplexación
   for(int i=t2;i<=t4;i++){ 
     if(i == t3){// pone el punto decimal
       digitalWrite(pt,HIGH);
     }
     //Muestra unidades
     puerto(display7c[dig[i-t2]],a,g); 
     digitalWrite(i,HIGH);  //Enciende el display de unidades
     delay(500);               //Retardo de 1 milisegundos
     digitalWrite(i,LOW);   //Apaga el display de unidades
     digitalWrite(pt,LOW);
   }                      
}
//Función que cuenta el tiempo que le toma al temporizador
void temporizacion() 
{
   tiempo=1; //ciclos con el mismo valor de temperatura
   while (tiempo>0) //Mientras que la variable con sea mayor que cero
   {
      mostrar();        //Llamar la funcion para colocar cada numero en cada display
      tiempo--;        // Decremente la variable tiempo
   }
}
//Configura todos los pines como Salidas
void setup() {
  for(int i=a;i<=t4;i++){
    pinMode(i,OUTPUT);
  }
  pinMode(A0, INPUT);
}
void loop() {
   tempor=(5.0 * analogRead(A0) * 100.0)/1023.0;//conversion del voltaje a temperatura
   tempor*=10;//quita el valor decimal
   temporizacion(); //funcion para hacer recorrer los 3 displays
}
