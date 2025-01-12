#include "SystemState.h"








SystemState::SystemState(const int switch_button):SWITCH_BUTTON(switch_button){}
SystemState::~SystemState(){}

bool SystemState::debugerPrint()
{
    if (millis() - lastOutputTime >= 5000)
    {
        lastOutputTime = millis();
        return true;
    }else{
        return false;
    }
}

void SystemState::setup()
{
    //set the enum class as Temperature, this is the default state
    systemStateEnum = SysteStateEnum::TEMPERATURE;
    //by defual set on within this is the same as the OK state
    status_system = WholeSystemState::WITHIN_HUM_TEMP_RANGE;
    pinMode(SWITCH_BUTTON, INPUT_PULLUP);
}

void SystemState::changerStateSwitcher()
{
 buttonState = digitalRead(SWITCH_BUTTON);

  if(buttonState != lastButtonState){
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
      // turn LED on:
    //Serial.println(F(" On "));
    
    
    count_button_press++;
    //Serial.println(count_button_press);
    
    if(count_button_press == 1){
      systemStateEnum = SysteStateEnum::HUMIDITY;
    }
    if(count_button_press==2){
      systemStateEnum = SysteStateEnum::TEMPERATURE;
    }
    if(count_button_press==3){
      systemStateEnum = SysteStateEnum::SET_TEMPT;
    }
    if(count_button_press==4){
      systemStateEnum = SysteStateEnum::SET_HUM;
      count_button_press = 0;
    }

    
        

    } else {
      // turn LED off:
    //  Serial.println(F(" Off "));
    }
     // Delay a little bit to avoid bouncing
    delay(50);

  }
  lastButtonState = buttonState;
}

void SystemState::check_status(RotaryEncoder& rot)
{

  switch (systemStateEnum)
  {
  case SysteStateEnum::TEMPERATURE:
    //Serial.println(F(" Temperature "));
    break;
  case SysteStateEnum::HUMIDITY:
    //Serial.println(F(" Humidity "));
    break;
  case SysteStateEnum::SET_TEMPT:
    rot.check_button_save();
    rot.check_status();
    break;
  case SysteStateEnum::SET_HUM:
    rot.check_button_save_humidity();
    rot.check_status_for_hum();
    break;
  }
}

void SystemState::check_temperature_rotary(RotaryEncoder &rot)
{
    Serial.println(F(" This is the maximun and minimun temperaure setted "));
    
    max_temp_rotary = rot.get_max_temp();
    min_temp_rotary = rot.get_min_temp();

    Serial.println(max_temp_rotary);
    Serial.println(min_temp_rotary);
    Serial.println(F(" This is the maximun and minum  humidity setted "));
    max_hum_rotary = rot.get_max_hum();
    min_hum_rotary = rot.get_min_hum();

    Serial.println(max_hum_rotary);
    Serial.println(min_hum_rotary);
  
}

void SystemState::checkTemperatureState(DHTTemperature &dht_manager)
{

  int current_temp = dht_manager.get_temperature();
  int current_hum = dht_manager.get_humidity();

  bool tempOk = true;
  bool humOk = true;

  bool tempWithin = true;
  bool humWithin = true;

  
  if(current_temp <= max_temp_rotary && current_temp >= min_temp_rotary){
      //within range
     
      status_system = WholeSystemState::TEMP_WITHIN;
      tempWithin = true;
  }else{
      
      status_system = WholeSystemState::TEMP_OUTSIDE_RANGE;
      tempOk = false;
      tempWithin = false;
  }
  if(current_hum <= max_hum_rotary && current_hum >= min_hum_rotary){
  
      status_system = WholeSystemState::HUM_WITHIN;
      humWithin = true;
  }else{
      status_system = WholeSystemState::HUMIDITY_OUTSIDE_RANGE;
      humOk = false;
      humWithin = false;
  }
  if(tempOk && humOk){
      status_system = WholeSystemState::WITHIN_HUM_TEMP_RANGE;
  }else {
      if (!tempOk && !humOk){
      status_system = WholeSystemState::BOTH_HUM_TEMP_OUTSIDE;
      }
  }
  

}

void SystemState::check_state_of_system()
{
  switch(status_system)
  {
    case WholeSystemState::TEMP_OUTSIDE_RANGE:
    Serial.println(F(" Temp Outside Range "));
    break;

    case WholeSystemState::HUMIDITY_OUTSIDE_RANGE:
    Serial.println(F(" HUM Outside Range "));
    break;

    case WholeSystemState::BOTH_HUM_TEMP_OUTSIDE:
    Serial.println(F(" Both OUTSIDE RANGE "));
    break;
    
    case WholeSystemState:: WITHIN_HUM_TEMP_RANGE:
    Serial.println(F(" WITHIN RANGE BOTH "));
    break;
    
    case WholeSystemState::TEMP_WITHIN:
    Serial.println(F(" TEMP WITHIN "));
    break;
    
    case WholeSystemState::HUM_WITHIN:
    Serial.println(F(" HUMIDITY WITHIN "));
    break;

  }

}
