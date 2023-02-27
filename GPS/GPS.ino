#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

int led=13;
#define rxPin 2
#define txPin 3
SoftwareSerial wifi(rxPin,txPin); 

AltSoftSerial neogps;

TinyGPSPlus gps;

unsigned long previousMillis = 0;
long interval = 15000;


void setup()
{
  pinMode(led,OUTPUT);
  Serial.begin(115200);
  neogps.begin(9600);
  wifi.begin(115200);
  Serial.println("Iniciando...");
}

void loop()
{
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) 
    {
       previousMillis = currentMillis;
       sendGpsToServer();
    }
    if (wifi.available())
    {
      Serial.println(wifi.readString());
    }
}

int sendGpsToServer()
{
    boolean newData = false;
    for (unsigned long start = millis(); millis() - start < 5000;)
    {
      while (neogps.available())
      {
        if (gps.encode(neogps.read()))
        {
          newData = true;
          break;
        }
      }
    }
  
    if(true)
    {
      newData = false;
      
      String latitud, longitud;
  
      latitud = String(gps.location.lat(), 6); // Latitud en grados (double)
      longitud = String(gps.location.lng(), 6); // Longitud en grados (double)
      
      Serial.print("Latitud= "); 
      Serial.print(latitud);
      Serial.print(" Longitud= "); 
      Serial.println(longitud);
        
      String enviar, temp;
      enviar = (latitud + ";" + longitud);

      wifi.println(enviar);    
      delay(1000);

  }
  return 1;    
}
