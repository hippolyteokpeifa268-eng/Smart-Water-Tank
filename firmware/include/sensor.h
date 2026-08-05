#pragma once

class SensorManager {
public:
    void begin();
    float getWaterLevelPercentage(); // Retourne le niveau converti en %
};
