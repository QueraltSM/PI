volatile int timer;
volatile int count;
volatile int display = 1;
volatile int unidades = 0;
volatile int decenas = 6;
boolean almohadilla = false;
const int numeros[]  {0x3F, 0x06,0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
String numeroLeido;
int flag = 0;
boolean arriba;
boolean abajo;
boolean jugando = false;
boolean menu = false;
volatile int numeroSecreto;
boolean mostrarDisplay47 = false;
volatile int aproximacion;
int contador = 0;
int dificultad;

void setup(){
  Serial.begin(9600);
  DDRA = B11111111;
  DDRC = B00000001;
  PORTC= B11111000;
  DDRL = B00001111;
  PORTL= B11111111;

// *****************************************************************
// disable interrupts
 cli();
 // modo normal de funcionamiento
 TCCR1A = 0;
 TCCR1B = 0;
 TCNT1 = 0; // cuenta inicial a cero
 // mode CTC
 TCCR1B |= (1<<WGM12);
 // prescaler N = 1024
 TCCR1B |= (1<<CS12)|(1<<CS10);
 // fintr = fclk/(N*(OCR1A+1)) --> OCR1A = [fclk/(N*fintr)] - 1
 // para fintr = 100Hz --> OCR1A = [16*10^6/(1024*100)] -1 = 155,25 --> 155

 OCR1A = 77; // para 200 Hz programar OCR1A = 77
 // enable timer1 compare interrupt
 TIMSK1 |=(1<<OCIE1A);
 // habilitamos interrupciones
 sei();
 randomSeed(analogRead(0));
// *****************************************************************
}

ISR(TIMER1_COMPA_vect){
// Aquí va la rutina de servicio a ejecutar: barrido teclado-display
// Se ejecuta cada 5ms (100Hz)
  if (jugando) {
        interrupt();
        if (timer == 200) { // 1 segundo
              timer = 0;
              count--;  
             if (count==0) {
                tiempoAgotado();
             }
             tone(37,100,50);
        } else {
          timer++;
        }
    }
}


void mostrarTempo(){
    if (flag == 0) {
      unidades = (count%10);
      mostrarDisplay(49,unidades);    
      flag=1;  
    } else if (flag==1) {
      decenas = (count/10);
      mostrarDisplay(48, decenas);
      flag = 0;
    } 
}


void displayParpadear() {
  int j = 0;
  while (j<10) {
    int i = 0; 
    // Encendemos display
    while (i < 25) {
      mostrarDisplay(49,0);
      delay(5);
      digitalWrite(49,1);
      mostrarDisplay(48,0);
      delay(5);    
      i++;
    }
    // Apagamos display
    i = 0;
    while (i < 2000) {
      digitalWrite(49,1);  
      digitalWrite(48,1);
      i++;
    }
    j++;
  }
}


void tiempoAgotado(){
  Serial.println("");Serial.println("El tiempo se ha acabado. Ha perdido :(");Serial.println("");
  emitirSonidoFallo();
  displayParpadear();
  delay(100);
  menu = false;
  jugando = false;
}


void interrupt(){
   if(display == 1){
    unidades = (count%10);
    mostrarDisplay(49,unidades);
    leerTeclado(1);
    display++;
  }else if(display == 2){
    decenas = ((count/10)%10);
    mostrarDisplay(48,decenas);
    leerTeclado(2);
    display++;
  } else {
    if (!mostrarDisplay47) { // No se tiene que mostrar el display 47
          mostrarDisplay(47,0);
    } else {
        mostrarDisplay(47,aproximacion);
         if (contador==150) {
          mostrarDisplay47 = false;
          contador = 0;
        } else {
          contador++;
        }
    }
    leerTeclado(3);
    display = 1;
  } 
}


void mostrarDisplay(int display, int value){
  digitalWrite(47, 1); 
  digitalWrite(48, 1);
  digitalWrite(49, 1);
  if(display == 47){
    PORTA = value;
  }else {
    PORTA = numeros[value];
  }
  digitalWrite(display,0);
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
        if (digitalRead(42) == 0 && !almohadilla){ // 1
          numeroLeido.concat("1"); 
          almohadilla = false;
          while(digitalRead(42)==0){}
        } 
    
        if (digitalRead(43) == 0 && !almohadilla){ // 4
          numeroLeido.concat("4"); 
          almohadilla = false;
          while(digitalRead(43)==0){}
        } 
    
        if (digitalRead(44) == 0 && !almohadilla){ // 7
          numeroLeido.concat("7"); 
          almohadilla = false;
          while(digitalRead(44)==0){}
        } 
}

void columna2() {
    if (digitalRead(42) == 0 && !almohadilla){ // 2
          numeroLeido.concat("2"); 
          almohadilla = false;
          while(digitalRead(42)==0){}
    } 
  
    if (digitalRead(43) == 0 && !almohadilla){ // 5
          numeroLeido.concat("5"); 
          almohadilla = false;
          while(digitalRead(43)==0){}
    } 
  
    if (digitalRead(44) == 0 && !almohadilla){ // 8
          numeroLeido.concat("8"); 
          almohadilla = false;
          while(digitalRead(44)==0){}
    } 
  
    if (digitalRead(45) == 0 && !almohadilla){ // 0
          numeroLeido.concat("0"); 
          almohadilla = false;
          while(digitalRead(45)==0){}
    } 
}

void columna3() {
    if (digitalRead(42) == 0 && !almohadilla){ // 3
          numeroLeido.concat("3"); 
          almohadilla = false;
          while(digitalRead(42)==0){}
    } 
  
    if (digitalRead(43) == 0 && !almohadilla){ // 6
          numeroLeido.concat("6"); 
          almohadilla = false;
          while(digitalRead(43)==0){}
    } 
  
    if (digitalRead(44) == 0 && !almohadilla){ // 9
          numeroLeido.concat("9"); 
          almohadilla = false;
          while(digitalRead(44)==0){}
    }

    if (!digitalRead(45)) { // #
      almohadilla = true;
      while (digitalRead(45)==0) {}
      comprobarNumero();
    }
}



void mostrarAproximacion(){
    mostrarDisplay47 = true; 
  if (numeroLeido.toInt()>numeroSecreto) {
     aproximacion = 0x8;
  } else {
    aproximacion = 0x1;
  }
  Serial.println("");
  Serial.println("Vuelve a intentarlo. Introduce un numero por teclado (por ejemplo: 2#) ");
  numeroLeido="";
  almohadilla = false;
  
}



void emitirSonidoFallo(){
    noTone(37);
    tone(37, 500, 300);  
}


void emitirSonidoVictoria(){
      noTone(37);
      tone(37,4000,300);
      noTone(37);
      tone(37,400,300);
      noTone(37);
      tone(37,40,300);
      noTone(37);
      tone(37,10,300);
      noTone(37);
      tone(37,3500,300);
}


void comprobarNumero(){
  if (numeroSecreto == numeroLeido.toInt()) {
    Serial.println("");
    Serial.println("Ha ganado la jugada :)");
    emitirSonidoVictoria();
    checkPuntuacion();
    menu = false;
    jugando = false;
    delay(100); 
    
  } else {
    Serial.println("");
    Serial.println("Ha fallado :(");
    emitirSonidoFallo();
    mostrarAproximacion();
  }
}


void comenzarPartida() {
  timer = 0;
  jugando = true;
}


void preguntaDificultad(){
    Serial.println("");Serial.println("Introduzca dificultad:");Serial.println("1 - Facil");Serial.println("2 - Medio");Serial.println("3 - Dificil");
    while (Serial.available() == 0) {}
    Serial.println("");
    
    switch(Serial.readString().toInt()){
      case 1:
        Serial.println("Ha comenzado la partida. Dificultad facil. Tiene 60 segundos. Mucha suerte :)");
        count=60;
        dificultad=1;
        break;
      case 2:
        Serial.println("Ha comenzado la partida. Dificultad media. Tiene 40 segundos. Mucha suerte :)");
        count = 40;
        dificultad=2;
        break;
      case 3:
        Serial.println("Ha comenzado la partida. Dificultad dificil. Tiene 20 segundos. Mucha suerte :)");
        count = 20;
        dificultad=3;
        break;
     default:
        Serial.println("Opcion invalida");
        preguntaDificultad();
        break;
    }  
}


void checkPuntuacion(){
    Serial.println("");
    Serial.print("Ha obtenido ");
    if (dificultad==1) {
        Serial.print(count);
    } else if (dificultad==2) {
      Serial.print(count*3);
    } else {
      Serial.print(count*8);
    }
    Serial.println(" puntos"); 
}


void loop() {
  arriba = digitalRead(34);
  abajo = digitalRead(31);
  
  if (!menu) {
    menu = true;
    Serial.println("");Serial.println("Bienvenido al juego"); Serial.println("Pulse el boton superior para comenzar la partida.");Serial.println("");
  }
  
  if (!arriba && !jugando) {
         preguntaDificultad();
         Serial.println("");
         Serial.println("Teclee un numero en el teclado (por ejemplo: 2#)");Serial.println("PISTA: El numero secreto se encuentra entre 0 y 99");
         numeroSecreto = random(0,99);
         numeroLeido = "";
         almohadilla = false;
         while (digitalRead(34)==0) {}
        comenzarPartida(); 
  }

  if (!arriba && !abajo && jugando) {
    Serial.println("");
    Serial.println("Ha parado el juego. Ha perdido :(");
    Serial.println("Gracias por jugar");Serial.println("");
    while ((digitalRead(34)==0) && (digitalRead(31)==0)) {}
    jugando = false;
    menu = false;
    delay(100);
  }
}
