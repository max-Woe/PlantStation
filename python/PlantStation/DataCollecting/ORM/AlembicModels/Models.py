from datetime import datetime

from sqlalchemy.orm import Mapped, declarative_base, mapped_column
from sqlalchemy import String

Base = declarative_base()

metadata = Base.metadata

class MeasurementModel(Base):
    __tablename__ = 'measurement'

    id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    value: Mapped[float]
    sensor_id: Mapped[int] = mapped_column(nullable=True)
    recorded_at: Mapped[datetime]
    created_at: Mapped[datetime]

    def __repr__(self):
        return f"id: {self.id}, vlaue: {self.value}, unit: {self.unit}, sensor_id: {self.sensor_id}, recorded_at: {self.recorded_at}, created_at: {self.created_at}"



class SensorModel(Base):
    __tablename__ = 'sensor'

    id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    type: Mapped[str]
    unit: Mapped[str]
    station_id: Mapped[int] = mapped_column(nullable=True)
    created_at: Mapped[datetime]

    def __repr__(self):
        return f"id: {self.id}, type: {self.type}, unit: {self.unit}, station_id: {self.station_id}, created_at: {self.created_at}"
