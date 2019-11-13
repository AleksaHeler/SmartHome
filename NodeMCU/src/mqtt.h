#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

///Internet
const char* ssid = "your_ssid";
const char* password = "your_password";
const char* mqtt_server = "192.168.1.7";
const int   mqtt_port = 1883;

///MQTT
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[150];

void setup_wifi() {
  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.printf("\nWiFi connected: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT ");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.printf("connected: %s:%d\n", mqtt_server, mqtt_port);
    } else
      delay(1000);
  }
}

bool publish(float rt, float d_t, float d_h, float l, float at, bool pir){
  snprintf(msg, 150,"NodeMCU;ID=0001;INSIDETEMP=%.2lf;INSIDEHUMID=%.2lf;RADTEMP=%.2lf;LIGHT=%.2lf;PCTEMP=%.2lf;PIR=%d;", d_t, d_h, rt, l, at, pir);
  client.publish("devices", msg);
  return true;
}

void handleMQTT(){
  if (!client.connected())
    reconnect();
  client.loop();
}
