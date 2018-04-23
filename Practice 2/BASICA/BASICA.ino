const int SCL_L=2; 
const int SDA_L=3; 
const int SCL_E=4; 
const int SDA_E=5;

int flag=0;
  
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

void loop(){
    Serial.flush();
    Serial.println("Pulsa 1 para guardar un valor en una posicion de memoria");  
    Serial.println("Pulsa 2 para leer una posicion de memoria");
    Serial.println("Pulsa 3 para inicializar toda la memoria a un valor");
    Serial.println("Pulsa 4 para mostrar el contenido de toda la memoria en decimal");
    Serial.println("Pulsa 5 para inicializar un rango en de la memoria");
    Serial.println("Pulsa 6 para leer un rango en de la memoria");
    Serial.println("Pulsa 7 para mostrar el contenido de toda la memoria en hexadecimal y en 8 columnas");
    

  digitalWrite(13,1);
  
  int dato = 0;
  int mem = 0;
  int i = 0;
  int memFinal = 0;

  
    switch (readNum()){
        case 1 :
            Serial.println("Introduce un valor de 0 a 255 (dato): ");
           dato = readNum();
           
            if(dato < 0 || dato > 255){
                Serial.println("Valor incorrecto");
            }else{
                Serial.print("Valor introducido: ");Serial.println(dato);
                Serial.println("Introduce un valor de 0 a 127 (memoria)");
                int mem = readNum();
                
                if(mem < 0 || mem > 127){
                    Serial.println("Valor incorrecto");
                }else{
                    Serial.print("Valor introducido: ");Serial.println(mem);
                    guardarValorEnMemoria(mem,dato);
                    Serial.println("Valor guardado");
                }
            }
            break;

            
        case 2 :
            Serial.println("Introduce un valor de 0 a 127 (memoria): ");
            dato = readNum();
            if(dato < 0 || dato > 127){
                Serial.println("Valor incorrecto");
            } else{
                leerValorDeMemoria(dato);
            }
            break;

            
       case 3 :
            Serial.println("Introduce un valor de 0 a 255 (dato): ");
            dato = readNum();
            if(dato < 0 || dato > 255){
                Serial.println("Valor incorrecto");
            }else{
        Serial.print("Valor introducido: ");Serial.println(dato);
                Serial.println("Actualizando memoria...");
                while(i < 128){
                    guardarValorEnMemoria(i,dato);
                    i++;
                }
                Serial.println("Memoria actualizada");
            }
           break;

           
       case 4 :
            Serial.println("Mostrando el contenido de los 128 bytes de memoria: ");
            while(i < 128){
                leerValorDeMemoria(i);
                i++;
            }
            break;

            
     case 5 :
            Serial.println("Introduce un valor de 0 a 255 (dato): ");
            dato = readNum();
            if(dato < 0 || dato > 255){
                Serial.println("Valor incorrecto");
            }else{
        Serial.print("Valor introducido: ");Serial.println(dato);
        Serial.println("Introduce un valor de 0 a 127 (memoria) como inicio del rango");
        mem = readNum();
                if(mem < 0 || mem > 127){
                    Serial.println("Valor incorrecto");
                }else{
          Serial.print("Valor introducido: ");Serial.println(mem);
                    Serial.println("Introduce otro valor de 0 a 127 (memoria) como final del rango");
          int memFinal = readNum();
          
          if(memFinal < 0 || memFinal > 127 || memFinal < mem){
            Serial.println("Valor incorrecto");
          }else{
            Serial.print("Valor introducido: ");Serial.println(memFinal);
            i = mem;
            Serial.println("Actualizando memoria...");
            while(i <= memFinal){
              guardarValorEnMemoria(i,dato);
              delay(20);
              i++;
            }
            Serial.println("Memoria actualizada");
          }
                }
            }
      break;
     case 6 :
            Serial.println("Introduce un valor de 0 a 127 (memoria) como inicio del rango");
            mem = readNum();
            if(mem < 0 || mem > 127){
                Serial.println("Valor incorrecto");
            }else{
        Serial.print("Valor introducido: ");Serial.println(mem);
        Serial.println("Introduce un valor de 0 a 127 (memoria) como final del rango");
        memFinal = readNum();
                if(memFinal < 0 || memFinal > 127 || memFinal < mem){
                    Serial.println("Valor incorrecto");
                }else{
          Serial.print("Valor introducido: ");Serial.println(mem);
          int bytes = memFinal-mem;
          Serial.print("Mostrando el contenido de los ");
          Serial.print(bytes);
          Serial.println(" bytes de memoria: ");
          i = mem;
          while(i <= memFinal){
            leerValorDeMemoria(i);
            i++;
          }
                }
            }
      break;

      case 7:
         Serial.println("Mostrando el contenido de los 128 bytes de memoria: ");
            while(i < 128){
                flag=1;
                if ((i%8) == 0) {
                  Serial.println("");
                } 
                   leerValorDeMemoria(i);
                 
                i++;
            }

      break;

      
       default  :
            Serial.println("Valor incorrecto");
    }
  digitalWrite(13,0);
  Serial.println("");
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
  
    if (flag==0) {
    Serial.print("Numero leido en la posicion ");
    Serial.print(memoria);
    Serial.print(": ");
    Serial.println(obtenerDato());
    } else {
          Serial.print(obtenerDato(), HEX);
          Serial.print("   ");
          flag=0;
    }
    
  STOP();
    return 0;
}

int readNum(){
    char clearBuffer = ' ';
    while (Serial.available() == 0){/*Espera hasta que el buffer de entrada tenga un caracter*/}
    int num = Serial.parseInt();
    while (Serial.available() > 0){
        clearBuffer = Serial.read();  //limpia el buffer de teclado
    }
    return num;
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