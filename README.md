This is software which enables steering the tank by controlling tow DC-motors using XIAO ESP32S3 with small battery and driver drv8833.
The web server is hosted on XIAO ESP32S3, the website with control panel is uploaded to memory of ESP32. With this, I am able to control two motors in two directions by web app.
To use it, device must be powered up by battery or usb-c, you have to connect to Wi-Fi of esp32 and go to 192.168.4.1. There is control panel for motors.

XIAO ESP32S3 pinouts: GPIO2, GPIO3, GPIO4, GPIO5 to DRV8833: IN4, IN3, IN2, IN1. 
DRV8833: OUT1, OUT2, Out3, OUT4 to MOTOR1: -, + MOTOR2: +, -. 
External 3,7V battery +, - to both ESP32S3: BAT+, BAT- and DRV8833: VCC, GND.

Idea: https://www.instructables.com/Camera-NanoTank/
Web Server Connection based on: https://shawnhymel.com/1882/how-to-create-a-web-server-with-websockets-using-an-esp32-in-arduino/
Controlling motors with DRV8833 using library: https://github.com/JoaoLopesF/ESP32MotorControl 

Demonstration:
https://youtu.be/do-1lVbuCjg
