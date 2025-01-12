#pragma once
#include <Arduino.h>
#include <SystemState.h>



class LedChanger
{

public:
  
    LedChanger(int redpin, int greenpin, int bluepin);
    ~LedChanger();
    const int Led_Delay = 1000;
    unsigned long lastChangeTime;
    // const int redPin=17;
    // const int greenPin =16;
    // const int bluePin =4;
    const int redPin;
    const int greenPin;
    const int bluePin;
    
    //time difference for the lad
    boolean timeDiff(unsigned long start, int specifiedDelay);
    //led blue and green
    void ledBlue();
    void ledGreen();
    void ledRed();
    //setup loop led
    void ledSetUp();
    //switch loop
    void setLed(SystemState& sys_state);

private:
    

};


