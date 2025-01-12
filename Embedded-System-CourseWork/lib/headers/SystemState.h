#pragma once
#include <Arduino.h>
#include <RotaryEncoder.h>
#include <DHTTemperature.h>


class SystemState
{


public:
    SystemState(const int switch_button);
    ~SystemState();
    unsigned long lastOutputTime = 0;
    const int debuggerTime = 5000;
    bool debugerPrint();
    enum class SysteStateEnum{TEMPERATURE, HUMIDITY, SET_TEMPT, SET_HUM};
    enum class WholeSystemState
    {
    TEMP_OUTSIDE_RANGE,
    HUMIDITY_OUTSIDE_RANGE,
    BOTH_HUM_TEMP_OUTSIDE,
    WITHIN_HUM_TEMP_RANGE,
    TEMP_WITHIN,
    HUM_WITHIN,
    };
    void setSystemEnum(SysteStateEnum s){systemStateEnum = s;}
    SysteStateEnum getSystemEnum(){return systemStateEnum;}
    
    void set_whole_system_enum(WholeSystemState s){status_system = s;}
    WholeSystemState get_whole_system_enum(){return status_system;}
    //data for the swithcher state
    const int SWITCH_BUTTON;
    void setup();
    void changerStateSwitcher();
    void check_status(RotaryEncoder& rot);
    void check_temperature_rotary(RotaryEncoder& rot);
    void checkTemperatureState(DHTTemperature& dht_manager);
    void check_state_of_system();
     
    

private:
    SysteStateEnum systemStateEnum;
    WholeSystemState status_system;
    int buttonState = 0; // current state of the button
    // the last state
    int lastButtonState = 0;

    int count_button_press = 0;

    int max_temp_rotary = 0;
    int min_temp_rotary = 0;
    int max_hum_rotary = 0;
    int min_hum_rotary = 0;

 
    
};


