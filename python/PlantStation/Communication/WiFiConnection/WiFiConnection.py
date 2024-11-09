import requests

class WiFiConnection:
    def __init__(self, url):
        self._url = url

    def fetch_data(self):
        try:
            response = requests.get(self._url)
            if response.status_code == 200:
                print("Data received from D1 mini:", response.text)
                return response.text
            else:
                print("Failed to retrieve data, status code:", response.status_code)
        except Exception as e:
            print("Error:", e)
