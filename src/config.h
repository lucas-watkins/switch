//
// Created by Lucas Watkins on 4/6/25.
//

#ifndef PINS_H
#define PINS_H

#define TESTKIT

#define RED_LED 16
#define GREEN_LED 5
#define SSID "ssid"
#define PASSWORD "password"
#define BASESTATION_USERNAME "admin123"
#define BASESTATION_PASSWORD "admin123"

// Usage: curl "http://yourIP/toggle?username=admin123&password=admin123"

inline void on() {
    digitalWrite(RED_LED, HIGH);
}

inline void off() {
    digitalWrite(RED_LED, LOW);
}

#endif //PINS_H
