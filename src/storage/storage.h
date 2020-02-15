#include "Arduino.h"
#include <EEPROM.h>

#define CONFIG_LENGTH 64

struct WifiConfig { 
    char ssid[CONFIG_LENGTH] = "nothing";
    char pass[CONFIG_LENGTH] = "nothing";
  };

class Storage {
    private:
        uint m_wificonfig_addr = 0;

    public:
        Storage();
        void saveWifiConfig(WifiConfig data);
        WifiConfig loadWifiConfig();
};
