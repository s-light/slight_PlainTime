/******************************************************************************

    some simple time clock formatting helpers..

    written by stefan krueger (s-light),
        github@s-light.eu, http://s-light.eu, https://github.com/s-light/

******************************************************************************/
/******************************************************************************
The MIT License (MIT)

Copyright (c) 2024 Stefan Krüger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#ifndef slight_PlainTime_H_
#define slight_PlainTime_H_

// include Core Arduino functionality
#include "Print.h"
#include "WString.h"
#include <Arduino.h>

class slight_PlainTime {
    int32_t time_sec;

    // buffer for formatting
    // 55555:59:59.999
    static const uint8_t BUFFER_LENGTH = 16;
    char buffer[BUFFER_LENGTH];

public:
    const uint32_t factorHours = (60 * 60);
    const uint32_t factorMinutes = (60);
    const uint32_t factorSeconds = (1);

    slight_PlainTime() { setTimeAsSeconds(0); }
    slight_PlainTime(int32_t time_sec_) { setTimeAsSeconds(time_sec_); }
    slight_PlainTime(int32_t hours, uint8_t minutes, uint8_t seconds) {
        addHours(hours);
        addMinutes(minutes);
        addSeconds(seconds);
    }

    void setTimeAsSeconds(int32_t time_sec_) { time_sec = time_sec_; }
    int32_t getTimeAsSeconds() { return time_sec; }
    // void setTimeAsMilliseconds(int32_t time_ms_) { time_ms = time_ms_; }
    // int32_t getTimeAsMilliseconds() { return time_ms; }

    // void setTime(int32_t hours, uint16_t minutes, uint32_t seconds, uint16_t milliseconds) {
    void setTime(int32_t hours, uint16_t minutes, uint32_t seconds) {
        time_sec = 0;
        addHours(hours);
        addMinutes(minutes);
        addSeconds(seconds);
        // addMilliseconds(milliseconds);
    }

    // uint8_t getMilliseconds() { return (int32_t(time_ms / uint16_t(1)) % 1000); }
    // uint8_t getSeconds() { return (int32_t(time_ms / uint16_t(1000)) % 60); }
    // uint8_t getMinutes() { return (int32_t(time_ms / uint16_t(1000*60)) % 60); }
    // int32_t getHours() { return (time_ms / uint16_t(1000*60 * 60)); }
    uint8_t getSeconds() { return (int32_t(time_sec / uint16_t(1)) % 60); }
    uint8_t getMinutes() { return (int32_t(time_sec / uint16_t(60)) % 60); }
    int32_t getHours() { return (time_sec / uint16_t(60 * 60)); }
    // int32_t getHours() {
    //     return (time_sec / factorHours);
    //     // allow for negative hours
    //     // if (time_sec < 0) {
    //     //     return (time_sec / (1000 * 60 * 60)) - (1000 * 60 * 60);
    //     // } else {
    //     //     return (time_sec / (1000 * 60 * 60));
    //     // }
    // }

    slight_PlainTime &addHours(int32_t hours) {
        time_sec += int32_t(int32_t(hours) * factorHours);
        return *this;
    }
    slight_PlainTime &addMinutes(uint16_t minutes) {
        time_sec += int32_t((minutes)*factorMinutes);
        return *this;
    }
    slight_PlainTime &addSeconds(uint32_t seconds) {
        time_sec += int32_t((seconds)*factorSeconds);
        return *this;
    }
    // slight_PlainTime &addMilliseconds(uint32_t milliseconds) {
    //     time_sec += int32_t((milliseconds)*factorMilliseconds);
    //     return *this;
    // }

    String format() {
        // https://cplusplus.com/reference/cstdio/snprintf/
        // https://cplusplus.com/reference/cstdio/printf/
        snprintf(buffer, BUFFER_LENGTH, "%02d:%02d:%02d", int16_t(getHours()),
                 uint8_t(getMinutes()), uint8_t(getSeconds()));
        return String(buffer);
    }
    void print(Stream &out) { out.print(format()); }

    String formatHM() {
        const uint8_t BUFFER_LENGTH = 12;
        char buffer[BUFFER_LENGTH];
        snprintf(buffer, BUFFER_LENGTH, "%02d:%02d", int16_t(getHours()),
                 uint8_t(getMinutes()), uint8_t(getSeconds()));
        return String(buffer);
    }
    void printHM(Stream &out) { out.print(formatHM()); }

    // String formatHMSM() {
    //     // https://cplusplus.com/reference/cstdio/snprintf/
    //     // https://cplusplus.com/reference/cstdio/printf/
    //     snprintf(buffer, BUFFER_LENGTH, "%02d:%02d:%02d.%03d",
    //              int16_t(getHours()), uint8_t(getMinutes()),
    //              uint8_t(getSeconds()), int16_t(getMilliseconds()));
    //     return String(buffer);
    // }
    // void printHMSM(Stream &out) { out.print(formatHMSM()); }

    friend slight_PlainTime operator+(const slight_PlainTime &obj1,
                                      const slight_PlainTime &obj2) {
        slight_PlainTime temp;
        temp.time_sec = obj1.time_sec + obj2.time_sec;
        return temp;
    }
    friend slight_PlainTime operator-(const slight_PlainTime &obj1,
                                      const slight_PlainTime &obj2) {
        slight_PlainTime temp;
        temp.time_sec = obj1.time_sec - obj2.time_sec;
        return temp;
    }

    // compound assignment
    slight_PlainTime &operator+=(const slight_PlainTime &rhs) {
        // (does not need to be a member, but often is, to modify the private
        // members)
        time_sec += rhs.time_sec;
        return *this; // return the result by reference
    }
    slight_PlainTime &operator-=(const slight_PlainTime &rhs) {
        time_sec -= rhs.time_sec;
        return *this;
    }

    // https://en.cppreference.com/w/cpp/language/operators#Comparison_operators
    friend bool operator<(const slight_PlainTime &lhs,
                          const slight_PlainTime &rhs) {
        return lhs.time_sec < rhs.time_sec;
    }
    friend bool operator>(const slight_PlainTime &lhs,
                          const slight_PlainTime &rhs) {
        return rhs < lhs;
    }
    friend bool operator<=(const slight_PlainTime &lhs,
                           const slight_PlainTime &rhs) {
        return !(lhs > rhs);
    }
    friend bool operator>=(const slight_PlainTime &lhs,
                           const slight_PlainTime &rhs) {
        return !(lhs < rhs);
    }
    friend bool operator==(const slight_PlainTime &lhs,
                           const slight_PlainTime &rhs) {
        return lhs.time_sec == rhs.time_sec;
    }
    friend bool operator!=(const slight_PlainTime &lhs,
                           const slight_PlainTime &rhs) {
        return !(lhs == rhs);
    }
};

#endif // slight_PlainTime_H_
