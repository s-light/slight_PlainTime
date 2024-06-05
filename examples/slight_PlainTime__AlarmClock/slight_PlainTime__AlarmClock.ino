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
const uint32_t updateInterval = 10000;

void setup() {
    delay(1000);
    Serial.begin(115200);
    delay(200);
    Serial.println("\n\n\n\n\n");
    Serial.println(F("slight_PlainTime__AlarmClock.ino sketch."));
    Serial.println(F("simple alarm clock."));
    delay(200);

    Serial.println();
    currentTime.print(Serial);
    Serial.println();
    
    Serial.print("factorHours: ");
    Serial.println(currentTime.factorHours);
    Serial.print("factorMinutes: ");
    Serial.println(currentTime.factorMinutes);
    Serial.print("factorSeconds: ");
    Serial.println(currentTime.factorSeconds);

    Serial.println("setTime(0)");
    currentTime.setTime(0);
    Serial.print("currentTime.print():   ");
    currentTime.print(Serial);
    Serial.println();

    Serial.println("\n\n\n");

    Serial.println("addSeconds(42)");
    currentTime.addSeconds(42);
    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTime());
    
    Serial.println("addSeconds(60)");
    currentTime.addSeconds(60);
    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTime());
    
    Serial.println("addSeconds(60)");
    currentTime.addSeconds(60);
    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTime());
    
    Serial.println("addSeconds(60)");
    currentTime.addSeconds(300);
    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTime());
    
    
    Serial.println("addMinutes(1)");
    currentTime.addMinutes(1);
    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTime());
    
    Serial.println("addMinutes(5)");
    currentTime.addMinutes(5);
    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTime());


    Serial.println("\n\n\n");





    Serial.println("setTime(14sec)");
    // currentTime.addSeconds(14);
    currentTime.setTime(14 * 1000);

    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTime());

    Serial.print("currentTime.print():   ");
    currentTime.print(Serial);
    Serial.println();

    Serial.println("setTime(14sec + 7min)");
    // currentTime.addSeconds(14);
    currentTime.setTime(uint32_t(14 * uint32_t(1000)) +
                        uint32_t(7 * 60 * uint32_t(1000)));

    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTime());

    Serial.print("currentTime.print():   ");
    currentTime.print(Serial);
    Serial.println();

    Serial.print("currentTime.get*:      ");
    Serial.print(currentTime.getHours());
    Serial.print(":");
    Serial.print(currentTime.getMinutes());
    Serial.print(":");
    Serial.print(currentTime.getSeconds());
    Serial.println();

    Serial.println("setTime(14sec + 7min + 13h)");
    // currentTime.addSeconds(14);
    currentTime.setTime(uint32_t(14 * uint32_t(1000)) +
                        uint32_t(7 * 60 * uint32_t(1000)) +
                        uint32_t(13 * 60 * 60 * uint32_t(1000)));

    Serial.print("currentTime.getTime(): ");
    Serial.println(currentTime.getTime());

    Serial.print("currentTime.print():   ");
    currentTime.print(Serial);
    Serial.println();

    Serial.print("currentTime.get*:      ");
    Serial.print(currentTime.getHours());
    Serial.print(":");
    Serial.print(currentTime.getMinutes());
    Serial.print(":");
    Serial.print(currentTime.getSeconds());
    Serial.println();

    delay(1000);
}

void loop() {

    if (millis() > updateLast + updateInterval) {
        updateLast = millis();
        currentTime.addMinutes(1);

        // currentTime.print(Serial);
        // Serial.print("   alarm: ");
        // alarm.print(Serial);
        Serial.print(currentTime.getHours());
        Serial.print(":");
        Serial.print(currentTime.getMinutes());
        Serial.print(":");
        Serial.print(currentTime.getSeconds());
        Serial.println();
    }

    // if (currentTime >= alarm) {
    //     Serial.println("\n PING \n");
    //     alarm.addMinutes(20);
    // }
}
