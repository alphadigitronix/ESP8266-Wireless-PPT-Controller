import requests
import time

ESP8266_IP = "192.168.1.14"
URL = "http://" + ESP8266_IP + "/command"

print("================================")
print("ESP8266 BUTTON TEST")
print("================================")
print()
print("ESP8266 IP:", ESP8266_IP)
print("Waiting for button presses...")
print()
print("D1 = NEXT")
print("D2 = PREVIOUS")
print()

while True:
    try:
        response = requests.get(URL, timeout=1)

        command = response.text.strip()

        if command == "NEXT":
            print("BUTTON: NEXT")

        elif command == "PREVIOUS":
            print("BUTTON: PREVIOUS")

    except requests.exceptions.RequestException:
        print("ESP8266 connection error")

    time.sleep(0.05)