import os
import logging

from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.exc import SQLAlchemyError
from sqlalchemy.pool import QueuePool
from dotenv import load_dotenv

load_dotenv()


class PostgresConnection:
    def __init__(self, db_url: str = None, pool_size: int = 5, max_overflow: int = 10):
        """
        Initialize the PostgreSQL connection with pooling support.

        :param db_url: Database connection URL (optional, can be passed or fetched from environment variable)
        :param pool_size: Number of connections to keep in the pool (default: 5)
        :param max_overflow: Number of connections to allow beyond pool_size (default: 10)
        """
        self.db_url = db_url or os.getenv('DATABASE_URL_AWS')

        self.engine = create_engine(
            self.db_url,
            poolclass=QueuePool,
            pool_size=pool_size,
            max_overflow=max_overflow,
            echo=False
        )

        self.Session = sessionmaker(bind=self.engine)

    def __enter__(self):
        """Beendet den 'with'-Block und gibt eine Session zurück."""
        try:
            self.session = self.Session()
            logging.info("Session created successfully.")
            return self.session
        except SQLAlchemyError as e:
            logging.error(f"Error creating session: {e}")
            raise

    def get_session(self):
        """Returns a new session from the pool."""
        try:
            session = self.Session()
            return session
        except SQLAlchemyError as e:
            print(f"Error creating session: {e}")
            return None

    def _get_engine(self):
        """Gibt die Engine zurück, falls benötigt."""
        return self.engine

    def close(self):
        """Properly closes the connection pool."""
        self.engine.dispose()

    def __exit__(self, exc_type, exc_value, traceback):
        try:
            if hasattr(self, 'session'):
                self.session.close()
            self.engine.dispose()
            logging.info("Connection pool disposed and session closed.")
        except SQLAlchemyError as e:
            logging.error(f"Error disposing the connection pool: {e}")
            raise