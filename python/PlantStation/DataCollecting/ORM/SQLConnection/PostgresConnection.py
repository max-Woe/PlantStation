import os
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.exc import SQLAlchemyError
from sqlalchemy.pool import QueuePool
from dotenv import load_dotenv

# Lade Umgebungsvariablen aus der .env-Datei
load_dotenv()


class PostgresConnection:
    def __init__(self, db_url: str = None, pool_size: int = 5, max_overflow: int = 10):
        """
        Initialize the PostgreSQL connection with pooling support.

        :param db_url: Database connection URL (optional, can be passed or fetched from environment variable)
        :param pool_size: Number of connections to keep in the pool (default: 5)
        :param max_overflow: Number of connections to allow beyond pool_size (default: 10)
        """
        # Falls keine DB_URL übergeben wird, hole sie aus der Umgebungsvariablen
        self.db_url = db_url or os.getenv('DATABASE_URL')

        # Engine mit Connection Pooling erstellen
        self.engine = create_engine(
            self.db_url,
            poolclass=QueuePool,
            pool_size=pool_size,
            max_overflow=max_overflow,
            echo=False  # Setze auf True für Debugging von SQL-Abfragen
        )

        self.Session = sessionmaker(bind=self.engine)

    def get_session(self):
        """Returns a new session from the pool."""
        try:
            session = self.Session()
            return session
        except SQLAlchemyError as e:
            print(f"Error creating session: {e}")
            return None

    def close(self):
        """Properly closes the connection pool."""
        # self.Session.close()
        self.engine.dispose()

