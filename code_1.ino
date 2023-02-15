
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



char auth[] = "ZPhgIX9tDWZ4JsIer5FYjdtzjbBn4RSB";//Enter your Auth token
char ssid[] = "Kishore";//Enter your WIFI name
char pass[] = "mamu12345";//Enter your WIFI password

BlynkTimer timer;
bool Relay = 0;


#define sensor A0
#define waterPump D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);


  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);


  timer.setInterval(100L, soilMoistureSensor);
}


BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);

  } else {
    digitalWrite(waterPump, HIGH);

  }
}


void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);


}

void loop() {
  Blynk.run();
  timer.run();
}