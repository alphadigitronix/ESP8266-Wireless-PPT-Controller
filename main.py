import requests
import pyautogui
import time

# ==========================================
# ESP8266 SETTINGS
# ==========================================

ESP8266_IP = "192.168.1.14"
URL = "http://" + ESP8266_IP + "/command"

# ==========================================
# START
# ==========================================

print("================================")
print("ESP8266 WIRELESS PPT CONTROLLER")
print("================================")
print()
print("ESP8266 IP:", ESP8266_IP)
print()
print("D1 = NEXT SLIDE")
print("D2 = PREVIOUS SLIDE")
print()
print("Waiting for button presses...")
print()

# ==========================================
# MAIN LOOP
# ==========================================

while True:

    try:

        # Get command from ESP8266
        response = requests.get(URL, timeout=1)

        command = response.text.strip()

        # -------------------------------
        # NEXT SLIDE
        # -------------------------------

        if command == "NEXT":

            print("➡ NEXT SLIDE")

            pyautogui.press("right")

        # -------------------------------
        # PREVIOUS SLIDE
        # -------------------------------

        elif command == "PREVIOUS":

            print("⬅ PREVIOUS SLIDE")

            pyautogui.press("left")

    except requests.exceptions.RequestException:

        print("⚠ ESP8266 connection error")

        time.sleep(1)

    except KeyboardInterrupt:

        print()
        print("Controller stopped.")
        break

    # Small delay
    time.sleep(0.05)