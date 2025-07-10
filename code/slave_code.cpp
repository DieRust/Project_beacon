#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#define SLAVE_NUM 1
#define PIN D1
#define NUMPIXELS 3

// NeoPixel setup
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Command structure: 'b' + 3 RGB bytes (must match master)
typedef struct {
  char command;  // 'b' for blink command
  uint8_t r;     // Red value (0-255)
  uint8_t g;     // Green value (0-255)
  uint8_t b;     // Blue value (0-255)
} command_packet;

command_packet receivedCmd;

// Function to set LED color
void ledColor(uint8_t r, uint8_t g, uint8_t b) {
  for(int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, r, g, b);
  }
  pixels.setBrightness(255);
  pixels.show();
}

// Simple LED blink function (non-blocking)
void simpleBlink() {
  digitalWrite(LED_BUILTIN, LOW);   // On
  digitalWrite(LED_BUILTIN, HIGH);  // Off immediately
}

// Callback function executed when data is received
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  // Simple LED blink when packet received
  simpleBlink();
  
  // Copy received data
  memcpy(&receivedCmd, incomingData, sizeof(receivedCmd));
  
  // Check if it's a valid blink command
  if (receivedCmd.command == 'b' && len == sizeof(command_packet)) {
    // Set NeoPixel color
    ledColor(receivedCmd.r, receivedCmd.g, receivedCmd.b);
    
    // Debug output
    Serial.print("<<< [SLAVE ");
    Serial.print(SLAVE_NUM);
    Serial.print("] Received blink command from ");
    for (int i = 0; i < 6; i++) {
      Serial.printf("%02X", mac[i]);
      if (i < 5) Serial.print(":");
    }
    Serial.print(" | RGB: ");    Serial.print(receivedCmd.r); Serial.print(",");
    Serial.print(receivedCmd.g); Serial.print(",");
    Serial.println(receivedCmd.b);
  } else {
    Serial.print("<<< [SLAVE ");
    Serial.print(SLAVE_NUM);
    Serial.println("] Received invalid command");
  }
}

void setup() {
  Serial.begin(9600);
  
  // Initialize built-in LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Turn off initially (inverted)
  
  // Initialize NeoPixels
  pixels.begin();
  ledColor(0, 0, 0); // Start with LEDs off
  
  // Set WiFi mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("<<< [SLAVE] Error initializing ESP-NOW");
    return;
  }
  
  // Set ESP-NOW role as slave
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  
  // Register receive callback
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println();
  Serial.print("<<< [SLAVE ");
  Serial.print(SLAVE_NUM);  Serial.print("] MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("<<< [SLAVE] ESP-NOW initialized, ready to receive commands");
}

void loop() {
  // Keep LEDs active and responsive
  delay(100);
}