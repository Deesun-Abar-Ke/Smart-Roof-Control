#include <Servo.h>

// Initialize the Servo object
Servo myservo;

// Define pin connections
const int rainSensorPin = A0;      // Analog pin for raindrop sensor
const int soilMoisturePin = A1;    // Analog pin for soil moisture sensor
const int servoPin = 9;            // Digital pin for servo
const int relayPin = 7;            // Digital pin for relay

// Define thresholds
const int rainThreshold = 500;     // Threshold for rain detection
const int moistureThreshold = 300; // Threshold for soil moisture

void setup() {
  // Attach the servo on pin 9 to the servo object
  myservo.attach(servoPin);
  
  // Initialize the relay pin as OUTPUT
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Initialize relay as off
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the servo to the initial position (0 degrees)
  myservo.write(0);
}

void loop() {
  // Read the value from the raindrop sensor
  int rainSensorValue = analogRead(rainSensorPin);
  
  // Read the value from the soil moisture sensor
  int soilMoistureValue = analogRead(soilMoisturePin);
  
  // Print the sensor values to the Serial Monitor
  Serial.print("Rain Sensor: ");
  Serial.println(rainSensorValue);
  Serial.print("Soil Moisture Sensor: ");
  Serial.println(soilMoistureValue);
  
  // Rain detection logic
  if (rainSensorValue < rainThreshold) {  // Rain detected
    // Rotate the servo to 180 degrees to close the roof
    myservo.write(90);
  } else {  // No rain detected
    // Rotate the servo back to 0 degrees to open the roof
    myservo.write(0);
  }

  // Soil moisture detection logic
  if (soilMoistureValue < moistureThreshold) {  // Dry soil detected
    // Turn on the relay to activate the pump for irrigation
    digitalWrite(relayPin, HIGH);
  } else {  // Soil is sufficiently moist
    // Turn off the relay to stop irrigation
    digitalWrite(relayPin, LOW);
  }
  
  // Small delay to avoid flooding the serial monitor
  delay(1000);
}