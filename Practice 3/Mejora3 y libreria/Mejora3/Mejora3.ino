#include <LiquidCrystal.h>
#include<Keypad.h>

const int DO  = 262;
const int RE  = 294;
const int MI  = 330;
const int FA  = 349;
const int SOL = 392;
const int LA  = 440;
const int SI  = 494;
const int DO2  = 523;

boolean mostrarMenu = true;

const byte filas = 4;
const byte columnas = 3;
const byte rowsPins[filas] = { 42, 43, 44, 45 };
const byte columnsPins[columnas] = { 49, 48, 47};

char teclas[filas][columnas] = {
              {'1','2','3'},
              {'4','5','6'},
              {'7','8','9'},
              {'*','0','#'}
};


Keypad teclado = Keypad(makeKeymap(teclas), rowsPins, columnsPins, filas, columnas);
char tecla;


void setup(){
  Serial.begin(9600);
  DDRA = B11111111;
  DDRC = B00000001;
  PORTC= B11111000;
  DDRL = B00001111;
  PORTL= B11111111;
  
  Serial3.begin(9600);
  clearLCD();
  
}


void clearLCD(){
    Serial3.write(0xFE); Serial3.write(0x51);
    Serial3.write(0xFE); Serial3.write(0x46);
}



void loop(){

  if (mostrarMenu) {
      Serial.println("Pulsa el boton del centro para tocar Fur Elise de Beethoven");
      Serial.println("Pulsa la tecla 1 para tocar un DO");
      Serial.println("Pulsa la tecla 2 para tocar un RE");
      Serial.println("Pulsa la tecla 3 para tocar un MI");
      Serial.println("Pulsa la tecla 4 para tocar un FA");
      Serial.println("Pulsa la tecla 5 para tocar un SOL");
      Serial.println("Pulsa la tecla 6 para tocar un LA");
      Serial.println("Pulsa la tecla 7 para tocar un SI");
      Serial.println("Pulsa la tecla 8 para tocar un DO'");
      mostrarMenu = false;
  }




  if (!digitalRead(33)) { // Si pulsamos botón dle centro : Melodía Fur Elise
    Serial3.write("Tocando Fue Elise de Beethoven");
    furElise();
    clearLCD();
  } 

  switch (teclado.getKey()) {
    case '1':
        Serial3.write("Tocando la nota DO");
        delay(1000);
        emitirSonido(DO);
        clearLCD();
    break;

    case '2':
        Serial3.write("Tocando la nota RE");
        delay(1000);
        emitirSonido(RE);
        clearLCD();
    break;
    
    case '3':
        Serial3.write("Tocando la nota MI"); 
         delay(1000);
        emitirSonido(MI);
        clearLCD();
    break;

    case '4':
        Serial3.write("Tocando la nota FA");
         delay(1000);       
        emitirSonido(FA);
        clearLCD();
        
    break;

    case '5':
        Serial3.write("Tocando la nota SOL");
        delay(1000);
        emitirSonido(SOL);
        clearLCD();
    break;  

   case '6':
        Serial3.write("Tocando la nota LA");
         delay(1000);       
        emitirSonido(LA);
        clearLCD();
    break;

    case '7':
        Serial3.write("Tocando la nota SI");
        delay(1000);      
        emitirSonido(SI);
        clearLCD();
    break;

    case '8':
        Serial3.write("Tocando la nota DO'");
        delay(1000);       
        emitirSonido(DO2);
        clearLCD();
    break; 
    
  }

  
}




