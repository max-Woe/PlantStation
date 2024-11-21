import pandas as pd
from sqlalchemy.testing.plugin.plugin_base import logging

from DataCollecting.ORM.SQLConnection.PostgresConnection import *

class SensorTableManager:
    def __init__(self):
        self.data_df = None

    def _get_session(self):
        return PostgresConnection()

    def get_table(self):
        with self._get_session() as db_session:
            try:
                query = "SELECT * FROM sensor"
                self.data_df = pd.read_sql(query, db_session.bind)
            except Exception as e:
                logging.error(f"Error retrieving table sensor! Error:{e}")
                raise
        return self.data_df

    def get_row(self):
        return self.data_df

    def add_row(self, sensor_model):
        with self._get_session() as db_session:
            try:
                db_session.add(sensor_model)
                db_session.commit()

            except Exception as e:
                logging.error(f"Error writing table measurement! Error:{e}")

            finally:
                db_session.close()
