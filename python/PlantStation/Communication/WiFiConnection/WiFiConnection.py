# import requests
#
# class WiFiConnection:
#     def __init__(self, url):
#         self._url = url
#
#     def fetch_data(self):
#         try:
#             response = requests.get(self._url)
#             if response.status_code == 200:
#                 print("Data received from D1 mini:", response.text)
#                 return response.text
#             else:
#                 print("Failed to retrieve data, status code:", response.status_code)
#         except Exception as e:
#             print("Error:", e)


import os
import requests
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry
from dotenv import load_dotenv

# Lade Umgebungsvariablen aus der .env-Datei
load_dotenv()


class HttpConnection:
    def __init__(self, base_url: str = None, retries: int = 3, backoff_factor: float = 1.0, pool_size: int = 10):
        """
        Initialize the HTTP connection with connection pooling and retries.

        :param base_url: Base URL for the HTTP API (e.g., 'https://api.example.com')
        :param retries: Number of retries for failed requests (default: 3)
        :param backoff_factor: Time to wait between retries (default: 1.0 seconds)
        :param pool_size: Max number of connections in the pool (default: 10)
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
        Fetch data from the API with a GET request.

        :param endpoint: API endpoint (e.g., 'data')
        :param params: Optional query parameters for the request
        :return: Response data as JSON or None if failed
        """
        try:
            response = self.session.get(f"{self.base_url}/{endpoint}", params=params)
            response.raise_for_status()  # Fehler bei schlechten HTTP Status Codes
            return response.text
        except requests.RequestException as e:
            print(f"HTTP request failed: {e}")
            return None

    def close(self):
        """Close the HTTP session properly to release the connection pool."""
        self.session.close()