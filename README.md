📘 Overview
This project is an interactive RGB Mood Lamp built using an Arduino UNO, featuring manual and automatic color control. Users adjust Red, Green, and Blue levels using potentiometers, control brightness, and toggle between preset colors and fade mode via pushbuttons.

An OLED display provides real-time RGB and HEX values, along with brightness and mode info. The system also stores the last selected color in EEPROM, ensuring it persists across resets.

🎯 Key Features
✅ Manual RGB color control using potentiometers
✅ Brightness control via a fourth potentiometer
✅ Preset color buttons: Red, Green, White
✅ Auto-fade color cycling in HSV color space
✅ Real-time OLED display with HEX code output
✅ EEPROM memory for last used color
✅ Simulated color preview on OLED
✅ Fully simulated on Wokwi (Arduino UNO)

🔧 Components Used
Component	Function
Arduino UNO	Main microcontroller
RGB LED (Common Anode)	Visual color output
3x Potentiometers	Adjust Red, Green, Blue levels
1x Potentiometer	Controls brightness
4x Push Buttons	Red, Green, White, Fade toggle
SSD1306 OLED (I2C)	Displays color and system info
EEPROM (internal)	Stores RGB values across resets

🖥️ Controls
Control	Function
Pot A0	Red intensity (0–255)
Pot A1	Green intensity (0–255)
Pot A2	Blue intensity (0–255)
Pot A3	Brightness control (0–255)
Button D7	Set to Red
Button D8	Set to Green
Button D9	Set to White
Button D10	Toggle fade mode (auto color cycle)

📟 OLED Display Output
Shows the following in real-time:

✅ RGB values

🎨 HEX color code (e.g., #FF0088)

🌞 Brightness level

🔁 Current mode (Manual or Auto-Fade)

▓ Color preview bar (monochrome emulated)

💾 EEPROM Usage
Address	Purpose
0	Red value (0–255)
1	Green value (0–255)
2	Blue value (0–255)

Stored values load automatically on boot.

🔌 Circuit Connections (Arduino UNO)
Component	Arduino UNO Pin
Red LED (PWM)	D3
Green LED (PWM)	D5
Blue LED (PWM)	D6
Pot R	A0
Pot G	A1
Pot B	A2
Pot Brightness	A3
Button Red	D7
Button Green	D8
Button White	D9
Button Fade	D10
OLED SDA	A4
OLED SCL	A5

🧪 Simulation
🎮 Try it on Wokwi:
🔗 RGB Mood Lamp Simulation (UNO)

🚀 How to Run
Open project in Wokwi

Connect components as per table above

Upload sketch to Arduino UNO

Interact using potentiometers and buttons

View real-time color status on OLED

💡 Future Enhancements
Add IR Remote or Bluetooth control

Expand fade effect with user-tunable speed

Add sound reactivity (e.g., mic input)

