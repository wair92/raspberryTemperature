#ifndef TIMEFORMAT_H
#define TIMEFORMAT_H

#include <string>
#include <ctime>

class TimeFormat{
public:
    static std::string getCurrentMonth();
    static std::string getCurrentHour();
    static std::string getCurrentDay();
    static std::string getCurrentDaystamp();
    static std::string getLastDayStamp();
    static std::string getCurrentTimeStamp();
private:
    static tm* getLocalTime();
};

#endif
