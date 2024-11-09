#include <Arduino.h>
#include <Uhr\Uhr.h>

// RTC_DS3231 rtc;

// char wochentage[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

Uhr::Uhr()
{
    // RTC_DS3231 _rtc;
    strncpy(_wochentage[0], "Sonntag", sizeof(_wochentage[0]));
    strncpy(_wochentage[1], "Montag", sizeof(_wochentage[1]));
    strncpy(_wochentage[2], "Dienstag", sizeof(_wochentage[2]));
    strncpy(_wochentage[3], "Mittwoch", sizeof(_wochentage[3]));
    strncpy(_wochentage[4], "Donnerstag", sizeof(_wochentage[4]));
    strncpy(_wochentage[5], "Freitag", sizeof(_wochentage[5]));
    strncpy(_wochentage[6], "Samstag", sizeof(_wochentage[6]));
    
    if (! _rtc.begin()) 
    {
        Serial.println("Finde keine RTC");
        while (true);
    }

    if (_rtc.lostPower()) 
    {
        _rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Zeit vom Compiler setzen
    }

    _date_time = _rtc.now();
    
    Serial.println(_date_time.day());
    _current_time.hour = get_hour();
    _current_time.minute = get_minute();
    _current_time.second = get_second();
}

void Uhr::update_time()
{
    _date_time = _rtc.now();
}
int Uhr::get_year()
{
    return _date_time.year();
}

int Uhr::get_month()
{
    return _date_time.month();
}

int Uhr::get_day()
{
    return _date_time.day();
}

int Uhr::get_hour()
{
    return _date_time.hour();
}

int Uhr::get_minute()
{
    return _date_time.minute();
}

int Uhr::get_second()
{
    return _date_time.second();
}

int Uhr::get_day_of_week()
{
    return _date_time.dayOfTheWeek();
}

Time Uhr::get_time()
{
    return _current_time;
}

DateTime Uhr::get_date()
{
    return _date_time;
}

String Uhr::get_day_of_week_string()
{
    return _wochentage[get_day_of_week()];
}

String Uhr::to_string()
{  
     return String(_date_time.year()) + "-" +
                        String(_date_time.month()) + "-" +
                        String(_date_time.day()) + " " +
                        String(_date_time.hour()) + ":" +
                        String(_date_time.minute()) + ":" +
                        String(_date_time.second());

}
