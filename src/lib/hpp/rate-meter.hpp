#ifndef RATE_METER_HPP
#define RATE_METER_HPP

#include <chrono>

using namespace std::chrono;

class RateMeter {
public:
    RateMeter();
    void updateRate();
    double getRate();
    
private:
    double rate;
    time_point<high_resolution_clock> lastSampleSystemClock;
};

#endif
