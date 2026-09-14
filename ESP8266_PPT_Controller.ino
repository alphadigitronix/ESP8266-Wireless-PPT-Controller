#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ===============================
// Wi-Fi
// ===============================

const char* AP_SSID = "WIFI NAME";
const char* AP_PASSWORD = "PASSWORD";

// ===============================
// Web Server
// ===============================

ESP8266WebServer server(80);

// ===============================
// Push Buttons
// ===============================

#define NEXT_BUTTON D1
#define PREVIOUS_BUTTON D2

// ===============================
// Command
// ===============================

String command = "NONE";

// ===============================
// Home Page
// ===============================

void handleRoot()
{
  String html = "";

  html += "<html>";
  html += "<head><title>ESP8266 PPT Controller</title></head>";
  html += "<body>";
  html += "<h1>ESP8266 PPT Controller</h1>";
  html += "<h2>Last Command: ";
  html += command;
  html += "</h2>";
  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

// ===============================
// Command URL
// ===============================

void handleCommand()
{
  server.send(200, "text/plain", command);

  // Clear command after sending
  command = "NONE";
}

// ===============================
// Setup
// ===============================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  // Buttons
  pinMode(NEXT_BUTTON, INPUT_PULLUP);
  pinMode(PREVIOUS_BUTTON, INPUT_PULLUP);

  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP8266 PPT CONTROLLER");
  Serial.println("==============================");

  // Connect to Airtel Wi-Fi
  WiFi.mode(WIFI_STA);

  WiFi.begin(AP_SSID, AP_PASSWORD);

  Serial.println("Connecting to Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi Connected!");

  Serial.print("Wi-Fi: ");
  Serial.println(AP_SSID);

  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());

  // Web server
  server.on("/", handleRoot);
  server.on("/command", handleCommand);

  server.begin();

  Serial.println("Web server started!");
  Serial.println("==============================");
}

// ===============================
// Loop
// ===============================

void loop()
{
  server.handleClient();

  // -----------------------------
  // NEXT BUTTON - D1
  // -----------------------------

  if (digitalRead(NEXT_BUTTON) == LOW)
  {
    command = "NEXT";

    Serial.println("NEXT BUTTON PRESSED");

    // Wait for release
    while (digitalRead(NEXT_BUTTON) == LOW)
    {
      server.handleClient();
      delay(10);
    }

    delay(100);
  }

  // -----------------------------
  // PREVIOUS BUTTON - D2
  // -----------------------------

  if (digitalRead(PREVIOUS_BUTTON) == LOW)
  {
    command = "PREVIOUS";

    Serial.println("PREVIOUS BUTTON PRESSED");

    // Wait for release
    while (digitalRead(PREVIOUS_BUTTON) == LOW)
    {
      server.handleClient();
      delay(10);
    }

    delay(100);
  }
}