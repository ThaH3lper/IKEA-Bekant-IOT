#include "storage.h"

Storage::Storage() {
    EEPROM.begin(CONFIG_LENGTH * 2);
}

void Storage::saveWifiConfig(WifiConfig data) {
    EEPROM.put(m_wificonfig_addr,data);
    EEPROM.commit(); 
}

WifiConfig Storage::loadWifiConfig() {
    WifiConfig data;
    EEPROM.get(m_wificonfig_addr, data);
    return data;
}