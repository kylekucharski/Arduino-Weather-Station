#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

// Create a BME680 object
Adafruit_BME680 bme;

void setup() {
  // Start Serial Communication
  Serial.begin(115200);
  while (!Serial);

  // Initialize the BME680 sensor
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Configure BME680 settings
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
}

void loop() {
  // Ensure the sensor has data to provide
  if (!bme.performReading()) {
    // In case of failing to connect to sensor
    Serial.println("Failed to perform reading from BME680 sensor!");
    return;
  }

  // Print sensor readings to Serial Monitor
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");


  Serial.println();
  
  delay(3600000); // Delay for 1 hour
}
