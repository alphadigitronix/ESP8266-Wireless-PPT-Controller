import pyautogui
import time

print("Starting in 5 seconds...")
print("Click the PowerPoint slideshow window!")

time.sleep(5)

print("Sending NEXT...")
pyautogui.press("right")

time.sleep(3)

print("Sending NEXT...")
pyautogui.press("right")

time.sleep(3)

print("Sending PREVIOUS...")
pyautogui.press("left")

print("Test finished")