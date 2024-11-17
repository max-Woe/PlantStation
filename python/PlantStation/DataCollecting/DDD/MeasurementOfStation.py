from datetime import datetime, time, date
import pandas as pd

class MeasurementOfStation:
    def __init__(self, measurement_dict:dict=None):
        try:
            if isinstance(measurement_dict, dict):
                self.time_stamp = datetime.strptime(measurement_dict["time_stamp"], "%Y-%m-%d %H:%M:%S")
                self.temperature = float(measurement_dict["temperature"])
                self.humidity = float(measurement_dict["humidity"])
                self.water_level = float(measurement_dict["water_level"])
                self.measurement_values_dict = {'temperature': self.temperature, 'humidity': self.humidity, 'water_level': self.water_level}
                self.seperate_time_stampe()
            else:
                raise ValueError("measurements_dict is not a dictionary!")
        except ValueError as e:
            print(f"Error: {e}")
    @property
    def time_stamp(self):
        return self._time_stamp

    @time_stamp.setter
    def time_stamp(self, time_stamp_value):
        if isinstance(time_stamp_value, datetime):
            self._time_stamp = time_stamp_value
        else:
            raise ValueError("time_stamp is not a datetime object!")

    @property
    def temperature(self):
        return self._temperature

    @temperature.setter
    def temperature(self, temperature_value):
        if isinstance(temperature_value, float):
            self._temperature = temperature_value
        else:
            raise ValueError("temperature is not a float!")

    @property
    def humidity(self):
        return self._humidity

    @humidity.setter
    def humidity(self, humidity_value):
        if isinstance(humidity_value, float):
            self._humidity = humidity_value
        else:
            raise ValueError("humidity is not a float!")

    @property
    def water_level(self):
        return self._water_level

    @water_level.setter
    def water_level(self, water_level_value):
        if isinstance(water_level_value, float):
            self._water_level = water_level_value
        else:
            raise ValueError("water_level is not a float!")

    @property
    def time(self):
        return self._time

    @time.setter
    def time(self, time_value):
        if isinstance(time_value, time):
            self._time = time_value
        else:
            raise ValueError("time is not a time object!")

    @property
    def date(self):
        return self._date

    @date.setter
    def date(self, date_value):
        if isinstance(date_value, date):
            self._date = date_value
        else:
            raise ValueError("date is not a date object!")

    @property
    def year(self):
        return self._year

    @year.setter
    def year(self, year_value):
        if isinstance(year_value, int):
            self._year = year_value
        else:
            raise ValueError("year is not an integer!")

    @property
    def month(self):
        return self._month

    @month.setter
    def month(self, month_value):
        if isinstance(month_value, int):
            self._month = month_value
        else:
            raise ValueError("month is not an integer!")

    @property
    def day(self):
        return self._day

    @day.setter
    def day(self, day_value):
        if isinstance(day_value, int):
            self._day = day_value
        else:
            raise ValueError("day is not an integer!")

    @property
    def hour(self):
        return self._hour

    @hour.setter
    def hour(self, hour_value):
        if isinstance(hour_value, int):
            self._hour = hour_value
        else:
            raise ValueError("hour is not an integer!")

    @property
    def minute(self):
        return self._minute

    @minute.setter
    def minute(self, minute_value):
        if isinstance(minute_value, int):
            self._minute = minute_value
        else:
            raise ValueError("minute is not an integer!")

    @property
    def second(self):
        return self._second

    @second.setter
    def second(self, second_value):
        if isinstance(second_value, int):
            self._second = second_value
        else:
            raise ValueError("second is not an integer!")

    def seperate_time_stampe(self):
        self.time = self.time_stamp.time()
        self.date = self.time_stamp.date()
        self.year = self.time_stamp.year
        self.month = self.time_stamp.month
        self.day = self.time_stamp.day
        self.hour = self.time_stamp.hour
        self.minute = self.time_stamp.minute
        self.second = self.time_stamp.second

    def get_measurements_as_df(self):
        df = pd.DataFrame(columns=['time_stamp', 'value', 'unit','recorded_at', 'created_at' ])
        for key, measurement in self.measurement_values_dict.items():
            if key == 'temperature':
                unit = "°C"
            elif key == 'humidity':
                unit = "%rel"
            elif key == 'water_level':
                unit = "%"
            new_row = pd.DataFrame({'time_stamp': [self.time_stamp],
                                    'value': [measurement],
                                    'unit': [unit],
                                    'recorded_at': [self.time_stamp],
                                    'created_at': [datetime.now()]})

            # Füge die neue Zeile zum bestehenden DataFrame hinzu
            df = pd.concat([df, new_row], ignore_index=True)

        return df
