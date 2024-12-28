import pandas as pd
from sqlalchemy.testing.plugin.plugin_base import logging

from DataCollecting.ORM.SQLConnection.PostgresConnection import *

class MeasurementTableManager:
    """
    Representative of the content from the measurement table. Can be used to request
    either the full table or a single row and add single or multiple row
    Attributes:
        data_df(DataFrame): content from the measurement table.
    """
    def __init__(self):

        self.data_df = None

    def _get_session(self):
        """
        This methode initializes a new postgresql session for interactions with the
        database.
        :return: A new PostgresConnection session
        :rtype: PostgresConnection
        """
        return PostgresConnection()

    def get_table(self):
        with self._get_session() as db_session:
            try:
                query = "SELECT * FROM measurement"
                self.data_df = pd.read_sql(query, db_session.bind)
            except Exception as e:
                logging.error(f"Error retrieving table measurement! Error:{e}")
                raise
        return self.data_df

    def get_row(self):
        return self.data_df

    def add_row(self, measurement_model):
        with self._get_session() as db_session:
            try:
                db_session.add(measurement_model)
                db_session.commit()

            except Exception as e:
                logging.error(f"Error writing table measurement! Error:{e}")

            finally:
                db_session.close()

    def add__multiple_rows(self, measurement_model):
        with self._get_session() as db_session:
            try:
                db_session.add_all(measurement_model)
                db_session.commit()

            except Exception as e:
                logging.error(f"Error writing table measurement! Error:{e}")

            finally:
                db_session.close()
