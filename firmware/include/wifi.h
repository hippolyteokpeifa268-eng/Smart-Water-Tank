#pragma once

class WiFiManager {
public:
    void begin();
    void loop();
    bool isConnected();
};