const int numbers[] {0x3F, 0x06,0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
String d1 = "";
String d2 = "";
String d3= "";
String d4 = "";

void setup(){
  Serial.begin(9600);
  DDRA = B11111111;
  DDRC = B00000001;
  PORTC= B11111000;
  DDRL = B00001111;
  PORTL= B11111111;
 }

void showDisplay(int disp, int value){
   PORTA = numbers[value];
   digitalWrite(disp,0);
}

 void getAndShowNumber(String numero) {
  switch(numero.length()) {
    case 1:
      showDisplay(49, numero.toInt());
      delay(3000);
      digitalWrite(49,1);
      break;

    case 2:

      for (int i = 0; i<300; i++) {
          d1 = numero.charAt(0);
          showDisplay(48,d1.toInt());
          delay(5);
          digitalWrite(48,1);

          d2 = numero.charAt(1);  
          showDisplay(49,d2.toInt());
          delay(5);
          digitalWrite(49,1);
      }

    break;

    case 3:

      for (int i = 0; i<300; i++) {
          d1 = numero.charAt(0);
          showDisplay(47,d1.toInt());
          delay(5);
          digitalWrite(47,1);

          d2 = numero.charAt(1);  
          showDisplay(48,d2.toInt());
          delay(5);
          digitalWrite(48,1); 

          d3 = numero.charAt(2);  
          showDisplay(49,d3.toInt());
          delay(5);
          digitalWrite(49,1);
      }
                      
        break;

    case 4:

      for (int i = 0; i<300; i++) {
        
          d1 = numero.charAt(0);
          showDisplay(46,d1.toInt());
          delay(5);
          digitalWrite(46,1);
          
          d2 = numero.charAt(1);
          showDisplay(47,d2.toInt());
          delay(5);
          digitalWrite(47,1);

          d3 = numero.charAt(2);  
          showDisplay(48,d3.toInt());
          delay(5);
          digitalWrite(48,1); 

          d4 = numero.charAt(3);  
          showDisplay(49,d4.toInt());
          delay(5);
          digitalWrite(49,1);
      }             
        break;
      }
  }
  

 void loop(){
    Serial.println("Introduce un numero de entre 1 y 4 digitos: ");
    while (Serial.available()==0) {}
    String numero = Serial.readString();  
    Serial.print("Numero introducido es ");
    Serial.println(numero);
    if ((numero.length() >= 5) || (numero.indexOf("-") >= 0)) {
       Serial.println("Numero invalido\n\n");
    } else {
      Serial.println("Mostrando en el display de 7 segmentos...");
      getAndShowNumber(numero); 
      delay(400);  
      Serial.println("Display reseteado\n\n");   
    }
  }

