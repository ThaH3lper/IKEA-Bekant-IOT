#include "delay.h"

void Delay::update(unsigned long millis) {
    if (m_nextTimeStamp == NOT_SET) {
        return;
    }

    if (millis >= m_nextTimeStamp) {
        m_nextTimeStamp = NOT_SET;
        m_callback();
    }
}

bool Delay::isRunning() {
    return m_nextTimeStamp != NOT_SET;
}

bool Delay::start(unsigned long millis, int delayMS, Callback callback) {
    if (m_nextTimeStamp != NOT_SET) {
        return false;
    }
    
    m_nextTimeStamp = millis + delayMS;
    m_callback = callback;

    return true;
}
