import os
import requests
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry
from dotenv import load_dotenv

# Lade Umgebungsvariablen aus der .env-Datei
load_dotenv()


class HttpConnection:
    """
       Manages HTTP connections using the `requests` library with automatic retry and backoff.

       :param base_url: The base URL for the HTTP requests. Defaults to the environment variable 'HTTP_URL'.
       :type base_url: str, optional
       :param retries: The number of retry attempts in case of failed requests. Defaults to 3.
       :type retries: int, optional
       :param backoff_factor: A backoff factor to apply between retries. Defaults to 1.0.
       :type backoff_factor: float, optional
       :param pool_size: The maximum number of connections to keep open in the connection pool. Defaults to 10.
       :type pool_size: int, optional
       """

    def __init__(self, base_url: str = None, retries: int = 3, backoff_factor: float = 1.0, pool_size: int = 10):
        """
        Initializes the HTTP connection, setting up the base URL and retry settings.

        :param base_url: The base URL for the HTTP requests. Defaults to the environment variable 'HTTP_URL'.
        :type base_url: str, optional
        :param retries: The number of retry attempts in case of failed requests. Defaults to 3.
        :type retries: int, optional
        :param backoff_factor: A backoff factor to apply between retries. Defaults to 1.0.
        :type backoff_factor: float, optional
        :param pool_size: The maximum number of connections to keep open in the connection pool. Defaults to 10.
        :type pool_size: int, optional
        """
        # Falls keine base_url übergeben wird, hole sie aus der Umgebungsvariablen
        self.base_url = base_url or os.getenv('HTTP_URL')

        # HTTP Session mit Pooling und Retry-Logik erstellen
        self.session = requests.Session()

        # Retry-Logik definieren
        retry = Retry(
            total=retries,
            backoff_factor=backoff_factor,
            status_forcelist=[500, 502, 503, 504]  # Retry auf diese HTTP Status Codes
        )

        # Mount den Adapter auf die Session für HTTP und HTTPS
        adapter = HTTPAdapter(pool_connections=pool_size, max_retries=retry)
        self.session.mount("http://", adapter)
        self.session.mount("https://", adapter)

    def fetch_data(self, endpoint: str = "data", params: dict = None):
        """
        Fetches data from the specified endpoint using a GET request.

        :param endpoint: The endpoint to query. Defaults to 'data'.
        :type endpoint: str, optional
        :param params: Optional query parameters to include in the GET request.
        :type params: dict, optional
        :return: The response content as text, or None if the request failed.
        :rtype: str or None
        """
        try:
            response = self.session.get(f"{self.base_url}/{endpoint}", params=params)
            response.raise_for_status()  # Fehler bei schlechten HTTP Status Codes
            return response.text
        except requests.RequestException as e:
            print(f"HTTP request failed: {e}")
            return None

    def close(self):
        """
        Closes the HTTP session to release resources.

        :return: None
        """
        self.session.close()