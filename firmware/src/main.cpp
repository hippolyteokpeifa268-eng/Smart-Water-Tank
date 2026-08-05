#include <Arduino.h>
#include "sensor.h"
#include "wifi.h"
#include "mqtt.h"
#include "display.h"

SensorManager sensor;
WiFiManager wifi;
MQTTManager mqtt;
DisplayManager display;

unsigned long lastReadTime = 0;
const unsigned long interval = 2000;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n=== SMART WATER TANK MONITOR (DYNAMIC SIMULATION) ===");
    
    wifi.begin();
    sensor.begin();
    mqtt.begin();
    display.begin();
}

void loop() {
    wifi.loop();
    mqtt.loop();

    unsigned long currentMillis = millis();
    
    if (currentMillis - lastReadTime >= interval) {
        lastReadTime = currentMillis;
        
        float level = sensor.getWaterLevelPercentage();
        
        display.update(level);
        mqtt.publishData(level);
        mqtt.checkAndPublishAlert(level);
        
        if (level <= 15.0f && level > 0.0f) {
            Serial.println("  [ALERTE CRITIQUE] Niveau d'eau critique (<= 15%) !");
        } else if (level == 0.0f) {
            Serial.println("  [ÉTAT] Réservoir considéré VIDE (0%).");
        }
        
        Serial.println("----------------------------------------------");
    }
}
