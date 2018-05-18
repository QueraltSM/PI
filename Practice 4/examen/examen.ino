int unidades = 0;
int decenas = 0;
int frecuencia = 200;
int display=1;
boolean asterisco = false;
const int numeros[]  {0x3F, 0x06,0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const int segmentos[] {1, 2, 4, 8, 16, 32};

boolean asteriscoAlmohadilla = false;

void setup(){
  Serial.begin(9600);
  
	DDRA = B11111111;
	DDRC = B00000001;
	PORTC= B11111000;
	DDRL = B00001111;
	PORTL= B11111111;
  
   tone(20,100);
   attachInterrupt(2,interrupt,CHANGE);

 }

void loop(){
  boolean arriba = digitalRead(34);
  boolean abajo = digitalRead(31);

  
	if (!abajo){
    decrementarContador();
    emitirSonido();
  }  


	if(!arriba){ 
    incrementarContador();
    emitirSonido();
  }


  if(!arriba && !abajo){ 
    resetearContador();
    emitirSonido();
  }  
  delay(50);
}


void resetearContador(){
    unidades = 0;
    decenas = 0; 
}

void incrementarContador() {
    if(unidades == 9){
      if(decenas == 9){
        decenas=0;
    }else{
      decenas++;
    }
        unidades = 0;
    }else{
        unidades++;
    }
}

void decrementarContador() {
    if(unidades==0){
      if(decenas ==0){
        decenas=9;
    }else{
        decenas--;
    }
      unidades=9;
    }else{
      unidades--;
    }
}


void emitirSonido(){
  noTone(20);
  tone(37, frecuencia, 50);
  delay(50);
  noTone(37);
  tone(20,100);
   
}


void mostrarDisplay(int display, int value){
  digitalWrite(47, HIGH); 
  digitalWrite(48, HIGH);
  digitalWrite(49, HIGH);
 
  if(display == 47){
    PORTA = value;
  }else {
    PORTA = numeros[value];
  }
  digitalWrite(display,0);
}


void interrupt(){
  if(display == 1){
    mostrarDisplay(49,unidades);
    leerTeclado(1);
    display++;
  }else if(display == 2){
    mostrarDisplay(48,decenas);
    leerTeclado(2);
    display++;
  }else{
    mostrarDisplay(47,0);
    leerTeclado(3);
    display = 1;
  }
}

void leerTeclado(int columna){
  if(columna == 1){
    columna1();
  } else if(columna == 2){  
    columna2();  
  } else if(columna == 3){
    columna3();
   }
}

void columna1() {
        if (digitalRead(42) == 0 && asterisco){ // 1
            frecuencia = 200;
            asterisco= false;
            asteriscoAlmohadilla = false;
    } 
    
        if (digitalRead(43) == 0 && asterisco){ // 4
            frecuencia = 800;
            asterisco= false;
            asteriscoAlmohadilla = false;
        } 
    
        if (digitalRead(44) == 0 && asterisco){ // 7
            frecuencia = 1400;
            asterisco= false;
            asteriscoAlmohadilla = false;
        } 
        if (digitalRead(45) == 0){ // *
            asterisco= true; 
            asteriscoAlmohadilla = true;
        }
}


void columna2() {
    if (digitalRead(42) == 0 && asterisco){ // 2
      frecuencia = 400;
      asterisco= false;
      asteriscoAlmohadilla = false;
    } 
  
    if (digitalRead(43) == 0 && asterisco){ // 5
      frecuencia = 1000;
      asterisco= false;
      asteriscoAlmohadilla = false;
    } 
  
    if (digitalRead(44) == 0 && asterisco){ // 8
      frecuencia = 1600;
      asterisco= false;
      asteriscoAlmohadilla = false;
    } 
  
    if (digitalRead(45) == 0 && asterisco){ // 0
      frecuencia = 0;
      asterisco= false;
      asteriscoAlmohadilla = false;
    } 
}


void columna3() {
    if (digitalRead(42) == 0 && asterisco){ // 3
      frecuencia = 600;
      asterisco= false;
      asteriscoAlmohadilla = false;
    } 
  
    if (digitalRead(43) == 0 && asterisco){ // 6
      frecuencia = 1200;
      asterisco= false;
      asteriscoAlmohadilla = false;
    } 
  
    if (digitalRead(44) == 0 && asterisco){ // 9
      frecuencia = 1800;
      asterisco= false;
      asteriscoAlmohadilla = false;
    }

    if (digitalRead(45) == 0 && asteriscoAlmohadilla) { // #
      gusano();
    }
}




void displayParpadear() {
  int j = 0;
  while (j<2) { // Parpadear 3 veces
    int i = 0; 
    // Encendemos display
    while (i < 200) {
      mostrarDisplay(49,0);
      delay(5);
      digitalWrite(49,1);
      mostrarDisplay(48,0);
      delay(5);    
      i++;
    }
    
    // Apagamos display
    i = 0;
    while (i < 10000) {
      digitalWrite(49,1);  
      digitalWrite(48,1);
      i++;
    }
    j++;
  }
}



void encenderLeds() {
  int i = 0;
  while (i<6) {
    digitalWrite(48,1);
    digitalWrite(47,1);
    PORTA = segmentos[i];
    digitalWrite(49,0);
    delay(150000);  
    digitalWrite(49,1);  
    delay(100);
    i++;
  }
}

void gusano() {
  int i = 0;
  while (i<2) {
    encenderLeds();
    delay(10000);
    i++;
  }

  displayParpadear();
}


