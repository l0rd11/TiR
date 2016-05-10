  #include <Servo.h>
  

  int pos = 90;
  int vel;
  int hig;
  Servo myservo;
  Servo velocity;
  Servo hight;
  
  bool hasStarted = false;
  
    void setup()
    {
      Serial.begin(9600);
      Serial1.begin(115200); // wartość zależna od modułu, najczęściej 9600 lub 115200
      myservo.attach(10);
      velocity.attach(11);
      hight.attach(9);

          
      sendData("AT+RST\r\n",2000); // reset modułu
      sendData("AT+CWMODE=2\r\n",1000); // ustawienie w trybie Access Point
      sendData("AT+CWSAP=\"SIECTESTOWA\",\"HELLOWORLD\",5,3",1000);

      sendData("AT+CIFSR\r\n",1000); // Uzyskanie adresu IP (domyślnie 192.168.4.1)
      sendData("AT+CIPMUX=1\r\n",1000); // Tryb połączeń wielokrotnych
      sendData("AT+CIPSERVER=1,80\r\n",1000); // Ustawienie serwera na porcie 80
    }
     
    void loop()
    {
      if(!hasStarted)
      {
        velocity.write(35);
        myservo.write(90);
        hight.write(35);
      }
      if(Serial1.available()) // sprawdzenie czy moduł otzrymał dane 
      {
        if(Serial1.find("+IPD,"))
        {
         delay(10); // czekanie na zapełnienie bufora danymi
         hasStarted = true;
         Serial1.find("serwo="); // wyszukanie frazy "pin=" oraz ustawienie tam "kursora"
         
         char h = Serial1.read(); // pobranie pierwszej cyfry, np. dla pinu 13, pierwsza cyfra to 1, należy ją pomnożyć przez 10
         char v = Serial1.read();
         char a = Serial1.read();

         pos = int(a);

         if(pos < 0)
            pos = 127 + (pos + 127);
         
         //Serial.println(pos);

         //pos = 10;

          if(pos>180||pos<0){
            pos=90;
            Serial.println("Im wrong");
          }
          myservo.write(180-pos);

          //
          vel = int(v);
          Serial.println(vel);
          velocity.write(vel);


          //
          hig = int(h);
          hight.write(hig);
         
         // zamknięcie połączenia
//         String closeCommand = "AT+CIPCLOSE="; 
//         closeCommand+=connectionId; // ID połączenia odczytane na początku
//         closeCommand+="\r\n";
//         
//         sendData(closeCommand,100); 
        }
      }
    }
     
    /*
    * Funkcja wysyłająca komendy do modułu Serial1
    * Parametry:
    * command - komenda do wysłania
    * timeout - czas oczekiwania na odpowiedź
    */
    String sendData(String command, const int timeout)
    {
        String response = "";
        
        Serial1.print(command); // wysłanie polecenia do Serial1
        
        long int time = millis();
        
        while( (time+timeout) > millis())
        {
          while(Serial1.available()) //jeśli są jakieś dane z modułu, wtedy następuje ich odczyt
          {
            char c = Serial1.read(); // odczyt kolejnego znaku
            response += c;
          }  
        } 
        Serial.print(response);
        return response;
    }
