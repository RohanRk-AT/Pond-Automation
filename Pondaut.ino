#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi credentials
const char* ssid = "Realme";
const char* password = "87654321";

// Server details
const char* serverURL = "https://pond-managment-system.onrender.com/submit-data";

// HC-SR04 pins
#define TRIG_PIN 5  // GPIO pin connected to the TRIG pin of the HC-SR04
#define ECHO_PIN 18 // GPIO pin connected to the ECHO pin of the HC-SR04

void setup() {
  // Start Serial for debugging
  Serial.begin(115200);

  // Initialize the HC-SR04 pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Measure distance using HC-SR04
    long duration, distance;

    // Send a 10-microsecond pulse to the TRIG pin
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read the ECHO pin and calculate distance
    duration = pulseIn(ECHO_PIN, HIGH); // Duration of the echo signal in microseconds
    distance = duration * 0.034 / 2;   // Convert to distance in centimeters

    // Log the distance
    if (distance >= 2 && distance <= 400) {
      Serial.printf("Distance: %ld cm\n", distance);
    } else {
      Serial.println("Out of range");
      distance = -1; // Indicate an invalid reading
    }

    // Create the payload (JSON format)
    String payload = "{\"distance\": " + String(distance) + "}";

    // Send data to the server
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(payload);

    // Log the response
    if (httpResponseCode > 0) {
      Serial.printf("HTTP Response code: %d\n", httpResponseCode);
      String response = http.getString();
      Serial.printf("Server Response: %s\n", response.c_str());
    } else {
      Serial.printf("HTTP Request failed: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    // End the HTTP connection
    http.end();
  } else {
    Serial.println("WiFi not connected. Retrying...");
  }

  // Wait before sending the next request
  delay(5000); // Adjust as needed (e.g., 5 seconds)
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
