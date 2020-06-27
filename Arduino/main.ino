/* 
   Código demonstrativo para a aula de Sistemas Embarcados,
   Curso de Ciência da Computação,
   EEP.
*/

#include "DHT.h"

#define DHTPIN A0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float umidade_ar = 0;
float temperatura_celsius = 0;
float temperatura_fahrenheit = 0;

void setup() {
  Serial.begin(9600);
  
  delay(2000);
  
  umidade_ar = dht.readHumidity();
  temperatura_celsius = dht.readTemperature();
  temperatura_fahrenheit = dht.readTemperature(true);
  
  delay(2000);

}

void loop(){

  umidade_ar = dht.readHumidity();
  temperatura_celsius = dht.readTemperature();
  temperatura_fahrenheit = dht.readTemperature(true);
  
  Serial.print("Umidade do Ar = ");
  Serial.print(umidade_ar);
  Serial.print(" %  ");  
  Serial.print("Temperatura = ");
  Serial.print(temperatura_celsius); 
  Serial.print(" Celsius  ");
  Serial.print("Temperatura = ");
  Serial.print(temperatura_fahrenheit); 
  Serial.println(" Fahrenheit  ");  

  //Não diminuir o valor abaixo. O ideal é a leitura a cada 2 segundos
  delay(2000); 
}
