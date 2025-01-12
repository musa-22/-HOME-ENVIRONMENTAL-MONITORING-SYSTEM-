This was one of the university projects I worked on during my bachelor's degree, where I also served as the team leader.

The project involved implementing complex requirements, and my team and I successfully achieved them. The result was an embedded system capable of detecting temperature and humidity. The system provides visual alerts based on the readings:

Red LED blinks if the temperature is outside the specified range.
Blue LED blinks if the humidity is outside the specified range.
Red and Blue LEDs flash alternately if both temperature and humidity are outside their respective ranges.
Green LED blinks when both parameters are within range.
The system allows the temperature range to be adjusted using a rotary encoder. Pressing the rotary encoder's switch changes the state, and using its button, you can set the temperature and humidity thresholds.

Make sure to install the necessary libraries listed in the platformio.ini file and verify that your hardware setup uses the same pin configurations specified in the code.


![Screenshot 2025-01-12 142718](https://github.com/user-attachments/assets/e47c2c2f-4879-4685-91e3-abbf290a083e)
