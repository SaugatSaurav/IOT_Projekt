//Should be written in Arduino App:



#include <WiFi.h>
#include <WebSocketsClient.h>
#include <DHT.h>

// ----------- DHT Configuration -----------
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ----------- WiFi Credentials -----------
const char* ssid = "TP-Link_81C8";
const char* password = "47777576";

// ----------- LED Pins -----------
#define RED_LED_PIN 5
#define GREEN_LED_PIN 18
#define BLUE_LED_PIN 19

// ----------- WebSocket Configuration -----------
const char* websocket_server = "informatik.hs-bremerhaven.de";
const int websocket_port = 443;
const char* websocket_path = "/docker-sausubedi-websocket/"; // or "/docker-sausubedi-websocket/"

// ----------- Root CA Certificate -----------


// ----------- WebSocket Client -----------
WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("[WSc] Disconnected!");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to: %s\n", websocket_server);
      webSocket.sendTXT("ESP32 connected");
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] Received: %.*s\n", length, payload);
      break;
    case WStype_ERROR:
      Serial.println("[WSc] Error occurred!");
      break;
    default:
      Serial.printf("[WSc] Event Type [%d]\n", type);
  }
}

void controlLEDs(float temperature, float humidity) {
  // Turn off all LEDs initially
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  if (temperature >= 30.0 && humidity <= 30.0) {
    // High temperature and low humidity -> Red LED
    digitalWrite(RED_LED_PIN, HIGH);

  } else if (temperature <= 15.0 && humidity >= 60.0) {
    // Low temperature and high humidity -> Blue LED
    digitalWrite(BLUE_LED_PIN, HIGH);

  } else if (temperature > 15.0 && temperature < 30.0 && humidity > 30.0 && humidity < 60.0) {
    // Moderate temperature and humidity -> Green LED
    digitalWrite(GREEN_LED_PIN, HIGH);

  } else if (temperature >= 30.0 && humidity > 30.0 && humidity < 60.0) {
    // High temperature and moderate humidity -> Red + Green LEDs
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  else if (temperature <= 15 && humidity > 30.0 && humidity < 60.0){
    // Low temperature and moderate humidity -> Blue + Green LEDs
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  else if (temperature > 15.0 && temperature < 30.0 && humidity <= 30.0 ){
    // Moderate temperature and Low humidity ->Red + Blue LEDs
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
   
  }
  else if (temperature > 15.0 && temperature < 30.0 && humidity >= 60.0 ){
    // Moderate temperature and High humidity -> Red + Blue + Green LEDs
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, HIGH);

  }  

  else{
    // Other than these
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    
  }
}


void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Starting...");

  dht.begin();

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  Serial.print("Connecting to WiFi SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected. IP: ");
  Serial.println(WiFi.localIP());

  webSocket.beginSSL(websocket_server, websocket_port, websocket_path);
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(10000);  // Retry every 10 seconds
}

void loop() {
  webSocket.loop();

  static unsigned long lastSend = 0;
  if (millis() - lastSend > 1000) {
    lastSend = millis();

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h)) {
      controlLEDs(t, h);

      char msg[64];
      snprintf(msg, sizeof(msg), "{\"temp\":%.1f,\"hum\":%.1f}", t, h);

      bool sent = webSocket.sendTXT(msg);
      Serial.print("Sent: ");
      Serial.println(msg);
      if (sent) {
        Serial.println("Message sent successfully");
      } else {
        Serial.println("Message failed to send!");
      }
    } else {
      Serial.println("Failed to read from DHT sensor!");
    }
  }
}

