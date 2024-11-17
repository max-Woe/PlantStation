import importlib
import pandas as pd
from requests import session

from DataCollecting.ORM.SQLConnection.PostgresConnection import *

class MeasurementTable:
    def __init__(self):
        self.data_df = None

    def get_table(self):
        connection = PostgresConnection()
        query = "SELECT * FROM measurement"
        self.data_df = pd.read_sql(query, connection.engine)
        connection.close()
        return self.data_df

    def get_row(self):
        return self.data_df

    def add_row(self, MeasurementSQL):
        connection = PostgresConnection()
        session = connection.get_session()
        session.add(MeasurementSQL)
        session.close()
        connection.close()




