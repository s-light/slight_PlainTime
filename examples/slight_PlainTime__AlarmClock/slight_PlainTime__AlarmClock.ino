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

slight_PlainTime currentTime = slight_PlainTime(0);

// hours minutes seconds
slight_PlainTime alarm = slight_PlainTime(0);

uint32_t updateLast = 0;
const uint32_t updateInterval = 100;

void setup() {
    delay(1000);
    Serial.begin(115200);
    delay(200);
    Serial.println("\n\n\n\n\n");
    Serial.println(F("slight_PlainTime__AlarmClock.ino sketch."));
    Serial.println(F("simple alarm clock."));
    delay(200);
    
    Serial.print(F("set alarm to "));
    alarm.setTime(0,2,5);
    alarm.print(Serial);

    delay(200);
}

void loop() {

    if (millis() > updateLast + updateInterval) {
        updateLast = millis();
        currentTime.addSeconds(1);

        currentTime.print(Serial);
        Serial.print("         alarm: ");
        alarm.print(Serial);
        Serial.println();
    }

    if (currentTime >= alarm) {
        Serial.println("\n PING \n");
        alarm.addMinutes(10);
    }
}
