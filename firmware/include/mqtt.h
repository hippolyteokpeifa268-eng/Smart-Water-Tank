#pragma once

class MQTTManager {
public:
    void begin();
    void loop();
    void publishData(float levelPercentage);
    void checkAndPublishAlert(float levelPercentage); // Gère la condition < 20% pour la notification
};