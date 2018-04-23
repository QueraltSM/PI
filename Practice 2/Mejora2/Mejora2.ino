int filas = 0;
int columnas = 0;

#include <EEPROM.h>

int cuadrada = 0;

void setup(){
      Serial.begin(9600); 
      pinMode(13,OUTPUT);
      digitalWrite(13,0);  
}


void loop(){
    Serial.flush(); 
 
    resetEPROM();
    
    Serial.println("\n\nPulsa 1 : Inicializar diagonal de una matriz"); 
    Serial.println("Pulsa 2 : Obtener minimo y maximo valores de una matriz"); 
	  Serial.println("Pulsa 3 : Multiplicar una matriz por un escalar");

    switch (readValue()){
      
    case 1:
    
      Serial.println("\n--- INICIALIZAR DIAGONAL DE UNA MATRIZ ---");

      if (getRowsColumns()) {
        
          if (filas != columnas) {
          Serial.println("No se puede diagonalizar la matriz porque no es cuadrada.");  
          cuadrada = 0;
          
          } else {
            getMatrix(filas, columnas);
            cuadrada = 1;   
            Serial.print("\n\nIntroduce un valor para la diagonal: ");
            int8_t diagonal = readValue();
            Serial.print("\n\nDiagonal introducida = ");
            Serial.println(diagonal);
            diagonalizar(diagonal);
        }    
      } 
      
    break;
      
    case 2:
    
      Serial.println("\n--- OBTENER MINIMO Y MAXIMO VALOR DE UNA MATRIZ ---");
      if (getRowsColumns()) {
          getMatrix(filas, columnas);
          Serial.println("\n\nEl minimo y maximo valor de la matriz son: ");
          calcularMinMax();
      }

    break;
      
    case 3:
      Serial.println("\n--- MULTIPLICAR MATRIZ POR UN ESCALAR ---");
	    if (getRowsColumns()) {
          getMatrix(filas, columnas);
          Serial.println("\nIntroduce un escalar: "); 
          int8_t escalar = readValue();
          Serial.print("\nEscalar introducido = ");
          Serial.println(escalar);
          multiplicarEscalar(escalar);
          showMatrix();
	    }
    break;
    
    default:
    
      Serial.println("Opcion no valida.");
      
    break;
  } 

}

void resetEPROM() {
    int i = 0;
    while (i<128) {
       EEPROM.write(i, 0);
       i++;
    }
}


void multiplicarEscalar (int8_t escalar) {
  int i = 0;
  
  while (i<(filas*columnas)) {
    int8_t dato = EEPROM.read(i);
    int8_t multiplicacion = (dato*escalar);
    EEPROM.write(i,multiplicacion);
    i++;
  }
}


void calcularMinMax() {
    int i = 1;
    
    int8_t minimo =  EEPROM.read(0);
    int8_t maximo =  EEPROM.read(0);
    
    while (i<(filas*columnas)) {
       int8_t dato = EEPROM.read(i);

        if(minimo>dato) {
            minimo=dato;
         }

        if(maximo<dato){
          maximo=dato;
        }

        i++;
    }
      
      Serial.print("\nValor minimo = ");
      Serial.println(minimo);
      Serial.print("Valor maximo = ");
      Serial.println(maximo);
}


void diagonalizar(int8_t diagonal) {
    Serial.println("\nMatriz diagonalizada: ");
    int i = 0;
    int contador = 0;

    while (i<(filas*columnas)) {
            int8_t dato = 0;
            contador = (filas-i)+1;
            
            if ( ((i%(columnas+1))==0) || (i==0)) {
               
               dato = diagonal;
  
            } else {
                dato = EEPROM.read(i);
            }

             if ((i%columnas)==0) {
                Serial.println("");
            } 
            
            Serial.print(dato);
            Serial.print("  ");
            i++;
      }

      Serial.println("");
      
}

  void showMatrix() {
    Serial.print("\nMatriz resultante: ");
    int i = 0;
    
    while(i < (filas*columnas)) {
      
      if ((i%columnas)==0) {
          Serial.println("");
      } 
            int8_t dato = EEPROM.read(i);
            Serial.print(dato);
            Serial.print("  ");
      
      i++;
    }
  }


  void getMatrix(int filas, int columnas) {
    int i=0;

    while(i < (filas*columnas)) {
        Serial.print("Introduce valor en la posicion [");
        Serial.print(i);
        Serial.print("]: ");
        int8_t dato = readValue();
        Serial.println(dato);
        EEPROM.write(i,dato);
        i++;
    }
      showMatrix();
  }

  
	boolean getRowsColumns() {
		  Serial.print("\nIntroduce numero de filas de la matriz: ");
		  filas = readValue();
      Serial.print("\nNumero de filas = ");
      Serial.println(filas);
      
      if (filas <= 0) {
        Serial.println("\nNo se admiten matrices con menos de 1 fila.");
        return false;
      }
      
		  Serial.print("\nIntroduce numero de columnas de la matriz: ");
		  columnas = readValue();	
      Serial.print("\nNumero de columnas = ");
      Serial.println(columnas);
      
      if (columnas <= 0) {
        Serial.println("\nNo se admiten matrices con menos de 1 columna.");
        return false;
      }
      
      Serial.println("");
	}


int readValue(){
    char clearBuffer = ' ';
    while (Serial.available() == 0){/*Espera hasta que el buffer de entrada tenga un caracter*/}
    int num = Serial.parseInt();
    while (Serial.available() > 0){
        clearBuffer = Serial.read();  //limpia el buffer de teclado
    }
    return num;
}