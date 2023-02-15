#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#define sensorPin A1

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  pinMode(A0,INPUT);
  Serial.begin(9600);
  dht.begin(); // initialize the sensor

}

void loop()
{
int ldr_status=analogRead(A0);
if(ldr_status<575)
{
Serial.println(ldr_status);
Serial.println("Nitrogen is low");
}
else
{
Serial.println(ldr_status);
Serial.println("Nitrogen is high");
}
// wait a few seconds between measurements.
  delay(1200);

  // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht.readTemperature(true);


  //check if any reads failed
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) 
  {
   Serial.println("Failed to read from DHT sensor!");
  } 
  else 
  {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  "); 

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
  }
  
  Serial.print("Moisture content: ");
  int moisture=readSensor();
  Serial.println(moisture);
  
  if(moisture < 100)
  {
   
    digitalWrite(6,HIGH) ;   
  }
  else
  {
    
    digitalWrite(6,LOW) ;   
  }
  delay(100);
}
int readSensor() 
{
  int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor
  int outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
  return outputValue;
}