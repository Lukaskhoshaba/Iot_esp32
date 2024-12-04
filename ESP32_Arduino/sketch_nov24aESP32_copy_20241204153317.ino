#include "aws_secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <DHT.h>

// DHT11 Settings
#define DHTPIN  21       // GPIO-pinnen där DHT11 är ansluten
#define DHTTYPE DHT11    // Typ av sensor
DHT dht(DHTPIN, DHTTYPE);

// MQTT topics
#define AWS_IOT_PUBLISH_TOPIC "/telemetry"
#define AWS_IOT_SUBSCRIBE_TOPIC "/downlink"

// Global variables
WiFiClientSecure net;
MQTTClient client(1024);

void connectWiFi() {
  Serial.println("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
}

void connectAWS() {
  Serial.println("Setting up AWS IoT connection...");
  
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.begin(AWS_IOT_ENDPOINT, 8883, net);
  Serial.println("Connecting to AWS IoT...");
  while (!client.connect(THINGNAME)) { // Använder THINGNAME som är definierat i aws_secrets.h
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected to AWS IoT!");

  // Subscribe to topics
  client.subscribe(String(THINGNAME) + AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("Subscribed to topic: " + String(THINGNAME) + AWS_IOT_SUBSCRIBE_TOPIC);
}

void publishMessage(float temperature, float humidity) {
  // Skapa ett JSON-objekt
  String message = "{\"temperature\": " + String(temperature, 2) + ", \"humidity\": " + String(humidity, 2) + "}";
  Serial.print("Publishing message: ");
  Serial.println(message);

  if (client.publish(String(THINGNAME) + AWS_IOT_PUBLISH_TOPIC, message)) {
    Serial.println("Message published successfully!");
  } else {
    Serial.println("Failed to publish message.");
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin(); // Initiera DHT11-sensorn
  connectWiFi();
  connectAWS();
}

void loop() {
  if (!client.connected()) {
    Serial.println("Disconnected from AWS IoT, reconnecting...");
    connectAWS();
  }

  // Läs data från DHT11-sensorn
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    publishMessage(temperature, humidity);
  }

  delay(10000); // Publish every 10 seconds
}

