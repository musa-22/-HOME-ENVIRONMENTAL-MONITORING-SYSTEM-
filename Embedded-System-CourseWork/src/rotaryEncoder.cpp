#include "RotaryEncoder.h"




enum class Rotary_State
{
    MAX_TEMP,
    MIN_TEMP,
  
    
};

enum class Rotary_State_HUM
{
    MAX_HUM,
    MIN_HUM,
    
};


Rotary_State status = Rotary_State::MAX_TEMP;
Rotary_State_HUM statusHUM = Rotary_State_HUM::MAX_HUM;


RotaryEncoder::RotaryEncoder(const int rotaryA, const int rotaryB, const int rotaryButton)
:RotaryA(rotaryA), RotaryB(rotaryB), RotaryButton(rotaryButton)
{
}

RotaryEncoder::~RotaryEncoder()
{
}

void RotaryEncoder::setup()
{
     // we set up the encoder
        ESP32Encoder::useInternalWeakPullResistors = UP;
        pinMode(RotaryButton, INPUT_PULLUP);
        encoder.attachHalfQuad(RotaryA, RotaryB);
        // set the counter to start from 15
        encoder.setCount(15);

}

int RotaryEncoder::set_max_temperature()
{
        if (temp_value != encoder.getCount())
        {
            temp_value = encoder.getCount();

            if (temp_value >= 30)
            {
                temp_value = 30;
                encoder.setCount(temp_value);
            }
            else if (temp_value <= 6)
            {
                temp_value = 6;
                encoder.setCount(temp_value);
            }
        }
        Serial.println(temp_value);
        return temp_value;


}

int RotaryEncoder::set_mix_temperature()
{
   if (temp_value != encoder.getCount())
    {
            temp_value = encoder.getCount();

            if (temp_value >= max_temperature -1)
            {
                temp_value = max_temperature -1;
                encoder.setCount(temp_value);
            }
            else if (temp_value <= 5)
            {
                temp_value = 5;
                encoder.setCount(temp_value);
            }
    }
    Serial.println(temp_value);
    return temp_value;

}

int RotaryEncoder::set_max_humidity()
{
      if (temp_value != encoder.getCount())
        {
            temp_value = encoder.getCount();

            if (temp_value >= 100)
            {
                temp_value = 100;
                encoder.setCount(temp_value);
            }
            else if (temp_value <= 1)
            {
                temp_value = 1;
                encoder.setCount(temp_value);
            }
        }
        Serial.println(temp_value);
        return temp_value;
}

int RotaryEncoder::set_mix_humidity()
{
    if (temp_value != encoder.getCount())
    {
            temp_value = encoder.getCount();

            if (temp_value >= max_humidity -1)
            {
                temp_value = max_humidity -1;
                encoder.setCount(temp_value);
            }
            else if (temp_value <= 0)
            {
                temp_value = 0;
                encoder.setCount(temp_value);
            }
    }
    Serial.println(temp_value);
    return temp_value;
}

void RotaryEncoder::check_button_save()
{
     buttonState = digitalRead(RotaryButton);
       if(buttonState != lastButtonState){
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
        if (buttonState == HIGH) {
        // turn LED on:
        //Serial.println(F(" On "));
        
        
        count_button_press++;
        //Serial.println(count_button_press);
        
        if(count_button_press == 1){
            //this saves 
            status= Rotary_State::MAX_TEMP;
            encoder.setCount(max_temperature);
        }
        if(count_button_press==2){
      
            status= Rotary_State::MIN_TEMP;
            encoder.setCount(min_temperature);
            count_button_press = 0;
        }
              
        } else {
        // turn LED off:
        //Serial.println(F(" Off "));
        }
        // Delay a little bit to avoid bouncing
        delay(50);

    }
    lastButtonState = buttonState;
}

void RotaryEncoder::check_button_save_humidity()
{
    buttonState = digitalRead(RotaryButton);
       if(buttonState != lastButtonState){
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
        if (buttonState == HIGH) {
        // turn LED on:
        //Serial.println(F(" On "));
        count_button_press++;
        //Serial.println(count_button_press);
        
        if(count_button_press == 1){
            //this saves 
            statusHUM= Rotary_State_HUM::MAX_HUM;
            encoder.setCount(max_humidity);
        }
        if(count_button_press==2){
      
            statusHUM= Rotary_State_HUM::MIN_HUM;
            encoder.setCount(min_humidity);
            count_button_press = 0;
        }
              
        } else {
        // turn LED off:
        //Serial.println(F(" Off "));
        }
        // Delay a little bit to avoid bouncing
        delay(50);

    }
    lastButtonState = buttonState;
    //Serial.println(count_button_press);
}

void RotaryEncoder::check_status()
{
   switch (status)
  {
    case Rotary_State::MAX_TEMP:
    max_temperature = set_max_temperature();
    break;
  
    case Rotary_State::MIN_TEMP:
    min_temperature = set_mix_temperature();
    break;
    
   
  
  
  }


}

void RotaryEncoder::check_status_for_hum()
{
    switch (statusHUM)
    {
    case Rotary_State_HUM::MAX_HUM:
    max_humidity = set_max_humidity();
    //Serial.println("MAX HUM");
    break;
    
    case Rotary_State_HUM::MIN_HUM:
    min_humidity = set_mix_humidity();
     //Serial.println("MIN HUM");
    break;

  }
}
