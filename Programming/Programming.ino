#include <ESP8266WiFi.h>

const char* ssid = "Mr.A's Lab";
const char* password = "lskdmin2938#$";

WiFiServer server(23); // TCP port 23

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("");

  WiFi.begin(ssid, password); // Connect to WiFi

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  server.begin(); // Start TCP server
  Serial.println("Server started");

  delay(4000);

}

void loop() {

  WiFiClient client = server.available(); // Check for incoming clients

  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      if (client.available()) {
        Serial.write(client.read()); // Send data from client to serial
      }

      if (Serial.available()) {
        client.write(Serial.read()); // Send data from serial to client
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}
