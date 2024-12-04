#include "thingProperties.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

// BME680 sensor object
Adafruit_BME680 bme;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500); 

  // Initialize the BME680 sensor
  if (!bme.begin()) {
    Serial.println("Could not find BME680 sensor!");
    while (1);
  }

  // Configure BME680
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X); 
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  
  // Read sensor data
  if (bme.performReading()) {
    // Update cloud variables
    temperature = (bme.temperature * 9 / 5) + 32;  // Convert to Fahrenheit
    humidity = bme.humidity;
    pressure = bme.pressure /1000;  //Convert to kPa

    // Print readings to Serial Monitor
    Serial.println("\n--- Readings ---");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °F");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" kPa");
  } else {
    Serial.println("Failed to read from BME680 sensor");
  }

  delay(5000);  // Wait 5 seconds between readings
}

void onTemperatureChange() {
  Serial.println("Temperature updated from cloud");
}

void onHumidityChange() {
  Serial.println("Humidity updated from cloud");
}

void onPressureChange() {
  Serial.println("Pressure updated from cloud");
}