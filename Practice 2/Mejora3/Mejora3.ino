const int SCL_L=2; 
const int SDA_L=3; 
const int SCL_E=4; 
const int SDA_E=5; 


void setup(){
  Serial.begin(9600);  
  pinMode(SDA_L,INPUT);   
  pinMode(SCL_L,INPUT);
  pinMode(SDA_E,OUTPUT);  
  pinMode(SCL_E,OUTPUT);
  
  digitalWrite(SDA_E,1);  
  digitalWrite(SCL_E,1);
  pinMode(13,OUTPUT);
  digitalWrite(13,0);
}


int guardarValorEnMemoria(int memoria,int dato){
  do{
    START();
    enviarDirecDispositivo(); 
    E_BIT_0();                   // R/W = 0 = (Escritura)
  }while(R_BIT());
  enviar(memoria);
  if(R_BIT()) return -1;
  enviar(dato);
  if(R_BIT()) return -1;
    STOP();
    return 0;
}

int leerValorDeMemoria(int memoria){
    START();
    enviarDirecDispositivo(); 
    E_BIT_0();                   // R/W = 0 = (Escritura)
  if(R_BIT()) return -1;
  enviar(memoria);
  if(R_BIT()) return -1;
    START();
    enviarDirecDispositivo(); 
    E_BIT_1();                   // R/W = 1 = (Lectura)
  if(R_BIT()) return -1;
    Serial.println(obtenerDato(), DEC);
    STOP();
    return 0;
}


void conBin(int num,int datosEnDecimal[]){
  int i = 7;
  while(num > 1){
    datosEnDecimal[i] = num%2;
    num = num/2;
    i--;
  }
  datosEnDecimal[i] = num;
}

int conDec(int datoEnBinario[]){
    int num = 0;
    int potencia=1;
    for(int i = 0; i < 8 ;i++){
        if(datoEnBinario[i] == 1){
            for(int j = i ; j < 7 ; j++){
                potencia = potencia*2;
            }
            num = potencia + num;
            potencia=1;
        }
    }
    return num;
}
void enviar(int num){
  int enBinario[8]={0,0,0,0,0,0,0,0};
  conBin(num,enBinario);
  for(int i = 0 ; i < 8 ;i++){
    if(enBinario[i] == 0){
      E_BIT_0();
    }else{
      E_BIT_1();
    }
  }
}
int obtenerDato(){
  int datoEnBinario[8]={0,0,0,0,0,0,0,0};
  for(int i = 0 ; i < 8 ; i++){
    datoEnBinario[i]=R_BIT();
  }
  return conDec(datoEnBinario);
}

void enviarDirecDispositivo(){
  E_BIT_1();E_BIT_0();E_BIT_1();E_BIT_0();E_BIT_0();E_BIT_0();E_BIT_0();
}

void START(){
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,1);
    while(digitalRead(SCL_L) == 0 || digitalRead(SDA_L) == 0){/*esperar*/}
  digitalWrite(SDA_E,0);
  digitalWrite(SCL_E,1);
  digitalWrite(SDA_E,0);
  digitalWrite(SCL_E,0);
}

void STOP(){
  digitalWrite(SDA_E,0);
  digitalWrite(SCL_E,0);
  digitalWrite(SDA_E,0);
  digitalWrite(SCL_E,1);
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,1);
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,1);
}

void E_BIT_1(){
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,0);
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,1);
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,1);
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,0);
}

void E_BIT_0(){
  digitalWrite(SDA_E,0);
  digitalWrite(SCL_E,0);
  digitalWrite(SDA_E,0);
  digitalWrite(SCL_E,1);
  digitalWrite(SDA_E,0);
  digitalWrite(SCL_E,1);
  digitalWrite(SDA_E,0);
  digitalWrite(SCL_E,0);
}

int R_BIT(){
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,0);
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,1);
    while(digitalRead(SCL_L) == 0){/*esperar*/}
    int Dato=digitalRead(SDA_L);
  digitalWrite(SDA_E,1);
  digitalWrite(SCL_E,0);
    return Dato; //devolver ACK
}                     


