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
const unsigned long interval = 2000; // Intervalle de 2 secondes

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n=== SMART WATER TANK MONITOR (SIMULATION) ===");
    
    wifi.begin();
    sensor.begin();
    mqtt.begin();
    display.begin();
}

void loop() {
    wifi.loop();
    mqtt.loop();

    unsigned long currentMillis = millis();
    
    // Exécution toutes les 2000 ms (2 secondes)
    if (currentMillis - lastReadTime >= interval) {
        lastReadTime = currentMillis;
        
        // 1. Lecture du niveau d'eau simulé
        float level = sensor.getWaterLevelPercentage();
        
        // 2. Affichage sur l'écran
        display.update(level);
        
        // 3. Publication MQTT
        mqtt.publishData(level);
        mqtt.checkAndPublishAlert(level);
        
        // 4. Déclenchement d'alerte locale si le niveau est inférieur à 20%
        if (level < 20.0f) {
            Serial.println("  [ALERTE CRITIQUE] Niveau d'eau bas (< 20%) !");
        }
        
        Serial.println("----------------------------------------------");
    }
}
