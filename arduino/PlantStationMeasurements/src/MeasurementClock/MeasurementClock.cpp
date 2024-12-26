#include <Arduino.h>
#include <MeasurementClock\MeasurementClock.h>

// RTC_DS3231 rtc;

// char wochentage[7][12] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

MeasurementClock::MeasurementClock(){
    strncpy(_wochentage[0], "Sonntag", sizeof(_wochentage[0]));
    strncpy(_wochentage[1], "Montag", sizeof(_wochentage[1]));
    strncpy(_wochentage[2], "Dienstag", sizeof(_wochentage[2]));
    strncpy(_wochentage[3], "Mittwoch", sizeof(_wochentage[3]));
    strncpy(_wochentage[4], "Donnerstag", sizeof(_wochentage[4]));
    strncpy(_wochentage[5], "Freitag", sizeof(_wochentage[5]));
    strncpy(_wochentage[6], "Samstag", sizeof(_wochentage[6]));

    if (! _rtc.begin()){
        _rtc_initialized = false;
        Serial.println("Finde keine RTC");
        _date_time = DateTime(2000, 0, 0, 0, 0, 0);
        return;
    }
    else{
        _rtc_initialized = true;
    }

    if (_rtc.lostPower()){
        _rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Zeit vom Compiler setzen
    }

    _date_time = _rtc.now();
    _current_time.hour = get_hour();
    _current_time.minute = get_minute();
    _current_time.second = get_second();
}

void MeasurementClock::update_time(){
    if(_rtc_initialized)
    {
        //TODO: Klären wieso Zeit nicht läuft.
        Serial.println("TIme updated");
        _date_time = _rtc.now();
    }
}

int MeasurementClock::get_year(){
    return _date_time.year();
}

int MeasurementClock::get_month()
{
    return _date_time.month();
}

int MeasurementClock::get_day()
{
    return _date_time.day();
}

int MeasurementClock::get_hour()
{
    return _date_time.hour();
}

int MeasurementClock::get_minute()
{
    return _date_time.minute();
}

int MeasurementClock::get_second()
{
    return _date_time.second();
}

int MeasurementClock::get_day_of_week()
{
    return _date_time.dayOfTheWeek();
}

Time MeasurementClock::get_time()
{
    return _current_time;
}

DateTime MeasurementClock::get_date()
{
    return _date_time;
}

String MeasurementClock::get_day_of_week_string()
{
    return _wochentage[get_day_of_week()];
}

String MeasurementClock::to_string()
{  
     return String(_date_time.year()) + "-" +
                        String(_date_time.month()) + "-" +
                        String(_date_time.day()) + " " +
                        String(_date_time.hour()) + ":" +
                        String(_date_time.minute()) + ":" +
                        String(_date_time.second());

}
 DateTime MeasurementClock::get_date_time()
 {
    return _date_time;
 }
