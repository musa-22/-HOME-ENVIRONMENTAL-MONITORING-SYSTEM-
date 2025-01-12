// #include <main.cpp>
#include <unity.h>
#include "unity.h"
#include <stddef.h>

#include <Arduino.h>
#include <ledsRGB.cpp> // ledsRGB class called
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

enum State
{
    LED_BLUE,
    LED_RED
};

enum class SystemStates
{
    OK,
    TEMP_OUT,
    HUM_OUT,
    BOTH_OUT
};

enum class ConditionStates
{
    TEMP_BELOW,
    HUM_BELOW,
    TEMP_WITHIN,
    HUM_WITHIN,
    TEMP_AND_HUM_WITHIN,
    TEMP_ABOVE,
    HUM_ABOVE,
    BOTH_TEMP_AND_HUM_OUT
};

State current;
const int LED_PIN = LED_BUILTIN;
const int LED_DELAY = 250;
unsigned long lastChangeTime;
unsigned long lastOutputTime = 0;

#define DHTPIN 14
// Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);
// calling ledsRBG class and pass pin number of each color.
// ledsRGB rgb(37, 36, 33);
ledsRGB rgb(4, 16, 17);

uint32_t delayMS = 5000;
double temperature = 0; // Current temperature
double humidity = 0;    // Current humidity
SystemStates state = SystemStates::OK;
ConditionStates condition = ConditionStates::TEMP_AND_HUM_WITHIN;

boolean timeDiff(unsigned long start, int specifiedDelay)
{
    return (millis() - start >= specifiedDelay);
}
void ledBlue()
{
    digitalWrite(rgb.PIN_BLUE_LED_RGB, HIGH);
    digitalWrite(rgb.PIN_RED_LED_RGB, LOW);
    digitalWrite(rgb.PIN_GREEN_LED_RGB, LOW);
    if (timeDiff(lastChangeTime, LED_DELAY))
        current = LED_RED;
}

void ledRed()
{
    digitalWrite(rgb.PIN_RED_LED_RGB, HIGH);
    digitalWrite(rgb.PIN_BLUE_LED_RGB, LOW);
    digitalWrite(rgb.PIN_GREEN_LED_RGB, LOW);

    if (timeDiff(lastChangeTime, LED_DELAY))
        current = LED_BLUE;
}

void setup()
{
    Serial.begin(115200);
    pinMode(rgb.PIN_BLUE_LED_RGB, OUTPUT);
    pinMode(rgb.PIN_RED_LED_RGB, OUTPUT);
    pinMode(rgb.PIN_GREEN_LED_RGB, OUTPUT);
    // Initialize device.
    dht.begin();
    Serial.println(F("DHTxx Unified Sensor Example"));
    // Print temperature sensor details.
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print(F("Sensor Type: "));
    Serial.println(sensor.name);
    Serial.print(F("Driver Ver:  "));
    Serial.println(sensor.version);
    Serial.print(F("Unique ID:   "));
    Serial.println(sensor.sensor_id);
    Serial.print(F("Max Value:   "));
    Serial.print(sensor.max_value);
    Serial.println(F("°C"));
    Serial.print(F("Min Value:   "));
    Serial.print(sensor.min_value);
    Serial.println(F("°C"));
    Serial.print(F("Resolution:  "));
    Serial.print(sensor.resolution);
    Serial.println(F("°C"));
    Serial.println(F("------------------------------------"));
    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print(F("Sensor Type: "));
    Serial.println(sensor.name);
    Serial.print(F("Driver Ver:  "));
    Serial.println(sensor.version);
    Serial.print(F("Unique ID:   "));
    Serial.println(sensor.sensor_id);
    Serial.print(F("Max Value:   "));
    Serial.print(sensor.max_value);
    Serial.println(F("%"));
    Serial.print(F("Min Value:   "));
    Serial.print(sensor.min_value);
    Serial.println(F("%"));
    Serial.print(F("Resolution:  "));
    Serial.print(sensor.resolution);
    Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
    // Set delay between sensor readings based on sensor details.
    delayMS = sensor.min_delay / 1000;
}

int maxTemp = 35;
int minTemp = 10;
int minHumidity = 15;
int maxHumidity = 80;
// int maxmax = 30; //temp
// int maxmax_h = 100; // humidity

void set_led()
{
    switch (state)
    {
    case SystemStates::OK:
        digitalWrite(rgb.PIN_GREEN_LED_RGB, HIGH);
        digitalWrite(rgb.PIN_RED_LED_RGB, LOW);
        digitalWrite(rgb.PIN_BLUE_LED_RGB, LOW);
        if (timeDiff(lastChangeTime, LED_DELAY))
            break;
    case SystemStates::TEMP_OUT:
        digitalWrite(rgb.PIN_RED_LED_RGB, HIGH);
        digitalWrite(rgb.PIN_GREEN_LED_RGB, LOW);
        digitalWrite(rgb.PIN_BLUE_LED_RGB, LOW);
        break;
    case SystemStates::HUM_OUT:
        digitalWrite(rgb.PIN_RED_LED_RGB, LOW);
        digitalWrite(rgb.PIN_GREEN_LED_RGB, LOW);
        digitalWrite(rgb.PIN_BLUE_LED_RGB, HIGH);
        break;
    case SystemStates::BOTH_OUT:
        State old = current;
        switch (current)
        {
        case LED_RED:
            ledRed();
            break;

        case LED_BLUE:
            ledBlue();
            break;
        }

        if (old != current)
            lastChangeTime = millis();

        break;
    }
}

