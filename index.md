# Projeto 03
## Estação Meteorológica com acesso à Internet

Estação Meteorológica construída utilizando NODEMCU e o sensor DHT11. Alimentando a plataforma [ThingSpeak](thingspeak.com) para registro das informações e construções dos graficos abaixo.


##Sensores



#### Temperatura
<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1090302/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=50&title=+&type=spline&xaxis=Tempo&yaxis=Temperatura+%28%C2%BAC%29"></iframe>


<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1090302/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=50&title=+&type=spline&xaxis=Tempo&yaxis=Temperatura+%28%C2%BAF%29"></iframe>



#### Umidade Relativa

<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1090302/charts/3?bgcolor=%23ffffff&color=%233366ff&dynamic=true&results=60&title=Umidade+Relativa+&type=line&xaxis=Tempo&yaxis=%28%25%29"></iframe>




### Referencias

[Como Programar o ESP8266](https://www.filipeflop.com/universidade/aprenda-iot-em-casa-iniciante/aula-6-como-programar-o-esp8266-nodemcu/)

[Disponibilize Dados do tempo com o Sensor DHT11 e o ESP8266-nodemcu](https://www.filipeflop.com/universidade/aprenda-iot-em-casa-iniciante/aula-7-disponibilize-dados-do-tempo-com-o-sensor-dht11-e-o-esp8266-nodemcu/)



### Codigo Fonte (Arduino)

```c
#include <ESP8266WiFi.h> 
#include <DHT.h>
  
#define DHTPIN D1
  
#define SSID_REDE "" 
#define SENHA_REDE "" 
#define INTERVALO_ENVIO_THINGSPEAK 30000 
  

  
#define DHTTYPE DHT11 // DHT 11

char endereco_api_thingspeak[] = "api.thingspeak.com";
String chave_escrita_thingspeak = ""; 
unsigned long last_connection_time;
WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);
  

void envia_informacoes_thingspeak(String string_dados);
void init_wifi(void);
void conecta_wifi(void);
void verifica_conexao_wifi(void);
  

  
void envia_informacoes_thingspeak(String string_dados)
{
    if (client.connect(endereco_api_thingspeak, 80))
    {
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+chave_escrita_thingspeak+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(string_dados.length());
        client.print("\n\n");
        client.print(string_dados);
          
        last_connection_time = millis();
        Serial.println("- Informações enviadas ao ThingSpeak!");
    }
}
  

void init_wifi(void)
{
    Serial.println("------WI-FI -----");
    Serial.println("Conectando-se a rede: ");
    Serial.println(SSID_REDE);
    Serial.println("\nAguarde...");
  
    conecta_wifi();
}

void conecta_wifi(void)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }
      
    WiFi.begin(SSID_REDE, SENHA_REDE);
      
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }
  
    Serial.println("Conectado com sucesso a rede wi-fi \n");
    Serial.println(SSID_REDE);
}
  
void verifica_conexao_wifi(void)
{
    conecta_wifi();
}
  
void setup()
{
    Serial.begin(115200);
    last_connection_time = 0;
  
    dht.begin();
  
    init_wifi();
}
  
void loop()
{
    char fields_a_serem_enviados[100] = {0};
    float temperatura_cels_lida = 0.0;
    float temperatura_fahr_lida = 0.0;
    float umidade_lida = 0.0;
  
   
    if (client.connected())
    {
        client.stop();
        Serial.println("- Desconectado do ThingSpeak");
        Serial.println();
    }
  
    verifica_conexao_wifi();
      
    if( millis() - last_connection_time > INTERVALO_ENVIO_THINGSPEAK )
    {
        temperatura_cels_lida = dht.readTemperature();
        temperatura_fahr_lida =  dht.readTemperature(true);
        umidade_lida = dht.readHumidity();
        sprintf(fields_a_serem_enviados,"field1=%.2f&field2=%.2f&field3=%.2f", temperatura_cels_lida, temperatura_fahr_lida, umidade_lida);
        envia_informacoes_thingspeak(fields_a_serem_enviados);
    }
  
    delay(10);
}

```

