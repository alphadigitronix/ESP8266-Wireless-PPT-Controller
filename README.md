# ESP8266 Wireless PPT Controller

A wireless PowerPoint presentation controller built using an **ESP8266 NodeMCU**, push buttons, and a Python application.

The ESP8266 connects to the same Wi-Fi network as the laptop and sends button commands through a simple HTTP web server. The Python program receives these commands and controls PowerPoint using PyAutoGUI.

---

## Features

* Wireless PowerPoint slide control
* ESP8266-based controller
* NEXT slide button
* PREVIOUS slide button
* Wi-Fi communication
* Python-based desktop controller
* HTTP communication between ESP8266 and laptop
* No Bluetooth required
* Simple and low-cost hardware

---

## Project Architecture

```text
        Push Buttons
             │
             ▼
       ┌────────────┐
       │  ESP8266   │
       │  NodeMCU   │
       └─────┬──────┘
             │
             │ Wi-Fi
             ▼
       ┌────────────┐
       │  Python    │
       │ Controller │
       └─────┬──────┘
             │
             │ PyAutoGUI
             ▼
       ┌────────────┐
       │ PowerPoint │
       └────────────┘
```

---

## Hardware Requirements

| Component       |    Quantity |
| --------------- | ----------: |
| ESP8266 NodeMCU |           1 |
| Push Button     |           2 |
| Jumper Wires    | As required |
| Breadboard      |           1 |
| USB Cable       |           1 |
| Laptop/PC       |           1 |

---

## Pin Configuration

| Function      | ESP8266 Pin |
| ------------- | ----------- |
| NEXT          | D1          |
| PREVIOUS      | D2          |
| Button Ground | GND         |

The buttons use the ESP8266 internal pull-up resistors.

```cpp
pinMode(NEXT_BUTTON, INPUT_PULLUP);
pinMode(PREVIOUS_BUTTON, INPUT_PULLUP);
```

Therefore, external pull-up resistors are not required.

---

## Software Requirements

### ESP8266

Install:

* Arduino IDE
* ESP8266 Board Package

### Python

Python 3.x is recommended.

Required Python libraries:

```text
requests
pyautogui
```

Install them using:

```bash
pip install -r requirements.txt
```

Or:

```bash
pip install requests pyautogui
```

---

## Project Structure

```text
ESP8266-Wireless-PPT-Controller/
│
├── ESP8266_PPT_Controller/
│   └── ESP8266_PPT_Controller.ino
│
├── Python_Controller/
│   └── ppt_controller.py
│
├── README.md
└── requirements.txt
```

---

# ESP8266 Setup

## 1. Install ESP8266 Board Package

Open Arduino IDE.

Go to:

```text
File → Preferences
```

Add the following URL to:

```text
Additional Boards Manager URLs
```

```text
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```

Then go to:

```text
Tools → Board → Boards Manager
```

Search for:

```text
ESP8266
```

Install:

```text
esp8266 by ESP8266 Community
```

---

## 2. Select Board

Connect the ESP8266 to your computer.

Select:

```text
Tools → Board → ESP8266 Boards → NodeMCU 1.0 (ESP-12E Module)
```

Then select the correct COM port.

---

## 3. Wi-Fi Configuration

Inside the Arduino code, configure your Wi-Fi:

```cpp
const char* AP_SSID = "YOUR_WIFI_NAME";
const char* AP_PASSWORD = "YOUR_WIFI_PASSWORD";
```

Replace these values with the Wi-Fi network used by your laptop.

**Important:** Do not publish your real Wi-Fi password in a public GitHub repository.

---

## 4. Upload the Code

Open:

```text
ESP8266_PPT_Controller/ESP8266_PPT_Controller.ino
```

Click:

```text
Verify
```

Then:

```text
Upload
```

Open the Serial Monitor at:

```text
115200 baud
```

You should see:

```text
ESP8266 PPT CONTROLLER
Connecting to Wi-Fi...
............

Wi-Fi Connected!

ESP8266 IP Address: 192.168.1.XX

Web server started!
```

Write down the ESP8266 IP address.

---

# Testing the ESP8266

Open a browser on the laptop.

Enter:

