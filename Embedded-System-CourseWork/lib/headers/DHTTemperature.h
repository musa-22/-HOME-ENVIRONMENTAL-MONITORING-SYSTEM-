#pragma once
#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

class DHTTemperature
{
public:
    DHTTemperature();
    ~DHTTemperature();
    void dhtSetUP();
    void dhtPrinter();
    void state();
   

    double get_temperature(){return temperature;}
    double get_humidity(){return humidity;}

   

private:
    /* data */
    double temperature;
    double humidity;
    
   
   
};