void output_states()
{
    Serial.println("OUTPUT");
    switch (condition)
    {
    case ConditionStates::TEMP_AND_HUM_WITHIN:
        Serial.println("Temperature and humidity are within range");
        break;
    case ConditionStates::TEMP_WITHIN:
        Serial.println("Temperature is within range");
        break;
    case ConditionStates::HUM_WITHIN:
        Serial.println("Humidity is within range");
        break;
    case ConditionStates::TEMP_BELOW:
        Serial.println("Temperature is below range");
        break;
    case ConditionStates::HUM_BELOW:
        Serial.println("Humidity is below range");
        break;
    case ConditionStates::TEMP_ABOVE:
        Serial.println("Temperature is above range");
        break;
    case ConditionStates::HUM_ABOVE:
        Serial.println("Humidity is above range");
        break;
    case ConditionStates::BOTH_TEMP_AND_HUM_OUT:
        Serial.println("Both humidity and temperature are out of range");
        break;
    }
}

// void transition_states() {
//   switch(condition) {
//   case
//   }
// }

void check_conditions()
{
    bool tempOk = true;
    bool humOk = true;

    bool tempWithin = true;
    bool humWithin = true;

    if (temperature <= maxTemp && temperature >= minTemp)
    {
        // condition state here
        condition = ConditionStates::TEMP_WITHIN;
        state = SystemStates::OK;
        //Serial.println("Temperature is within range");
        tempWithin = true;
    }
    else
    {
        tempOk = false;
        tempWithin = false;
        //Serial.println("Changed range from green to");
        if (temperature > maxTemp)
        {
            condition = ConditionStates::TEMP_ABOVE;
            // Serial.println("Temperature is above range");
            tempWithin = false;
        }
        else
        {
            condition = ConditionStates::TEMP_BELOW;
            //Serial.println("Temperature is below range");
            tempWithin = false;
        }
    }

    if (humidity <= maxHumidity && humidity >= minHumidity)
    {
        // condition = ConditionStates::HUM_WITHIN;
        //Serial.println("Humidity is within range");
        humWithin = true;
    }
    else
    {
        humOk = false;
        humWithin = false;
        if (humidity > maxHumidity)
        {
            condition = ConditionStates::HUM_ABOVE;
            //Serial.println("Humidity is above range");
            humWithin = false;
        }
        else
        {
            condition = ConditionStates::HUM_BELOW;
            //Serial.println("Humidity is below range");
            humWithin = false;
        }
        if (temperature >= minTemp && humidity >= minHumidity)
            //condition = ConditionStates::BOTH_TEMP_AND_HUM_OUT;
            humWithin = false;
        tempWithin = false;

        state = SystemStates::BOTH_OUT;
        //condition = ConditionStates::BOTH_TEMP_AND_HUM_OUT;

        {
        }
    }

    if (tempOk && humOk)
    {
        state = SystemStates::OK;
        condition = ConditionStates::TEMP_AND_HUM_WITHIN;
    }
    else
    {
        if (!tempOk && !humOk)
            state = SystemStates::BOTH_OUT;
        //condition = ConditionStates::BOTH_TEMP_AND_HUM_OUT;

        else if (!tempOk)

            state = SystemStates::TEMP_OUT;
        //Serial.println("Temp is not ok");
        else
            state = SystemStates::HUM_OUT;
    }
}

void loop()
{
    check_conditions();
    set_led();

    // Delay between measurements.
    //delay(delayMS);
    //lastChangeTime = millis();

    if (millis() - lastOutputTime >= 5000)
    {

        lastOutputTime = millis();
        output_states();
        // only checking DHT every 5s make it check more frequently

        // temperature = event.temperature >>>>>> move it after dht.temperature().getEvent(&event);
        //otherwise it will skip the first loop of if statement

        // Get temperature event and print its value.
        sensors_event_t event;
        dht.temperature().getEvent(&event); ///>>>
        temperature = event.temperature;

        // State old = current;
        if (isnan(event.temperature))
        {

            Serial.println(F("Error reading temperature!"));
        }
        else
        {

            Serial.print(F("Temperature: "));
            Serial.print(event.temperature);

            Serial.println(F("°C"));
        }

        // Get humidity event and print its value.
        dht.humidity().getEvent(&event);
        humidity = event.relative_humidity;
        if (isnan(event.relative_humidity))

        {

            Serial.println(F("Error reading humidity!"));
        }
        else
        {
            Serial.print(F("Humidity: "));
            Serial.print(event.relative_humidity);
            Serial.println(F("%"));
        }
        // if (old != current)
        //   lastChangeTime = millis();
    }
}

void test()
{
}

int main()
{
}
