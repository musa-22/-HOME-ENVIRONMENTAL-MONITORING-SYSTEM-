#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP32Encoder.h>
#include <TFT_eSPI.h>
#include "AnalogueMeter.h"

#include "LedChanger.h"
#include "SystemState.h"
#include "DHTTemperature.h"
#include "RotaryEncoder.h"




//SystemState *systemStates = nullptr;
//32 pin for button
LedChanger leds(16,17,5);
SystemState sysManger(32); 
DHTTemperature dhtManager;
RotaryEncoder rotary(4,0,15);



//Rotary Button MS 15
//Rotary DT b 0
//Rotary CLK A 4
// const int RotaryA =4;
// const int RotaryB =0;
// int counter =0;
// int aState;
// int aLastState;
//const int DHT_PIN = 14;
//DHT dht(DHT_PIN, DHT11);
// double temperature;
// double humidity;



void setup(){
  
  Serial.begin(115200);

  Serial.println("ESP32 is ready to work" );
  
  sysManger.setup();
  leds.ledSetUp();
  rotary.setup();

 
  dhtManager.dhtSetUP();
  

}






void loop(){

 sysManger.changerStateSwitcher();
 sysManger.check_status(rotary);
 sysManger.checkTemperatureState(dhtManager);
 leds.setLed(sysManger);
  

  
  
  if(sysManger.debugerPrint()){
    Serial.println(F(" Every 5 seconds Debugger  "));
    dhtManager.dhtPrinter();
    sysManger.check_temperature_rotary(rotary);
    sysManger.check_state_of_system();
  }

   
  

}