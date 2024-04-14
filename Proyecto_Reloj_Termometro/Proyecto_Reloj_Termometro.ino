int estado=0; 
unsigned long segundoAnterior=0;
unsigned long segundoActual=0;
unsigned long segundos=0;
int minutos=0;
int horas=0;
int selector=0;
int contador=0;
int enter=0;
float centigrados=0;
int boton=0;
unsigned long delays=0;
unsigned long contadorActual=0;
unsigned long contadorAnterior=0;
#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2); 
uint16_t inputValue = 0;      

void setup() 
{
  //pinMode(9, OUTPUT);
  //digitalWrite(9, HIGH);
  lcd.begin(16, 2);             
}

float leerGradosC() {
  int dato;
  float c;
  dato = analogRead(A1);
  c = (500.0 * dato / 1024);
  return c;  
}

void loop() 
{
  ///////////////////////////////////////////////////////////////////////////// Segundero preciso
  segundoAnterior=segundoActual;
  segundoActual=(millis()/1000);

  if (segundoActual==segundoAnterior+1){ 
    segundos=segundos+1;
    contador=contador+1;
  }
  //////////////////////////////////////////////////////////////////////////////
  contadorAnterior=contadorActual;
  contadorActual=millis()/100;

  if(contadorActual==contadorAnterior +5) {delays ++;}
  ///////////////////////////////////////////////////////////////////////////// Hora
  if (segundos==60){ 
    segundos=0;
    minutos=minutos+1;
  }
  if (minutos==60){
    minutos=0;
    horas=horas+1;
  }
  if (horas==24){
    horas=0;
    minutos=0;
    segundos=0;  
  }
  
 if (segundos%2==0 && estado==2){
  centigrados = leerGradosC();
 }
///////////////////////////////////////////////////////////////////////////// 
  inputValue = analogRead(A0);
  
    if(inputValue < 100 && inputValue >= 0) {inputValue=1;boton = 1; contador=0;}
    else if((inputValue < 250 && inputValue > 150)){inputValue=2; boton = 2; contador=0;}
    else if(inputValue < 470 && inputValue > 370) {inputValue=3; boton = 3;}
    else if(inputValue < 670 && inputValue > 570) {inputValue; boton = 4; contador=0;}
    else if(inputValue < 870 && inputValue > 770) {inputValue=5; boton = 5; contador=0;}
    else if(inputValue <= 1023 && inputValue > 950) {inputValue=0; boton = 0;}
    
  if (millis()/100>=delays+3){ 
  delays= contadorActual;
  if((contador>10)&&((estado==1)||(estado==3)||(estado==4)||(estado==0))){
    estado=0;
    enter=0;
    selector=0;
  }
///////////////////////////////////////////////////////////////////////////// 
    if (boton==5){ 
      selector=selector +1;
      if (selector==3){ 
        selector=1;
      } 
    }
    if (boton==4 && selector !=0){
      enter=enter+1;
      if (enter>1){
        enter=0;
      }
    }


///////////////////////////////////////////////////////////////////////////// Estado 0
  if (estado==0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(horas);
    lcd.print(":");
    lcd.print(minutos);
    lcd.print(":");
    lcd.print(segundos);
    lcd.setCursor(10,0);
    lcd.print("CONFIG");
    lcd.setCursor(10,1);
    lcd.print("TEMPC");
    lcd.setCursor(15,1);
    lcd.print((char)223);
    
    if (selector==1){  
      lcd.setCursor(9,0);
      lcd.print(">");
      if (enter==1){
          estado=1;
          enter=0;
      }
    }
    if (selector==2){ 
      lcd.setCursor(9,1);
      lcd.print(">");
      if (enter==1){
        estado=2;
        enter=0;
        selector=0;
      }
    }
  }
///////////////////////////////////////////////////////////////////////////// Estado 1
  if (estado==1){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(horas);
    lcd.print(":");
    lcd.print(minutos);
    lcd.print(":");
    lcd.print(segundos);
    lcd.setCursor(10,0);
    lcd.print("CONFIG");
    lcd.setCursor(11,1);
    lcd.print("H");
    lcd.setCursor(14,1);
    lcd.print("M");
    if (selector==1){
      lcd.setCursor(10,1);
      lcd.print(">");
      
      if (enter==1){
          estado=3;
          enter=0;
      }
    }
    if (selector==2){
      lcd.setCursor(13,1);
      lcd.print(">");
      
      if (enter==1){
        estado=4;
        enter=0;
      }
    }
  }
///////////////////////////////////////////////////////////////////////////// Estado2
  if (estado==2){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(centigrados); 
    lcd.setCursor(5,0);
    lcd.print("C");
    lcd.setCursor(11,0);
    lcd.print("HORA");
    if (selector==1){
      lcd.setCursor(10,0);
      lcd.print(">");
      if (enter==1){
        estado=0;
        enter=0;
        selector=0; 
      }
    }
  }
///////////////////////////////////////////////////////////////////////////// Estado 3
  if (estado==3){
    segundos=0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(horas);
    lcd.print(":");
    lcd.print(minutos);
    lcd.print(":");
    lcd.print(segundos);
    lcd.setCursor(10,0);
    lcd.print("CONFIG");
    lcd.setCursor(14,1);
    lcd.print("M");
    lcd.setCursor(11,1);
    if (segundoActual%2==0){
      lcd.print("H");
    }
    if (boton==1){
      horas=horas+1;
    }
    if (boton==2){
      if (horas == 0){
        horas=23;
      }
      else{
        horas=horas-1;
        }
    }
    if (enter==1){
      enter=0;
      estado=1;
    }
  }
///////////////////////////////////////////////////////////////////////////// Estado 4
  if (estado==4){
    segundos=0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(horas);
    lcd.print(":");
    lcd.print(minutos);
    lcd.print(":");
    lcd.print(segundos);
    lcd.setCursor(10,0);
    lcd.print("CONFIG");
    lcd.setCursor(11,1);
    lcd.print("H");
    lcd.setCursor(14,1);
    if (segundoActual%2==0){
      lcd.print("M");
    }
    if (boton==1){
      minutos=minutos+1;
    }
    if (boton==2){
      if (minutos == 0){
        minutos=59;
      }
      else{
        minutos=minutos-1;
      }
    }
    if (enter==1){
      enter=0;
      estado=1;
    }
  }
  }
}
