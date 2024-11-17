from datetime import datetime

from sqlalchemy.orm import Mapped, declarative_base, mapped_column

Base = declarative_base()

metadata = Base.metadata

class MeasurementModel(Base):
    __tablename__ = 'measurement'

    recording_id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
    value: Mapped[float]
    unit: Mapped[str]
    sensor_id: Mapped[int] = mapped_column(nullable=True)
    recorded_at: Mapped[datetime]
    created_at: Mapped[datetime]

    def __repr__(self):
        return f"id: {self.recording_id}, vlaue: {self.value}, unit: {self.unit}, sensor_id: {self.sensor_id}, recorded_at: {self.recorded_at}, created_at: {self.created_at}"
