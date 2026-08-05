#include "sensor.h"
#include <Arduino.h>

static float currentLevel = 100.0f; 
static bool isRefilling = false;    

void SensorManager::begin() {
    Serial.println("[SensorManager] Initialisation de la simulation dynamique (vidange/remplissage).");
    currentLevel = 100.0f;
    isRefilling = false;
}

float SensorManager::getWaterLevelPercentage() {
    if (!isRefilling) {
        currentLevel -= 2.0f;
        if (currentLevel <= 0.0f) {
            currentLevel = 0.0f;
            isRefilling = true;
            Serial.println("  [SIMULATION] Réservoir vide (0%). Début du remplissage...");
        }
    } else {
        currentLevel += 5.0f;
        if (currentLevel >= 100.0f) {
            currentLevel = 100.0f;
            isRefilling = false;
            Serial.println("  [SIMULATION] Réservoir plein (100%). Début de la vidange...");
        }
    }
    return currentLevel;
}
