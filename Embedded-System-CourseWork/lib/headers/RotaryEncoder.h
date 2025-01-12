#pragma once
#include <Arduino.h>
#include <ESP32Encoder.h>

class RotaryEncoder
{
    public:
        RotaryEncoder(const int rotaryA, const int rotaryB, const int rotaryButton);
        ~RotaryEncoder();
        const int RotaryA;
        const int RotaryB;
        const int RotaryButton;
        ESP32Encoder encoder;

        void setup();
        int set_max_temperature();
        int set_mix_temperature();
        int set_max_humidity();
        int set_mix_humidity();
        void check_button_save();
        void check_button_save_humidity();
        void check_status();
        void check_status_for_hum();
        void set_temp_max(int t){max_temperature = t;}
        void set_temp_min(int t){min_temperature = t;}
        int get_max_temp(){return max_temperature;}
        int get_min_temp(){return min_temperature;}
        
        void set_hum_max(int h){max_humidity = h;}
        void set_hum_min(int h){min_humidity = h;}
        int get_max_hum(){return max_humidity;}
        int get_min_hum(){return min_humidity;}
            




    private:
        int count_button_press = 0;
        int buttonState = 0; // current state of the button
        // the last state
        int lastButtonState = 0;

        int encodercnt = 0;
        int max_temperature =25; 
        int min_temperature = 10;
        int max_humidity = 100;
        int min_humidity = 0;
        // temporary value of the temperature
        int temp_value = 0;

};