int readNum(){
    char clearBuffer = ' ';
    while (Serial.available() == 0){/*Espera hasta que el buffer de entrada tenga un caracter*/}
    int num = Serial.parseInt();
    while (Serial.available() > 0){
        clearBuffer = Serial.read();  
    }
    return num;
}

void generarFiguras(){
  int figura1 = random(0,2);
  int figura2 = random(0,2);
  
  String jugador1 = "";
  String jugador2 = "";
  
  switch(figura1) {
    case 0:
      jugador1 = "piedra";
      break;
    case 1:
      jugador1 = "papel";
      break;    
    default:
      jugador1 = "tijera";
      break;
    break;
  }
  
  Serial.print("El jugador 1 ha sacado ");
  Serial.println(jugador1);
  
  switch(figura2) {
    case 0:
      jugador2 = "piedra";
      break;
    case 1:
      jugador2 = "papel";
      break;    
    default:
      jugador2 = "tijera";
      break;
    break;
  }
  
  Serial.print("El jugador 2 ha sacado ");
  Serial.println(jugador2);
  
  resultado(jugador1, jugador2);  
}

void ganador(int jugador) {
  Serial.print("El ganador esta vez es el jugador numero ");
  Serial.println(jugador);
}

void resultado(String jugador1, String jugador2) {
  if (jugador1 == jugador2) {
    Serial.println("¡Empate!");
  } else {
    if (jugador1 == "piedra") {
        if (jugador2 == "papel") {
          ganador(2);         
        } else {
          ganador(1);         
        }
    }


    if (jugador1 == "papel") {
       if (jugador2 == "piedra") {
          ganador(1);         
        } else {
          ganador(2);
        }
    }

      if (jugador1 == "tijera") {
         if (jugador2 == "piedra") {
          ganador(2);         
        } else {
          ganador(1);
        } 
      }
  }
}


void mostrarMemoria() {
  int i = 0;
    while(i < 128){
        Serial.print("Posicion = ");
        Serial.print(i);
        Serial.print("  Valor = ");
    leerValorDeMemoria(i);
        Serial.println("");
        i++;
    }
}

void generarNumerosImpares() {
  int i = 0;
  while (i<128) {
    int numero = random(0,100);
    if ((numero%2)!=0) {
          guardarValorEnMemoria(i,numero);
      i++;
    }
  }
}

void generarNumerosPares() {
  int i = 0;
  while (i<128) {
    int numero = random(0,100);
    if ((numero%2)==0) {
          guardarValorEnMemoria(i,numero);
      i++;
    }
  }
}


void generarNumerosAleatorios() {
  int i = 0;
  while (i<128) {
    guardarValorEnMemoria(i,random(0,100));
    i++;
  }
}


void loop(){
    Serial.flush();
    Serial.println("Pulsa 1 para ver el contenido de la memoria");  
    Serial.println("Pulsa 2 para generar numeros aleatorios entre 0 y 100");
    Serial.println("Pulsa 3 para generar numeros aleatorios impares entre 0 y 100");
    Serial.println("Pulsa 4 para generar numeros aleatorios pares entre 0 y 100");
    Serial.println("Pulsa 5 para jugar a piedra, papel o tijera");
    
	digitalWrite(13,1);
  
    switch (readNum()){
    case 1: 
        Serial.println("Mostrando el contenido de los 128 bytes de memoria: ");
    		mostrarMemoria();
		break;
		
    case 2:
		Serial.println("Generando numeros aleatorios...");
		generarNumerosAleatorios();
		Serial.println("Memoria actualizada");
		break;
      
    case 3:
		Serial.println("\nGenerando numeros aleatorios impares...");
		generarNumerosImpares();
      break;
      
      case 4:
		Serial.println("\nGenerando numeros aleatorios pares...");
		generarNumerosPares();
      break;
	  
	  case 5:
	  Serial.println("\nEmpezamos el juego de piedra, papel o tijera...");
		generarFiguras();
	  
	  break;
      
       default  :
            Serial.println("Valor incorrecto");
      
    }
  
    digitalWrite(13,0);
    Serial.println("");
}
