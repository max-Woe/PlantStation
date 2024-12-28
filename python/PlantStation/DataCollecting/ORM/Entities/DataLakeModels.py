"""
Database models for the application.

This module defines SQLAlchemy models for the `measurement`, `sensor`, and `station` tables.
"""

from datetime import datetime
from sqlalchemy.orm import Mapped, declarative_base, mapped_column, relationship

Base = declarative_base()

metadata = Base.metadata

class MeasurementModel(Base):
    """
    Represents a measurement in the database.

    Attributes:
        id (int): Unique ID of the measurement.
        value (float): The measured value.
        sensor_id (int, optional): The ID of the associated sensor (can be `None`).
        sensor_reference (int): Reference ID of the sensor.
        recorded_at (datetime): The timestamp when the measurement was taken.
        created_at (datetime): The timestamp when the database entry was created.
    """
    __tablename__ = 'measurement'

    id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    value: Mapped[float]
    sensor_id: Mapped[int] = mapped_column(nullable=True)
    sensor_reference: Mapped[int]
    recorded_at: Mapped[datetime]
    created_at: Mapped[datetime]

    def __repr__(self):
        """
        Returns a human-readable representation of the object.
        """
        return f"id: {self.id}, vlaue: {self.value}, unit: {self.unit}, sensor_id: {self.sensor_id}, recorded_at: {self.recorded_at}, created_at: {self.created_at}"



class SensorModel(Base):
    """
    Represents a sensor in the database.

    Attributes:
        id (int): Unique ID of the sensor.
        type (str): The type of the sensor (e.g., temperature, humidity).
        unit (str): The unit of the sensor (e.g., °C, %).
        station_id (int, optional): The ID of the associated station (can be `None`).
        created_at (datetime): The timestamp when the sensor was created.
        measurements (list[MeasurementModel]): List of associated measurements.
    """
    __tablename__ = 'sensor'

    id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    type: Mapped[str]
    unit: Mapped[str]
    station_id: Mapped[int] = mapped_column(nullable=True)
    created_at: Mapped[datetime]

    measurements = relationship("SensorModel", back_populates="measurement")
    """
    Returns a human-readable representation of the object.
    """
    def __repr__(self):
        return f"id: {self.id}, type: {self.type}, unit: {self.unit}, station_id: {self.station_id}, created_at: {self.created_at}"


class StationModel(Base):
    """
    Represents a station in the database.

    Attributes:
        id (int): Unique ID of the station.
        position (str): The location of the station (e.g., bedroom, living room).
        sensors_count (int): The number of associated sensors.
        created_at (datetime): The timestamp when the station was created.
        sensors (list[SensorModel]): List of associated sensors.
    """
    __tablename__ = 'station'

    id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    position: Mapped[str]
    sensors_count: Mapped[int] = mapped_column(nullable=False)
    created_at: Mapped[datetime]

    sensors = relationship("StationModel", back_populates="sensor")
    """
    Returns a human-readable representation of the object.
    """
    def __repr__(self):
        return f"id: {self.id}, position: {self.position}, unit: {self.unit}, station_id: {self.station_id}, created_at: {self.created_at}"

class AppExceptionModel(Base):
    """
    Represents a measurement in the database.

    Attributes:
        id (int): Unique ID of the measurement.
        value (float): The measured value.
        sensor_id (int, optional): The ID of the associated sensor (can be `None`).
        sensor_reference (int): Reference ID of the sensor.
        recorded_at (datetime): The timestamp when the measurement was taken.
        created_at (datetime): The timestamp when the database entry was created.
    """
    __tablename__ = 'app_exceptions'

    id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    exception_message: Mapped[str]
    recorded_at: Mapped[datetime]

    def __repr__(self):
        """
        Returns a human-readable representation of the object.
        """
        return f"id: {self.id}, exception_message: {self.exception_message}, recorded_at: {self.recorded_at}"
