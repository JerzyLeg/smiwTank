This is software which is used to control XIAO ESP32S3 with small battery, driver drv8833, and two DC-motors.
The web server is hosted on ESP32, the wbesite with control panel is uploaded to memory of ESP32. With this, I am able to control two motors in two directions by web app.
To use it, device must be powered up by battery or usb-c, you have to connect to Wi-Fi of esp32 and go to 192.168.4.1. There is control panel for motors.

#HARDWARE CONNECTION:
XIAO ESP32S3 pinouts: GPIO2, GPIO3, GPIO4, GPIO5 to DRV8833: IN4, IN3, IN2, IN1. 
DRV8833: OUT1, OUT2, Out3, OUT4 to MOTOR1: -, + MOTOR2: +, -. 
External 3,7V battery +, - to both ESP32S3: BAT+, BAT- and DRV8833: VCC, GND.
