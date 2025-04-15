//
// Created by Lucas Watkins on 4/6/25.
//
#include <ESP8266WebServer.h>
#include "config.h"

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

class ConnectionManager {
  public:
    static const ConnectionManager& getInstance();
    //ESP8266WebServer* getServer();
    void connectToWifi() const;
    void handleIncomingConnections() const;
    void initalizeCallbacks() const;
    void send(const char*) const;
    [[nodiscard]] boolean validPasswordSupplied() const;

  private:
    inline static ESP8266WebServer* server {new ESP8266WebServer(80)};
    const char* ssid;
    const char* password;
    ConnectionManager() : ssid {SSID}, password {PASSWORD} {};
};

#endif //CONNECTIONMANAGER_H
