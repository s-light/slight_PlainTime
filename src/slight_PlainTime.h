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
#include <cstdint>

class SimpleTime {
    int32_t time_ms;

public:
    SimpleTime() {}
    SimpleTime(int32_t time_ms_) { setTime(time_ms_); }
    SimpleTime(int32_t hours, uint8_t minutes, uint8_t seconds) {
        addHours(hours);
        addMinutes(minutes);
        addSeconds(seconds);
    }

    void setTime(int32_t time_ms_) { time_ms = time_ms_; }
    int32_t getTime();

    int32_t getHours() {
        // allow for negative hours
        if (time_ms < 0) {
            return (time_ms / (1000 * 60 * 60)) - (1000 * 60 * 60);
        } else {
            return (time_ms / (1000 * 60 * 60));
        }
    }
    uint8_t getMinutes() { return (time_ms % (1000 * 60 * 60) / (1000 * 60)); }
    uint8_t getSeconds() { return (time_ms % (1000 * 60) / 1000); }
    uint16_t getMilliseconds() { return (time_ms % 1000); }

    SimpleTime &addHours(int32_t hours) {
        time_ms += hours * (1000 * 60 * 60);
        return *this;
    }
    SimpleTime &addMinutes(uint8_t minutes) {
        time_ms += minutes * (1000 * 60);
        return *this;
    }
    SimpleTime &addSeconds(uint8_t seconds) {
        time_ms += seconds * (1000);
        return *this;
    }
    slight_PlainTime SimpleTime &addMilliseconds(uint16_t milliseconds) {
        time_ms += milliseconds;
        return *this;
    }

    String format() {
        // https://cplusplus.com/reference/cstdio/snprintf/
        // https://cplusplus.com/reference/cstdio/printf/
        // format hours
        // minutes
        const uint8_t BUFFER_LENGTH = 100;
        char buffer[BUFFER_LENGTH];
        snprintf(buffer, BUFFER_LENGTH, "%02d:%02d:%02d", getHours(),
                 getMinutes(), getSeconds());
        return String(buffer);
    }
    void print(Stream &out) { out.print(format()); }

    friend SimpleTime operator+(const SimpleTime &obj1,
                                const SimpleTime &obj2) {
        SimpleTime temp;
        temp.time_ms = obj1.time_ms + obj2.time_ms;
        return temp;
    }
    friend SimpleTime operator-(const SimpleTime &obj1,
                                const SimpleTime &obj2) {
        SimpleTime temp;
        temp.time_ms = obj1.time_ms - obj2.time_ms;
        return temp;
    }

    // compound assignment
    SimpleTime &operator+=(const SimpleTime &rhs) {
        // (does not need to be a member, but often is, to modify the private
        // members)
        time_ms += rhs.time_ms;
        return *this; // return the result by reference
    }
    SimpleTime &operator-=(const SimpleTime &rhs) {
        time_ms -= rhs.time_ms;
        return *this;
    }

    // https://en.cppreference.com/w/cpp/language/operators#Comparison_operators
    friend bool operator<(const SimpleTime &lhs, const SimpleTime &rhs) {
        return lhs.time_ms < rhs.time_ms;
    }
    friend bool operator>(const SimpleTime &lhs, const SimpleTime &rhs) {
        return rhs < lhs;
    }
    friend bool operator<=(const SimpleTime &lhs, const SimpleTime &rhs) {
        return !(lhs > rhs);
    }
    friend bool operator>=(const SimpleTime &lhs, const SimpleTime &rhs) {
        return !(lhs < rhs);
    }
    friend bool operator==(const SimpleTime &lhs, const SimpleTime &rhs) {
        return lhs.time_ms == rhs.time_ms;
    }
    friend bool operator!=(const SimpleTime &lhs, const SimpleTime &rhs) {
        return !(lhs == rhs);
    }
};

#endif // slight_PlainTime_H_