void furElise() {
  delay(600);
  tone(37, 329.63, 300);
  delay(350);
  tone(37, 311.13, 300);
  delay(350);
  tone(37, 329.63, 300);
  delay(350);
  tone(37,311.13, 300);
  delay(350);
  tone(37, 329.63, 300);
  delay(350);
  tone(37, 246.94, 300);
  delay(400);
  tone(37, 293.66,300);
  delay(400);
  tone(37, 261.63,300);
  delay(400);
  tone(37, 220, 900);
  delay(1000);
  tone(37,146.83, 300);
  delay(350);
  tone(37, 174.61, 300);
  delay(400);
  tone(37, 220, 300);
  delay(400);
  tone(37, 246.94, 900);
  delay(1000);
  tone(37, 174.61, 300);
  delay(400);
  tone(37, 233.08, 300);
  delay(400);
  tone(37, 246.94, 300);
  delay(400);
  tone(37, 261.63, 900);
  delay(1000);
  delay(300);
  tone(37, 329.63, 300);
  delay(400);
  tone(37, 311.13, 300);
  delay(400);
  tone(10, 329.63, 300);
  delay(400);
  tone(10, 311.13, 300);
  delay(400);
  tone(10, 329.63, 300);
  delay(400);
  tone(10, 246.94, 300);
  delay(400);
  tone(10, 293.66, 300);
  delay(400);
  tone(10, 261.63, 300);
  delay(400);
  tone(10, 220, 900);
  delay(1000);
  tone(10, 146.83, 300);
  delay(400);
  tone(10, 174.61, 300);
  delay(400);
  tone(10, 220, 300);
  delay(400);
  tone(10, 246.94, 900);
  delay(1000);
  tone(10, 174.61, 300);
  delay(400);
  tone(10, 261.63, 300);
  delay(400);
  tone(10, 246.94, 300);
  delay(400);
  tone(10, 220, 900);
  delay(1000);
  tone(10,246.94, 300);
  delay(400);
  tone(10, 261.63, 300);
  delay(400);
  tone(10, 293.66, 300);
  delay(400);
  tone(10, 329.63, 900);
  delay(1000);
  tone(10, 196, 300);
  delay(400);
  tone(10, 349.23, 300);
  delay(400);
  tone(10, 329.23, 300);
  delay(400);
  tone(10, 293.63, 900);
  delay(1000);
  tone(10,164.81, 300);
  delay(400);
  tone(10, 329.63, 300);
  delay(400);
  tone(10, 293.63, 300);
  delay(400);
  tone(10, 261.63, 900);
  delay(1000);
  tone(10, 146.83, 300);
  delay(400);
  tone(10, 293.63, 300);
  delay(400);
  tone(10, 261.63, 300);
  delay(400);
  tone(10, 246.94, 900);
  delay(1000);
  delay(400);
  tone(10, 329.63, 300);
  delay(400);
  tone(10, 311.13, 300);
  delay(350);
  tone( 10, 329.63, 300);
  delay(350);
  tone( 10,311.13, 300);
  delay(350);
  tone(10, 329.63, 300);
  delay(350);
  tone( 10, 246.94, 300);
  delay(400);
  tone(10, 293.66,300);
  delay(400);
  tone(10, 261.63,300);
  delay(400);
  tone(10, 220, 900);
  delay(1000);
  tone(10,146.83, 300);
  delay(350);
  tone(10, 174.61, 300);
  delay(400);
  tone(10, 220, 300);
  delay(400);
  tone(10, 246.94, 900);
  delay(1000);
  tone(10, 174.61, 300);
  delay(400);
  tone(10, 233.08, 300);
  delay(400);
  tone(10, 246.94, 300);
  delay(400);
  tone(10, 261.63, 900);
  delay(1000);
  delay(300);
  tone(10, 329.63, 300);
  delay(400);
  tone(10, 311.13, 300);
  delay(400);
  tone(10, 329.63, 300);
  delay(400);
  tone(10, 311.13, 300);
  delay(400);
  tone(10, 329.63, 300);
  delay(400);
  tone(10, 246.94, 300);
  delay(400);
  tone(10, 293.66, 300);
  delay(400);
  tone(10, 261.63, 300);
  delay(400);
  tone(10, 220, 900);
  delay(1000);
  tone(10, 146.83, 300);
  delay(400);
  tone(10, 174.61, 300);
  delay(400);
  tone(10, 220, 300);
  delay(400);
  tone(10, 246.94, 900);
  delay(1000);
  tone(10, 174.61, 300);
  delay(400);
  tone(10, 261.63, 300);
  delay(400);
  tone(10, 246.94, 300);
  delay(400);
  tone(37, 220, 900);
  delay(1000);
  delay(5000);
}


void emitirSonido(long frecuency){
  noTone(20);
  tone(37, frecuency, 50);
  delay(50);
  noTone(37);
  tone(20,100);
}

