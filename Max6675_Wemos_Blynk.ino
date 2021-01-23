#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SPI.h>

#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>  //https://github.com/YuriiSalimov/MAX6675_Thermocouple

#define SCK_PIN 3
#define CS_PIN 4
#define SO_PIN 5

Thermocouple* thermocouple;
BlynkTimer timer;

char auth[] = "---------";

char ssid[] = "------";
char pass[] = "------";


void sendSensor()
{
  const double celsius = thermocouple->readCelsius();
  Serial.print("Temp. = ");
  Serial.println(celsius);
  Blynk.virtualWrite(V4, celsius);

}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
