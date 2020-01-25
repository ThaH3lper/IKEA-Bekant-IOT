#include "relay.h"

byte RELAY_ONE_ENABLE_CMD[] = {0xA0, 0x01, 0x01, 0xA2};  
byte RELAY_ONE_DISABLE_CMD[] = {0xA0, 0x01, 0x00, 0xA1};
byte RELAY_TWO_ENABLE_CMD[] = {0xA0, 0x02, 0x01, 0xA3};  
byte RELAY_TWO_DISABLE_CMD[] = {0xA0, 0x02, 0x00, 0xA2};

void enableRelay(int index) {
    if (index == RELAY_ONE) {
        Serial.write(RELAY_ONE_ENABLE_CMD, sizeof(RELAY_ONE_ENABLE_CMD));
    } else if (index == RELAY_TWO) {
        Serial.write(RELAY_TWO_ENABLE_CMD, sizeof(RELAY_TWO_ENABLE_CMD));
    }
    Serial.flush();
}

void disableRelay(int index) {
    if (index == RELAY_ONE) {
        Serial.write(RELAY_ONE_DISABLE_CMD, sizeof(RELAY_ONE_DISABLE_CMD));
    } else if (index == RELAY_TWO){
        Serial.write(RELAY_TWO_DISABLE_CMD, sizeof(RELAY_TWO_DISABLE_CMD));
    }
    Serial.flush();
}