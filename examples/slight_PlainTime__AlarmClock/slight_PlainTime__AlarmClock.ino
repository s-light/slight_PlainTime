/******************************************

    slight_PlainTime__AlarmClock.ino
        minimal example for library usage.
        debugport: serial interface 115200baud

    hardware:
        Arduino board of any type.

    libraries used:
        ~ slight_PlainTime

    written by stefan krueger (s-light),
        git@s-light.eu, http://s-light.eu, https://github.com/s-light/

    This Example Sketch is released as CC0
******************************************/

#include <slight_PlainTime.h>

slight_PlainTime currentTime = slight_PlainTime(millis());

// hours minutes seconds
slight_PlainTime alarm = slight_PlainTime(0, 0, 13);

uint32_t updateLast = 0;
const uint32_t updateInterval = 1000;

void setup() {
    delay(1000);
    Serial.begin(115200);
    delay(500);
    Serial.println();
    Serial.println(F("slight_PlainTime__AlarmClock.ino sketch."));
    Serial.println(F("simple alarm clock."));
}

void loop() {
    currentTime.setTime(millis());

    if (millis() > updateLast + updateInterval) {
        updateLast = millis();

        currentTime.print(Serial);
        Serial.print("   alarm: ");
        alarm.print(Serial);
        Serial.println();
    }

    if (currentTime >= alarm) {
        Serial.println("\n PING \n");
        alarm.addMinutes(10);
    }
}
