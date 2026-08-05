#pragma once

class MQTTManager {
public:
    void begin();
    void loop();
    void publishData(float level);
};
