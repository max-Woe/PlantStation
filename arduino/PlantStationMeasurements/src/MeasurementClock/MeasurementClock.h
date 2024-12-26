#ifndef MEASUREMENTCLOCK_H
#define MEASUREMENTCLOCK_H

#include <Arduino.h>
#include <RTClib.h>

struct Time{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

class MeasurementClock
{
    public:
        MeasurementClock();

        int get_year();
        int get_month();
        int get_day();
        int get_hour();
        int get_minute();
        int get_second();
        int get_day_of_week();
        Time get_time();
        DateTime get_date();
        String get_day_of_week_string();
        String to_string();
        void update_time();
        DateTime get_date_time();
    
    private:
        DateTime _date_time;
        Time _current_time;
        char _wochentage[7][12];
        RTC_DS3231 _rtc;
        bool _rtc_initialized;
        
};

#endif