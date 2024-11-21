import importlib
import pandas as pd
from requests import session
from sqlalchemy.testing.plugin.plugin_base import logging

from DataCollecting.ORM.SQLConnection.PostgresConnection import *

class MeasurementTableManager:
    def __init__(self):
        self.data_df = None

    def _get_session(self):
        return PostgresConnection()

    def get_table(self):

        # connection = self._get_connection()
        with self._get_session() as db_session:
            try:
                query = "SELECT * FROM measurement"
                self.data_df = pd.read_sql(query, db_session.bind)
            except Exception as e:
                logging.error(f"Error retrieving table measurement! Error:{e}")
                raise
            # connection.close()
        return self.data_df

    def get_row(self):
        return self.data_df

    def add_row(self, MeasurementSQL):
        # connection = self._get_connection()
        with self._get_session() as db_session:
            try:
                # db_session = db_session.get_session()
                db_session.add(MeasurementSQL)
                db_session.commit()

            except Exception as e:
                logging.error(f"Error writing table measurement! Error:{e}")

            finally:
                db_session.close()
        # connection.close()




