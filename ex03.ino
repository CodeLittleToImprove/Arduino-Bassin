#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    D0       
#define NUM_LEDS   64       
#define BRIGHTNESS 50      

Adafruit_NeoPixel matrix(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

const char* ssid     = "";
const char* password = "";
// set webserver port to 80
WiFiServer server(80);

const char* HTML_CONTENT = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>LED Matrix Control</title>
  <meta charset="UTF-8"> <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial, sans-serif; margin: 20px; }
    button { padding: 10px 15px; margin: 5px; font-size: 16px; cursor: pointer; }
    input[type="text"] { padding: 8px; font-size: 16px; width: 200px; }
  </style>
</head>
<body>
  <h1>LED Matrix Control</h1>
  <p> Here can you controll the LED Matrix.</p>
  <button onclick="sendAction('on')">LEDs on</button>
  <button onclick="sendAction('off')">LEDs off</button>

  <script>
    function sendAction(action) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/control?action=" + action, true);
      xhr.send();
    }
  </script>
</body>
</html>
)rawliteral";

void turnLedsOn() {
  for (int i = 0; i < NUM_LEDS; i++) {
    matrix.setPixelColor(i, matrix.Color(255, 0, 0)); 
  }
  matrix.show();
  Serial.println("LEDs turn red on");
}

void turnLedsOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    matrix.setPixelColor(i, 0);  
  }
  matrix.show();
  Serial.println("LEDs turn off");
}

void setup() {
  Serial.begin(9600);
  delay(1000);  

  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);
  matrix.show(); // turn off all LEd

  WiFi.mode(WIFI_STA);  // ensure in station mode
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}


void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client available");
    String currentLine = ""; 
    String request = "";     

    // small delay to make sure data was received
    unsigned long timeout = millis();
    while (!client.available() && millis() - timeout < 500) {
      delay(1);
    }

    if (!client.available()) { 
      Serial.println("No client data received.");
      return; 
    }

    // read HTTP-Request
    while (client.connected()) {
      if (client.available()) { //check if client has data to read 
        char c = client.read();
        request += c;
        if (c == '\n') { // 
          if (currentLine.length() == 0) { 
            break; // end of HTTP-Headers
          } else { // when not empty 
            currentLine = ""; // clear line
          }
        } else if (c != '\r') { // seems to be a standard in the http request, each line is divided by \r\n
          currentLine += c;
        }
      }
    }

    Serial.println("Request:");
    Serial.println(request);

    if (request.indexOf("GET /control?action=on") != -1) {
      Serial.println("Befehl: LEDs AN");
      turnLedsOn();
    } else if (request.indexOf("GET /control?action=off") != -1) {
      Serial.println("Befehl: LEDs AUS");
      turnLedsOff();
    } 
    // --- end of cmd execution ---

    // send HTTP-request
    client.println("HTTP/1.1 200 OK"); // 200 stands for http request was succesful
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println(F("")); // signal start of html content acts like a divider, f macro is used to save ram, strings gets saved on flash memory instead of ram
    client.println(HTML_CONTENT); // Send HTTP-Request to browser


    delay(1);
    client.stop();
    Serial.println("Client disconnected");
  }
}
