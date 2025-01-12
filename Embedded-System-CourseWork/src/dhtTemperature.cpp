#include "DHTTemperature.h"


const int DHT_PIN = 14;

DHT dht(DHT_PIN, DHT11);



DHTTemperature::DHTTemperature()
{
    
 
}

DHTTemperature::~DHTTemperature()
{
}

void DHTTemperature::dhtSetUP()
{
     dht.begin();
}

void DHTTemperature::dhtPrinter()
{
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    Serial.print(F(" Temperature: "));
    Serial.print(temperature);
    Serial.print(F("  Humidity: "));
    Serial.print(humidity);
}
