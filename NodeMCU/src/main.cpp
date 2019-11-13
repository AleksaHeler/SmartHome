#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include "DHT.h"

///Defines
#define SEND_INTERVAL 60       //seconds
#define DHT_INSIDE_PIN         D5
#define DHT_OUTSIDE_PIN        D6
#define PIR_PIN                D7
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET LED_BUILTIN

///Files
#include "mqtt.h"
#include "temp.h"
#include "analog.h"
#include "display.h"

DHT dht_inside(DHT_INSIDE_PIN, DHT11);
DHT dht_outside(DHT_OUTSIDE_PIN, DHT11);
Adafruit_SSD1306 display(OLED_RESET);
void draw_display(float rt, float dht_t, float dht_h, float l, float at, bool pir);
void setup_display(bool m);

void setup() {
  Serial.begin(115200);
  setup_display(false);

  dht_inside.begin();
  dht_outside.begin();
  Serial.println("DHT started");

  setup_analog();
  Serial.println("Analog started");

  setup_wifi();
  setup_display(true);
  delay(4000);
}

void loop() {
  handleMQTT();

  //Every # seconds, read values and publish via MQTT
  if (millis() - lastMsg > SEND_INTERVAL*1000) {
    lastMsg = millis();

    //Reading
    float rt,i=0; do{ rt = get_temp(); i++; } while(rt < -500 && i < 4);//radiator
    float dht_t = dht_inside.readTemperature();       //inside
    float dht_h = dht_inside.readHumidity();
    float l = get_light();                            //inside
    float at = get_analog_temp();                     //pc
    bool pir = digitalRead(D4);

    //Sending
    publish(rt, dht_t, dht_h, l, at, pir);
    Serial.println("Sending");

    //Displaying
    draw_display(rt, dht_t, dht_h, l, at, pir);
  }
}

void draw_display(float rt, float dht_t, float dht_h, float l, float at, bool pir){
  display.clearDisplay();
  display.setCursor(10, 0);
  display.print("t:  ");
  display.println(dht_t);
  display.setCursor(10, 10);
  display.print("h:  ");
  display.println(dht_h);
  display.setCursor(10, 20);
  display.print("rt: ");
  display.println(rt);
  display.setCursor(10, 30);
  display.print("l:  ");
  display.println(l);
  display.setCursor(10, 40);
  display.print("at: ");
  display.println(at);
  display.setCursor(10, 50);
  display.print("p:  ");
  display.println(pir);
  display.display();
}

void setup_display(bool m){
  if(m){
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("WiFi\n  ");
    display.println(ssid);
    display.print("IP\n  ");
    display.println(WiFi.localIP());
    display.print("MQTT\n  ");
    display.println(mqtt_server);
    display.display();
  }else{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("NodeMCU");
    display.println("Connecting...");
    display.setTextSize(1);
    display.display();
  }
 }
