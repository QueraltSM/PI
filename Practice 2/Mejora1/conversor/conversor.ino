int bin[8]={0,0,0,0,0,0,0,0};
int dec[8]={0,0,0,0,0,0,0,0};  
int decimal = 0;
int i = 0;
const int SCL_L=2; 
const int SDA_L=3; 
const int SCL_E=4; 
const int SDA_E=5; 

uint8_t direccion = 0;

#include <EEPROM.h>

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

  EEPROM.get(0, direccion);
  
}

void loop(){
    Serial.flush(); 
    Serial.println("");
    Serial.println("Pulsa 1 : Binario - Decimal"); 
    Serial.println("Pulsa 2 : Decimal - Binario"); 
    Serial.println("Pulsa 3 : Ver resultados en memoria");

    switch (readValue()){
    case 1:
    
      Serial.println("");
      Serial.println("--- BINARIO A DECIMAL ---");
      
      if (introduceBin()) {
      
        Serial.print("Numero en decimal = ");
        int dato = binToDec(bin);
        Serial.println(dato);
        guardarValorMem(direccion, dato);
        
      }
  
      break;
      
    case 2:
    
      Serial.println("");
      Serial.println("--- DECIMAL A BINARIO ---");
      Serial.println("Introduce un numero decimal: ");
      decimal = readValue();
      if ((decimal < 0) ||(decimal > 255)) {
        Serial.println("Valor incorrecto. Ha de estar entre 0 y 255.");
        break;
      }
      Serial.print("Numero introducido = ");
      Serial.println(decimal);
      getBin(decimal);
      guardarValorMem(direccion, decimal);
      
    
    break;
      
    case 3:
      
      Serial.println("");
      Serial.println("--- RESULTADOS EN MEMORIA ---");
      Serial.println("Numeros almacenados en memoria: ");

      i=0;
      
      while(i < 128){
        if ((i % 8) == 0) {
             Serial.println("");
         }
                leerValorDeMemoria(i);
                i++;
            }
      
      Serial.println("");
      
    break;
    
    default:
    
      Serial.println("Opcion no valida.");
      
    break;
  } 

}

  void guardarValorMem(int memoria, int dato) {
    Serial.print("Pulsa 1 para guardar valor en memoria o 0 en caso contrario: ");

if (readValue() == 1) {
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

    EEPROM.put(0, ++direccion);
    Serial.println("Se ha guardado el dato en memoria");
    return 0;
    }
    
  }
  
  void enviarDirecDispositivo(){
  E_BIT_1();E_BIT_0();E_BIT_1();E_BIT_0();E_BIT_0();E_BIT_0();E_BIT_0();
}


int leerValorDeMemoria(int posicion){
    START();
    enviarDirecDispositivo(); 
    E_BIT_0();                   // R/W = 0 = (Escritura)
  if(R_BIT()) return -1;
  enviar(posicion);
  if(R_BIT()) return -1;
    START();
    enviarDirecDispositivo(); 
    E_BIT_1();                   // R/W = 1 = (Lectura)
  if(R_BIT()) return -1;
  
    Serial.print(obtenerDato());
    Serial.print("   ");

  STOP();
    return 0;
}

int obtenerDato(){
  int datoEnBinario[8]={0,0,0,0,0,0,0,0};
  for(int i = 0 ; i < 8 ; i++){
    datoEnBinario[i]=R_BIT();
  }
  return binToDec(datoEnBinario);
}

void enviar(int num){
  int enBinario[8]={0,0,0,0,0,0,0,0};
  decToBin(num,enBinario);
  for(int i = 0 ; i < 8 ;i++){
    if(enBinario[i] == 0){
      E_BIT_0();
    }else{
      E_BIT_1();
    }
  }
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

  
  boolean introduceBin() {
      int i = 0;
      while(i<8) {
        Serial.print("Introduce un 1 o un 0: ");
        int number = readValue();
        
        if ((number == 1) || (number == 0)) {
              bin[i]=number;
              Serial.print("Valor guardado [");
              Serial.print(number);
              Serial.println("]");
              
        } else {
              Serial.println("Valor incorrecto. Ha de ser un 1 o un 0");
              return false;
        }
        i++;
      }
      return true;
  }

  void getBin(int decimal) {
      Serial.print("Numero en binario = ");
      decToBin(decimal, bin);
      int i = 0;
      while (i<8) {
          Serial.print(bin[i]);
          i++;
      }
      Serial.println("");
  }

  int readValue(){
    char clear = ' ';  
    while (Serial.available() == 0){} 
    int value = Serial.parseInt(); 
    while (Serial.available() > 0){ 
      clear = Serial.read();  
    }
    return value;
  }
  
  int binToDec(int bin[]) {
    int value = 0;
    int pot = 1; 
    for(int i = 0; i < 8 ;i++){ 
      if(bin[i] == 1){ 
        for(int j = i ; j < 7 ; j++){
          pot = pot*2;  
        }
        value = pot + value; 
        pot = 1; 
      }
    }
    return value;
  }
  
  void decToBin(int value,int dec[]){
    int i = 7;
    while(value > 1){
      dec[i] = value%2;
      value = value/2;
      i--;
    }
    dec[i] = value;
  }


