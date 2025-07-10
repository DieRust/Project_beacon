#include <WiFi.h>
#include <esp_now.h>
#include <Adafruit_NeoPixel.h>


uint8_t slave1Address[] = {0xC8,0xC9,0xA3,0x37,0xFD,0x9B}; // Slave1 
uint8_t slave2Address[] = {0xB0,0x81,0x84,0x03,0x60,0x4C}; // Slave2 
uint8_t slave3Address[] = {0x24, 0xD7, 0xEB, 0xEF, 0x23, 0x6A}; // Slave3
uint8_t slave4Address[] =  {0x08, 0xF9, 0xE0, 0x6B, 0xD6, 0x45}; // Slave4 

#define D1 2
#define D2 4
#define D3 5
#define D4 18

#define lb 26
#define pb 25
#define NUMPIXELS 4


Adafruit_NeoPixel pixels(NUMPIXELS, lb, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS, pb, NEO_GRB + NEO_KHZ800);

// Command structure: 'b' + 3 RGB bytes
typedef struct {
  char command;  // 'b' for blink command
  uint8_t r;     // Red value (0-255)
  uint8_t g;     // Green value (0-255)
  uint8_t b;     // Blue value (0-255)
} command_packet;

command_packet cmd;

String odebraneDane = "";

esp_now_peer_info_t peerInfo;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Function to set LED color
void ledColor(uint8_t r, uint8_t g, uint8_t b) {
  for(int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, r, g, b);
    
  }
  pixels.setBrightness(255);
  pixels.show();
  // Serial.println("color");
}

void ledColor2(uint8_t r, uint8_t g, uint8_t b) {
  for(int i = 0; i < NUMPIXELS; i++){
    pixels2.setPixelColor(i, r, g, b);
    
  }
  pixels2.setBrightness(255);
  pixels2.show();
  // Serial.println("color");
}


void setup() {
  Serial.begin(9600);
  Serial.println("zabij mnie");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); // dla pewności, że nie jest podłączony do AP

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // Dodaj każdego peera
  esp_now_peer_info_t peerInfo = {};
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, slave1Address, 6);
  esp_now_add_peer(&peerInfo);
  memcpy(peerInfo.peer_addr, slave2Address, 6);
  esp_now_add_peer(&peerInfo);
  memcpy(peerInfo.peer_addr, slave3Address, 6);
  esp_now_add_peer(&peerInfo);
  memcpy(peerInfo.peer_addr, slave4Address, 6);
  esp_now_add_peer(&peerInfo);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

  pixels.begin();
  pixels2.begin();


  cmd.command = 'b';
}


void loop() {
  ledColor(255,0,0);
  ledColor2(0,255,0);
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    odebraneDane = Serial.readStringUntil('\n'); 
    if(odebraneDane == "b1r"){
          Serial.println("b1r espnow");
          cmd.r =255;
          cmd.g =0;
          cmd.b =0;
          esp_now_send(slave1Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b1g"){
          Serial.println("b1g espnow");
          cmd.r = 0;
          cmd.g = 255;
          cmd.b = 0;
          esp_now_send(slave1Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b1o"){
          Serial.println("b1o espnow");
          cmd.r =0;
          cmd.g =0;
          cmd.b =0;
          esp_now_send(slave1Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b2r"){
          Serial.println("b2r espnow");
          cmd.r =255;
          cmd.g =0;
          cmd.b =0;
          esp_now_send(slave2Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b2g"){
          Serial.println("b2g espnow");
          cmd.r = 0;
          cmd.g = 255;
          cmd.b = 0;
          esp_now_send(slave2Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b2o"){
          Serial.println("b2o espnow");
          cmd.r =0;
          cmd.g =0;
          cmd.b =0;
          esp_now_send(slave2Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b3r"){
          Serial.println("b3r espnow");
          cmd.r =255;
          cmd.g =0;
          cmd.b =0;
          esp_now_send(slave3Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b3g"){
          Serial.println("b3g espnow");
          cmd.r = 0;
          cmd.g = 255;
          cmd.b = 0;
          esp_now_send(slave3Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b3o"){
          Serial.println("b3o espnow");
          cmd.r =0;
          cmd.g =0;
          cmd.b =0;
          esp_now_send(slave3Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b4r"){
          Serial.println("b4r espnow");
          cmd.r =255;
          cmd.g =0;
          cmd.b =0;
          esp_now_send(slave4Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b4g"){
          Serial.println("b4g espnow");
          cmd.r = 0;
          cmd.g = 255;
          cmd.b = 0;
          esp_now_send(slave4Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "b4o"){
          Serial.println("b4o espnow");
          cmd.r =0;
          cmd.g =0;
          cmd.b =0;
          esp_now_send(slave4Address, (uint8_t *) &cmd, sizeof(cmd));
    }
    if(odebraneDane == "d1"){
        Serial.println("spada bomba 1");
        digitalWrite(D1, HIGH);
        delay(3000);
        digitalWrite(D1, LOW);
    }
    if(odebraneDane == "d2"){
        Serial.println("spada bomba 2");

        digitalWrite(D2, HIGH);
        delay(3000);
        digitalWrite(D2, LOW);
    }
    if(odebraneDane == "d3"){
        Serial.println("spada bomba 3");

        digitalWrite(D3, HIGH);
        delay(3000);
        digitalWrite(D3, LOW);
    }
    if(odebraneDane == "d4"){
        Serial.println("spada bomba 4");

        digitalWrite(D4, HIGH);
        delay(3000);
        digitalWrite(D4, LOW);
    }
  }

}