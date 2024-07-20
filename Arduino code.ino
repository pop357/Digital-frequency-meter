#include <Wire.h>
#include <MCP23017.h>
#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "**";            // Wifi SSID
char pass[] = "**";  // Wifi password
int keyIndex = 0;                   // Network key Index number (needed only for WEP)

void connectToWiFi() {
  // Check if the WiFi module works
  if (WiFi.status() == WL_NO_SHIELD) {
    // Wait until WiFi ready
    Serial.println("WiFi adapter not ready");
    while (true);
  }

  // Check Firmware
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
    
  // Establish a WiFi connection
  while (status != WL_CONNECTED) {
 
    Serial.println("Attempting to connect to SSID: " + String(ssid));
    status = WiFi.begin(ssid, pass);
 
    // Wait 1 seconds for connection:
    delay(1000);
  }
}

// Define the addresses of the two MCP23017 I/O expanders
const uint8_t mcp1Address = 0x20; // Address of the first MCP23017
const uint8_t mcp2Address = 0x21; // Address of the second MCP23017

// Create instances of the MCP23017 class
MCP23017 mcp1(mcp1Address);
MCP23017 mcp2(mcp2Address);

const int inputPin = 2; // Pin for the input signal
const int ledPins[] = {2, 3, 4, 5}; // LED pins

void setup() {
  pinMode(inputPin, INPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Initialize the MCP23017 I/O expanders
  mcp1.begin();
  mcp2.begin();

  // Configure the pins of the first MCP23017 as inputs
  for (int i = 0; i < 14; i++) {
    mcp1.pinMode(i, INPUT);
  }

  // Configure the first 5 pins of the second MCP23017 as outputs
  for (int i = 0; i < 5; i++) {
    mcp2.pinMode(i, OUTPUT);
  }
}

void loop() {
  // Measure frequency
  int frequency = measureFrequency();
  // Segment frequency and turn on corresponding LED
  if (frequency >= 1 && frequency < 250000) {
    digitalWrite(ledPins[0], HIGH); // Turn on LED on pin D2
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
  } else if (frequency >= 250000 && frequency < 500000) {
    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[1], HIGH); // Turn on LED on pin D3
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
  } else if (frequency >= 500000 && frequency < 750000) {
    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], HIGH); // Turn on LED on pin D4
    digitalWrite(ledPins[3], LOW);
  } else if (frequency >= 750000 && frequency <= 1000000) {
    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], HIGH); // Turn on LED on pin D5
  }
  for (int i = 0; i < 14; i++) {
    int inputValue = mcp1.digitalRead(i);
    Serial.print("Input ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(inputValue);
  }
  for (int i = 0; i < 5; i++) {
    mcp2.digitalWrite(i, HIGH);
  }
}

int measureFrequency() {
  const unsigned long measurementPeriod = 1000; // Measurement period in microsecunds
  unsigned long startTime = micros(); // Start time of measurement
  unsigned int zeroCrossings = 0; // Count of zero crossings

  bool lastState = digitalRead(inputPin); // Initial state of the input signal

  while (micros() - startTime < measurementPeriod) {
    bool currentState = digitalRead(inputPin); // Current state of the input signal

    if (lastState!= currentState) {
      zeroCrossings++; // Increment zero crossing count when the state changes
    }

    lastState = currentState; // Update the last state
  }

  // Calculate frequency based on zero crossings and measurement period
  float frequency = (float)zeroCrossings / 2.0 / ((float)measurementPeriod / 1000.0); // Frequency in Hz (divided by 2 for full cycle)
  return frequency;
}