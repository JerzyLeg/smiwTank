# NanoTank Seeed Studio XIAO  ESP32S3

## Description

Still in progress... 
Software that enables to control two DC motors and capture live stream from attached camera.

The web server is hosted on the XIAO ESP32S3 and the website is uploaded to it's memory with the help of SPIFFS. With this setup, you can control two motors in both directions and watch live camera stream through a web app.

## Pinout Connections
- XIAO ESP32S3 Pins:
  - GPIO2, GPIO3, GPIO4, GPIO5 to DRV8833: IN4, IN3, IN2, IN1
- DRV8833 Pins:
  - OUT1, OUT2, OUT3, OUT4 to MOTOR1 (-, +) and MOTOR2 (+, -)
- Power Connections:
  - External 3.7V battery + and - connected to both:
    - ESP32S3: BAT+ and BAT-
    - DRV8833: VCC and GND
- Camera module OV2640 connector:
	 - B2B connector on the XIAO ESP32S3
- Antenna Wi-Fi:
	- WiFi/BT Antenna Connector on the XIAO ESP32S3  
## How to Use

1. Download all necessary libraries and tools:
	 - everything that is shown in WebSocket Server article and ESP32MotorControl library.
3. In Arduino IDE (only works on version 1.x.x), upload the code to XIAO ESP32S3.
4. By clicking ESP32 Sketch Data Upload, upload your data folder (index.html and style.css) (choose SPIFFS).
5. In serial monitor you should get IP address, to which you need to go.
6. Connect to the ESP32's Wi-Fi.
7. Open a browser and navigate to provided address to access the website.

## Inspiration
Idea, 3D printed parts and hardware based on this Instructables guide:<br> 
https://www.instructables.com/Camera-NanoTank/

## Motor Control
Controlled using the ESP32MotorControl library: <br>
https://github.com/JoaoLopesF/ESP32MotorControl
## WebSocket Server
Web socket server based on this article: <br>
https://shawnhymel.com/1882/how-to-create-a-web-server-with-websockets-using-an-esp32-in-arduino/ 

## Demonstration Video
Watch the demo on YouTube (tank was not streaming video yet): <br>
https://youtu.be/do-1lVbuCjg

