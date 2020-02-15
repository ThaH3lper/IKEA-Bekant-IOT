#include "Arduino.h"

#define NOT_SET 0

typedef std::function<void(void)> Callback;

class Delay {
    private:
        unsigned long m_nextTimeStamp = NOT_SET;
        Callback m_callback;

    public:
        Delay() = default;
        void update(unsigned long millis);
        bool isRunning();

        // Returns true if started, else false is already running.
        bool start(unsigned long millis, int delayMs, Callback callback);
};
