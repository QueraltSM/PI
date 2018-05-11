const int numeros[] {0x3F, 0x06,0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
String d1 = "";
String d2 = "";
String d3= "";
String d4 = "";
String codigo = "";
int flag=0;

void setup(){
  Serial.begin(9600);
  
  Serial3.begin(9600);
  clearLCD();
  
  DDRA = B11111111;
  DDRC = B00000001;
  PORTC= B11111000;
  DDRL = B00001111;
  PORTL= B11111111;
 }

void showDisplay(int disp, int value){
   PORTA = numeros[value];
   digitalWrite(disp,0);
}

 void getAndShowNumber(String numero) {
  switch(numero.length()) {
    case 1:
      showDisplay(49, numero.toInt());
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
  

void clearLCD(){
    Serial3.write(0xFE); Serial3.write(0x51);
    Serial3.write(0xFE); Serial3.write(0x46);
}

void unlockAlarm() {
    Serial.println("Introduzca el codigo para desbloquear la alarma");
    while (Serial.available()==0) {}
    String c = Serial.readString();
    
    if (c == codigo) {
          Serial3.write("Codigo correcto");
          delay(5000);
          clearLCD();
         Serial.println("Aprieta el boton del centro para establecer una nueva clave");
         flag=2;
         
    } else {   

         Serial3.write("Intruso");
         delay(5000);
         clearLCD();

               
        for(int hz = 440; hz < 1000; hz++){
          tone(37, hz, 50);
          delay(5);
        }
 
      noTone(37);

        for(int hz = 1000; hz > 440; hz--){
          tone(37, hz, 50);
          delay(5);
        }
      noTone(37);
   } 
}

 void loop(){
     if (!digitalRead(33) && flag==1) {
         unlockAlarm();
      } else if ((!digitalRead(33) && flag==2) || (flag==0)) {
        setPassword();
      } 
  }


  void setPassword(){
    Serial.println("Introduce un codigo de 4 digitos: ");
    while (Serial.available()==0) {}
    codigo = Serial.readString();  
    if ((codigo.length() > 5) || (codigo.indexOf("-") >= 0)) {
       Serial3.write("Numero invalido");
       flag=0;
    } else {
      Serial3.write("Codigo almacenado");
      getAndShowNumber(codigo);
      delay(2000);
      clearLCD();
      flag=1;
      Serial.println("Pulsa el boton del centro para desbloquear la alarma");
    } 
  }
  

