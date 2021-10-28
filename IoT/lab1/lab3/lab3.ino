// Example testing sketch for various DHT11, DHT21, DHT22 humidity/temperature sensors
// Written by Lin Wei Ting in National Taipei University of Technology Applied Network Laboratory. Taipei, Taiwan.

#include "LDHT.h"

#define DHTPIN 2          // what pin we're connected to
#define DHTTYPE DHT22     // using DHT22 sensor

LDHT dht(DHTPIN,DHTTYPE);

float tempC=0.0,Humi=0.0;

static const int DELAY_TIME = 7000;

void setup()
{
    Serial.begin(9600);
    dht.begin();
	
    Serial.print(DHTTYPE);
    Serial.println(" test!");

    Serial1.begin(9600);
    
}

void loop()
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    if(dht.read()) {
        tempC = dht.readTemperature();
        Humi = dht.readHumidity();

        Serial.println("------------------------------");
        Serial.print("Temperature Celcius = ");
        Serial.print(tempC);
        Serial.println("C");
        Serial.print("Humidity = ");
        Serial.print(Humi);
        Serial.println("%");

        String temp = "T" + String(tempC, 2);

        while (11 - temp.length())
          temp += "0";

        String payload = "AT+DTX=11,\"" + temp + "\"";
        Serial1.println(payload);
        Serial.println("Temperature payload: " + payload);

        delay(DELAY_TIME);

        int reply_length =Serial1.available();

        while (reply_length--) {
          Serial.print(char(int(Serial1.read())));
        }
        Serial.println("\n-----");

        String hum = "H" + String(Humi, 2);

        while (11 - hum.length())
          hum += "0";

        payload = "AT+DTX=11,\"" + hum + "\"";
        Serial1.println(payload);
        Serial.println("Humidity payload: " + payload);

        delay(DELAY_TIME);

        reply_length =Serial1.available();

        while (reply_length--) {
          Serial.print(char(int(Serial1.read())));
        }
        Serial.println("\n-----");
    }

    delay(500);
}
