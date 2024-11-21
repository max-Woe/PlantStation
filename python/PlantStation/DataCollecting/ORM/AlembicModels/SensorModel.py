# from datetime import datetime
#
# from sqlalchemy.orm import Mapped, mapped_column
# from sqlalchemy import String
# from Base import Base
#
# metadata = Base.metadata
#
# class SensorModel(Base):
#     __tablename__ = 'sensor'
#
#     id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)
#     type: Mapped[String]
#     unit: Mapped[String]
#     station_id: Mapped[int] = mapped_column(nullable=True)
#     created_at: Mapped[datetime]
#
#     def __repr__(self):
#         return f"id: {self.id}, type: {self.type}, unit: {self.unit}, station_id: {self.station_id}, created_at: {self.created_at}"
