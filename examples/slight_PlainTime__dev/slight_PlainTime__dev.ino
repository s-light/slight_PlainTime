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
slight_PlainTime alarm = slight_PlainTime(0, 0, 13);

uint32_t updateLast = 0;
const uint32_t updateInterval = 1000;

void setup() {
    delay(1000);
    Serial.begin(115200);
    delay(200);
    Serial.println("\n\n\n\n\n");
    Serial.println(F("slight_PlainTime__AlarmClock.ino sketch."));
    Serial.println(F("simple alarm clock."));
    delay(200);

    // Serial.println();
    // currentTime.print(Serial);
    // Serial.println();

    // Serial.print("factorHours: ");
    // Serial.println(currentTime.factorHours);
    // Serial.print("factorMinutes: ");
    // Serial.println(currentTime.factorMinutes);
    // Serial.print("factorSeconds: ");
    // Serial.println(currentTime.factorSeconds);

    // Serial.println("setTime(0)");
    // currentTime.setTime(0);
    // Serial.print("currentTime.print():   ");
    // currentTime.print(Serial);
    // Serial.println();

    // Serial.println("\n\n\n");

    // Serial.println("addSeconds(12)");
    // currentTime.addSeconds(12);
    // Serial.print("currentTime.getTime(): ");
    // Serial.println(currentTime.getTime());

    // Serial.println("addSeconds(18)");
    // currentTime.addSeconds(18);
    // Serial.print("currentTime.getTime(): ");
    // Serial.println(currentTime.getTime());

    // Serial.println("addSeconds(60)");
    // currentTime.addSeconds(60);
    // Serial.print("currentTime.getTime(): ");
    // Serial.println(currentTime.getTime());

    // Serial.println("addSeconds(300)");
    // currentTime.addSeconds(300);
    // Serial.print("currentTime.getTime(): ");
    // Serial.println(currentTime.getTime());

    // Serial.println("addMinutes(1)");
    // currentTime.addMinutes(1);
    // Serial.print("currentTime.getTime(): ");
    // Serial.println(currentTime.getTime());

    // Serial.println("addMinutes(5)");
    // currentTime.addMinutes(5);
    // Serial.print("currentTime.getTime(): ");
    // Serial.println(currentTime.getTime());

    // Serial.println("addMinutes(5)");
    // currentTime.addMinutes(5);
    // Serial.print("currentTime.getTime(): ");
    // Serial.println(currentTime.getTime());

    // Serial.println("addHours(5)");
    // currentTime.addHours(5);
    // Serial.print("currentTime.getTime(): ");
    // Serial.println(currentTime.getTime());

    // Serial.println("\n\n\n");

    Serial.println("\n 14sec");
    currentTime.setTimeAsSeconds(0);
    currentTime.addSeconds(14);

    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTimeAsSeconds());

    Serial.print("currentTime.print():   ");
    currentTime.print(Serial);
    Serial.println();

    Serial.println();
    Serial.println("7min + 14sec");
    currentTime.setTime(0,7,14);
    Serial.print("currentTime.print():   ");
    currentTime.print(Serial);
    Serial.println();

    Serial.println();
    Serial.println("13h + 7min + 14sec");
    currentTime.setTime(13, 7, 14);
    // currentTime.setTimeAsSeconds(0);
    // currentTime.addHours(13);
    // currentTime.addMinutes(7);
    // currentTime.addSeconds(14);
    Serial.print("currentTime.print():   ");
    currentTime.print(Serial);
    Serial.println();

    delay(1000);
}

void loop() {

    if (millis() > updateLast + updateInterval) {
        updateLast = millis();
        currentTime.addSeconds(1);
        currentTime.print(Serial);
        Serial.println();
    }

    // if (currentTime >= alarm) {
    //     Serial.println("\n PING \n");
    //     alarm.addMinutes(20);
    // }
}
