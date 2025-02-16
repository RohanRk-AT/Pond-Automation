#include <OneWire.h>
#include <DallasTemperature.h>

// pH Sensor Definitions
#define SensorPin A0      // pH sensor connected to analog pin A0
#define Offset -0.78      // Calibration offset for pH sensor
const float calibrationFactor = 1.0;  // Adjust based on your sensor calibration

// DS18B20 Temperature Sensor Definitions
#define ONE_WIRE_BUS 2     // DS18B20 data pin connected to digital pin 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Global variables
float voltage, pHValue;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(SensorPin, INPUT);
  
  // Start the DS18B20 sensor library
  sensors.begin();

 
}

void loop() {
  // Read pH value
  pHValue = readpHSensor();
  
  // Read temperature value
  float temperatureC = readTemperature();

  // Print sensor data to Serial Monitor
  Serial.print("pH Value: ");
  Serial.println(pHValue);
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  
  // Delay before the next reading (adjust as needed)
  delay(1000);
}

// Function to read pH sensor value
float readpHSensor() {
  int sensorValue = analogRead(SensorPin);  // Read analog value from pH sensor
  voltage = sensorValue * (5.0 / 1023.0);     // Convert the analog reading to voltage
  // Calculate pH value (modify equation if your sensor's behavior differs)
  float calculatedpH = 7.0 + ((2.5 - voltage) * calibrationFactor) + Offset;
  return calculatedpH;
}

// Function to read temperature from DS18B20 sensor
float readTemperature() {
  sensors.requestTemperatures();                     // Request temperature measurement
  float temp = sensors.getTempCByIndex(0);           // Get temperature in Celsius from sensor 0

  // Check if sensor reading is valid
 
  
  return temp;
}
