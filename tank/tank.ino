#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ESP32MotorControl.h> // https://github.com/JoaoLopesF/ESP32MotorControl

const int dns_port = 53;
const int http_port = 80;
const int ws_port = 1337;

const int motor0GPIO2 = 2;
const int motor0GPIO3 = 3;
const int motor1GPIO4 = 4;
const int motor1GPIO5 = 5;

const int speed = 50;
const int RSpeed = 75;
const int LSpeed = 100;

int motor0Backward = 0;
int motor0Forward = 0;
int motor1Backward = 0;
int motor1Forward = 0;

// MotorControl instance
ESP32MotorControl MotorControl = ESP32MotorControl();


// Globals
AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(1337);
char msg_buf[20];

/***********************************************************
   Functions
*/

// Callback: receiving any WebSocket message
void onWebSocketEvent(uint8_t client_num,
                      WStype_t type,
                      uint8_t *payload,
                      size_t length) {

  // Figure out the type of WebSocket event
  switch (type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", client_num);
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_num);
        Serial.printf("[%u] Connection from ", client_num);
        Serial.println(ip.toString());
      }
      break;

    // Handle text messages from client
    case WStype_TEXT:

      // Print out raw message
      Serial.printf("[%u] Received text: %s\n", client_num, payload);


      //Motor_0 FORWARD
      // Toggle forward
      if (strcmp((char *)payload, "moveForwardMotor0") == 0) {
        motor0Forward = motor0Forward ? 0 : 1;
        Serial.printf("Motor_0: Forward %u\n", motor0Forward);
        if(motor0Forward == 1)
        {
          motor0Backward = 0;
          MotorControl.motorForward(0, LSpeed);
        }
        else
        {
          MotorControl.motorStop(0);
        }

        
        // Report the state of the Motor_0 FORWARD
      } else if (strcmp((char *)payload, "stateForwardMotor0") == 0) {
        sprintf(msg_buf, "%s:%d", "motor0forward",motor0Forward);
        Serial.printf("Sending to [%u]: %s\n", client_num, msg_buf);
        webSocket.sendTXT(client_num, msg_buf);

      //Motor_0 BACKWARD
      // Toggle backward
      } else if (strcmp((char *)payload, "moveBackwardMotor0") == 0) {
        motor0Backward = motor0Backward ? 0 : 1;
        Serial.printf("Motor_0: Backward %u\n", motor0Backward);
        if(motor0Backward == 1)
        {
          motor0Forward = 0;
          MotorControl.motorReverse(0, LSpeed);
        }
        else
        {
          MotorControl.motorStop(0);
        }

        // Report the state of the LED2
      } else if (strcmp((char *)payload, "stateBackwardMotor0") == 0) {
        sprintf(msg_buf, "%s:%d","motor0backward",motor0Backward);
        Serial.printf("Sending to [%u]: %s\n", client_num, msg_buf);
        webSocket.sendTXT(client_num, msg_buf);

      //Motor_1 FORWARD
      // Toggle forward
      } else if (strcmp((char *)payload, "moveForwardMotor1") == 0) {
        motor1Forward = motor1Forward ? 0 : 1;
        Serial.printf("Motor_1: Forward %u\n", motor1Forward);
        if(motor1Forward == 1)
        {
          motor1Backward = 0;
          MotorControl.motorForward(1, RSpeed);
        }
        else
        {
          MotorControl.motorStop(1);
        }

        // Report the state of the LED3
      } else if (strcmp((char *)payload, "stateForwardMotor1") == 0) {
        sprintf(msg_buf, "%s:%d","motor1forward",motor1Forward);
        Serial.printf("Sending to [%u]: %s\n", client_num, msg_buf);
        webSocket.sendTXT(client_num, msg_buf);

      //Motor_1 BACKWARD
      // Toggle backward
      } else if (strcmp((char *)payload, "moveBackwardMotor1") == 0) {
        motor1Backward = motor1Backward ? 0 : 1;
        Serial.printf("Motor_1: Backward %u\n", motor1Backward);
        if(motor1Backward == 1)
        {
          motor1Forward = 0;
          MotorControl.motorReverse(1, RSpeed);
        }
        else
        {
          MotorControl.motorStop(1);
        }

        // Report the state of the LED4
      } else if (strcmp((char *)payload, "stateBackwardMotor1") == 0) {
        sprintf(msg_buf, "%s:%d","motor1backward",motor1Backward);
        Serial.printf("Sending to [%u]: %s\n", client_num, msg_buf);
        webSocket.sendTXT(client_num, msg_buf);

        // Message not recognized
      } else {
        Serial.println("[%u] Message not recognized");
      }
      
      break;

    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}

// Callback: send homepage
void onIndexRequest(AsyncWebServerRequest *request) {
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("[" + remote_ip.toString() + "] HTTP GET request of " + request->url());
  request->send(SPIFFS, "/index.html", "text/html");
}

// Callback: send style sheet
void onCSSRequest(AsyncWebServerRequest *request) {
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("[" + remote_ip.toString() + "] HTTP GET request of " + request->url());
  request->send(SPIFFS, "/style.css", "text/css");
}

// Callback: send 404 if requested file does not exist
void onPageNotFound(AsyncWebServerRequest *request) {
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("[" + remote_ip.toString() + "] HTTP GET request of " + request->url());
  request->send(404, "text/plain", "Not found");
}

/***********************************************************
   Main
*/

void setup() {
  
  //Setup pins as an output
  pinMode(motor0GPIO2, OUTPUT);
  pinMode(motor0GPIO3, OUTPUT);
  pinMode(motor1GPIO4, OUTPUT);
  pinMode(motor1GPIO5, OUTPUT);
  
  //Attach 2 motors
  MotorControl.attachMotors(motor0GPIO2, motor0GPIO3, motor1GPIO4, motor1GPIO5);

  // Start Serial port
  Serial.begin(115200);

  // Make sure we can read the file system
  if (!SPIFFS.begin(true)) {
    Serial.println("Error mounting SPIFFS");
    while (1)
      ;
  }

  // Start access point
  WiFi.mode(WIFI_AP);

  // Print our IP address
  Serial.println();
  Serial.println("AP running");
  Serial.print("My IP address: ");
  Serial.println(WiFi.softAPIP());

  // On HTTP request for root, provide index.html file
  server.on("/", HTTP_GET, onIndexRequest);

  // On HTTP request for style sheet, provide style.css
  server.on("/style.css", HTTP_GET, onCSSRequest);

  // Handle requests for pages that do not exist
  server.onNotFound(onPageNotFound);

  // Start web server
  server.begin();

  // Start WebSocket server and assign callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop() {

  // Look for and handle WebSocket data
  webSocket.loop();
}