```text
http://ESP8266_IP/
```

For example:

```text
http://192.168.1.14/
```

The ESP8266 web page should appear.

---

## Test NEXT

Press the D1 button.

Then open:

```text
http://192.168.1.14/command
```

Expected result:

```text
NEXT
```

---

## Test PREVIOUS

Press the D2 button.

Open:

```text
http://192.168.1.14/command
```

Expected result:

```text
PREVIOUS
```

---

# Python Controller Setup

Open:

```text
Python_Controller/ppt_controller.py
```

Set the ESP8266 IP address:

```python
ESP8266_IP = "192.168.1.14"
```

Replace it with the IP address displayed by your ESP8266.

---

## Install Dependencies

Open Command Prompt or Terminal.

Navigate to the project folder and run:

```bash
pip install -r requirements.txt
```

---

## Run the Controller

Navigate to:

```text
Python_Controller
```

Run:

```bash
python ppt_controller.py
```

Expected output:

```text
================================
ESP8266 WIRELESS PPT CONTROLLER
================================

ESP8266 IP: 192.168.1.14

D1 = NEXT SLIDE
D2 = PREVIOUS SLIDE

Waiting for button presses...
```

---

# Using the Controller

1. Connect ESP8266 to the Wi-Fi network.
2. Start the Python controller.
3. Open your PowerPoint presentation.
4. Start Slide Show.
5. Press D1 to move to the next slide.
6. Press D2 to move to the previous slide.

### Controls

| Button | Function       |
| ------ | -------------- |
| D1     | Next Slide     |
| D2     | Previous Slide |

---

# How It Works

When the D1 button is pressed:

```text
D1
 ↓
ESP8266 detects button
 ↓
command = "NEXT"
 ↓
Python requests /command
 ↓
ESP8266 returns "NEXT"
 ↓
PyAutoGUI presses RIGHT
 ↓
PowerPoint moves to next slide
```

When D2 is pressed:

```text
D2
 ↓
ESP8266 detects button
 ↓
command = "PREVIOUS"
 ↓
Python requests /command
 ↓
ESP8266 returns "PREVIOUS"
 ↓
PyAutoGUI presses LEFT
 ↓
PowerPoint moves to previous slide
```

---

# Troubleshooting

## ESP8266 does not connect to Wi-Fi

Check:

* Wi-Fi name
* Wi-Fi password
* ESP8266 power supply
* Wi-Fi signal
* Laptop and ESP8266 are connected to the same network

---

## Python shows connection error

Check the IP address printed by the ESP8266.

Update:

```python
ESP8266_IP = "YOUR_ESP8266_IP"
```

Also make sure the laptop and ESP8266 are on the same local network.

---

## Buttons do not work

Check:

```text
D1 → NEXT button
D2 → PREVIOUS button
Button → GND
```

The code uses:

```cpp
INPUT_PULLUP
```

Therefore, the button should connect the GPIO pin to **GND when pressed**.

---

## PowerPoint does not change slides

Make sure the PowerPoint slideshow is the active window.

The Python program uses:

```python
pyautogui.press("right")
```

for next slide and:

```python
pyautogui.press("left")
```

for previous slide.

---

# Security Note

The ESP8266 web server does not use authentication.

Anyone who can access the ESP8266 on the same network may potentially access its HTTP endpoints.

This project is intended primarily for demonstrations, classrooms, labs, and local networks.

Do not expose the ESP8266 web server directly to the public internet.

---

# Future Improvements

Possible upgrades include:

* OLED display
* Battery-powered controller
* ESP8266 onboard LED status
* Automatic Wi-Fi reconnect
* Automatic IP discovery
* Presentation start/stop button
* Black screen control
* Laser pointer control
* Slide number display
* Web-based controller
* ESP32 version
* Rechargeable battery
* 3D-printed enclosure
* PowerPoint remote with multiple functions

---

# Technologies Used

* ESP8266
* Arduino IDE
* C/C++
* Wi-Fi
* HTTP
* Python
* Requests
* PyAutoGUI
* Microsoft PowerPoint

---

# Author

**Alpha Digitronix**

ESP8266 Wireless PPT Controller

---

## License

This project can be used for educational and personal purposes.
