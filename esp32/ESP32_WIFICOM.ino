#include <WiFi.h>

#define RXD2 16 // Using pin 16 for RX2
#define TXD2 17 // Using pin 17 for TXD2

const char* ssid = "Malik iPhone";       // Mobile Hotspot used for project demo name
const char* password = "Thisdoesntwork";  //Mobile Hotspot used for project demo password

WiFiServer server(80);

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
  WiFi.mode(WIFI_STA);  // Set the ESP32 to station mode
  WiFi.begin(ssid, password); // Connect to wifi using credentials

  while (WiFi.status() != WL_CONNECTED) { // Waits for connection to occur
    delay(500);
    Serial.print(".");
  }   
  Serial.println("WiFi connected"); // Prints when wifi is connected
  Serial.println(WiFi.localIP()); //Prints IP address
  server.begin();  // Start WiFi server

  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2); // Start UART communication
}

void loop() {
  WiFiClient client = server.available(); //Checks if client has been connected
  if (client) { //Checks for request
    String request = client.readStringUntil('\r');  // Read the client's request
    client.flush(); //Clear request buffer

    if (request.indexOf("/speed/") != -1) { //Checks for input to have "speed"
      int speed = request.substring(request.indexOf("/speed/") + 7).toInt(); //Extracts speed value from request
      Serial.print("Received speed: ");
      Serial.println(speed);  // Print speed value received from client

      Serial2.write(speed); // Send speed value to MSP430 via UART
    }

    client.println("HTTP/1.1 200 OK"); // Send HTTP response back to the client
  }
}
