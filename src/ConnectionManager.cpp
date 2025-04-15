//
// Created by Lucas Watkins on 4/6/25.
//

#include <Arduino.h>
#include "ConnectionManager.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include "config.h"
#include <ESP8266mDNS.h>

inline const ConnectionManager& cm {ConnectionManager::getInstance()};
bool isTargetDeviceActive = false;

extern const ConnectionManager& ConnectionManager::getInstance() {
   	static ConnectionManager instance;
    return instance;
}

extern void ConnectionManager::connectToWifi() const {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

extern void ConnectionManager::handleIncomingConnections() const {
  server->handleClient();
}

extern void ConnectionManager::send(const char* msg) const {
  server->send(200, "text/html", msg);
}

boolean ConnectionManager::validPasswordSupplied() const {
	return server->args() == 2
      && server->argName(0) == "username"
      && server->argName(1) == "password"
      && server->arg(0) == BASESTATION_USERNAME
      && server->arg(1) == BASESTATION_PASSWORD;
}

extern void toggle() {
 if (cm.validPasswordSupplied())
  {
  	if (!isTargetDeviceActive) {
  	  on();
	  } else {
  	  off();
 	 }

  	isTargetDeviceActive = !isTargetDeviceActive;
  	cm.send("toggled");
 }

}

extern void ConnectionManager::initalizeCallbacks() const {
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  server->on("/toggle", toggle);
  server->on("/on", [] {if(!isTargetDeviceActive){ on(); cm.send("on");}});
  server->on("/off", [] {if(isTargetDeviceActive){ off(); cm.send("off");}});
  server->begin();
}