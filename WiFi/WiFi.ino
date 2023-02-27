#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "RR";
const char* password = "Rogger123";

float longitud = 0.0;
float latitud = 0.0;
void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Conectando...");
  }
}

void loop() 
{
  if (!Serial.available()){}
  else if (Serial.available())
  {
    enviarData();
    delay(2000);
  }
}

int enviarData()
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    leerData();
    const String url = ("http://pdcj01.000webhostapp.com/gpsdata.php?lat=" + String(latitud) + "&lng=" + String(longitud)); 
    Serial.println(url);
    WiFiClient client;
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode > 0) 
    {
      String payload = http.getString();
      Serial.println(payload);
    }
    http.end();
  }
}

int leerData()
{
  String recibo_str = Serial.readString();
  int recibo_len = recibo_str.length()+1;
  char recibo[recibo_len];
  recibo_str.toCharArray(recibo,recibo_len);
  bool flag = 0;
  int lati_len = 0;
  int longi_len = 0;

  for (int i=0 ; i <= recibo_len ; i++)
  {
    if (recibo[i] == ';')
    {
      flag = 1;
    }
    if (flag == 0)
    {
      lati_len++;
    }
  }
  longi_len = recibo_len - lati_len - 2;

  char lati[lati_len];
  char longi[longi_len];
  for (int i=0 ; i <= recibo_len ; i++)
  {
    if (i < lati_len)
    {
      lati[i] = recibo[i];
    }
    else if (i > lati_len)
    {
      longi[i - lati_len - 1] = recibo[i];
    }
  }

  
  String lati_str,longi_str;

  for (int i=0 ; i <= lati_len ; i++)
  {
    lati_str += lati[i];
  }

  for (int i=0 ; i <= longi_len ; i++)
  {
    longi_str += longi[i];
  }

  latitud = lati_str.toFloat();
  longitud = longi_str.toFloat();
}
