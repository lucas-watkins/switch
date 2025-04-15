#include <Arduino.h>
#include <ConnectionManager.h>
#include "config.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

inline const ConnectionManager& cm {ConnectionManager::getInstance()};

void setup() {
    Serial.begin(9600);
    cm.connectToWifi();

#ifdef TESTKIT
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(GREEN_LED, HIGH);
        delay(3000);
        digitalWrite(GREEN_LED, LOW);
    }
#endif

    Serial.println("IP Address: " + WiFi.localIP().toString());
    Serial.println("MAC Address: " + WiFi.macAddress());

    cm.initalizeCallbacks();
}

void loop() {
    cm.handleIncomingConnections();
}