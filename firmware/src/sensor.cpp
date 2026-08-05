#include "sensor.h"
#include <Arduino.h>

const int SENSOR_PIN = 34;

void SensorManager::begin() {
    pinMode(SENSOR_PIN, INPUT);
}

float SensorManager::getWaterLevelPercentage() {
    int rawValue = analogRead(SENSOR_PIN);
    float percentage = (rawValue / 4095.0f) * 100.0f;
    
    if (percentage < 0.0f) percentage = 0.0f;
    if (percentage > 100.0f) percentage = 100.0f;
    
    return percentage;
}
