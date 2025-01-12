#include <Arduino.h>
#include "LedChanger.h"



enum State{
    LED_BLUE, LED_RED, LED_GREEN
};

State current;



LedChanger::LedChanger(int redpin, int greenpin, int bluepin)
    : redPin(redpin), greenPin(greenpin), bluePin(bluepin)
{
}

LedChanger::~LedChanger()
{
}

boolean LedChanger::timeDiff(unsigned long start, int specifiedDelay)
{
    return (millis() - start >= specifiedDelay);
}

void LedChanger::ledBlue()
{
    digitalWrite(bluePin, HIGH);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    if (timeDiff(lastChangeTime, Led_Delay))
        current = LED_RED;
       
}

void LedChanger::ledGreen()
{
  
}

void LedChanger::ledRed()
{
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
    if (timeDiff(lastChangeTime, Led_Delay))
        current = LED_BLUE;
}

void LedChanger::ledSetUp()
{
    
    pinMode(redPin,OUTPUT);
    pinMode(greenPin,OUTPUT);
    pinMode(bluePin,OUTPUT);
   
}

void LedChanger::setLed(SystemState& sys_manager)
{

    
    switch (sys_manager.get_whole_system_enum())
    {
        // state OK
        case SystemState::WholeSystemState:: WITHIN_HUM_TEMP_RANGE:
            digitalWrite(greenPin, HIGH);
            digitalWrite(redPin, LOW);
            digitalWrite(bluePin, LOW);
        //if (timeDiff(lastChangeTime, Led_Delay))
        break;

        case SystemState::WholeSystemState::TEMP_OUTSIDE_RANGE:
            digitalWrite(redPin, HIGH);
            digitalWrite(bluePin, LOW);
            digitalWrite(greenPin, LOW);
        break;

        case SystemState::WholeSystemState::HUMIDITY_OUTSIDE_RANGE:
            digitalWrite(bluePin, HIGH);
            digitalWrite(redPin, LOW);
            digitalWrite(greenPin, LOW);
        break;

        case SystemState::WholeSystemState::TEMP_WITHIN:
            digitalWrite(bluePin, HIGH);
            digitalWrite(redPin, LOW);
            digitalWrite(greenPin, LOW);
        break;
        
        case SystemState::WholeSystemState::HUM_WITHIN:
            digitalWrite(redPin, HIGH);
            digitalWrite(bluePin, LOW);
            digitalWrite(greenPin, LOW);
        break;
        case SystemState::WholeSystemState::BOTH_HUM_TEMP_OUTSIDE:
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



    // State old = current;
    // switch (current)
    // {
    // case LED_RED:
    //   ledRed();
    //   break;

    // case LED_BLUE:
    //   ledBlue();
    //   break;
    // }

    // if (old != current)
    //   lastChangeTime = millis();  
