/******************************************

    slight_SimpleTime__basic.ino
        minimal example for library usage.
        debugport: serial interface 115200baud

    hardware:
        Arduino board of any type.

    libraries used:
        ~ slight_SimpleTime

    written by stefan krueger (s-light),
        git@s-light.eu, http://s-light.eu, https://github.com/s-light/

    This Example Sketch is released as CC0
******************************************/

#include <slight_SimpleTime.h>

// simpletime

void setup() {
    delay(1000);
    Serial.begin(115200);
    delay(500);
    Serial.println();
    Serial.println(F("slight_SimpleTime__basic.ino sketch."));
    Serial.println(F("minimal example for library usage."));
}

void loop() {
    // TODO: write example..
}
