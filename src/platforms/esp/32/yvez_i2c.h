#pragma once

#include <stdint.h>

#include "fixed_vector.h"
#include "crgb.h"

#include "namespace.h"

FASTLED_NAMESPACE_BEGIN

class YvezI2C
{
public:

    typedef FixedVector<uint8_t, 6> Pins;
    static Pins DefaultPins() {
    #ifdef CONFIG_IDF_TARGET_ESP32S3
      uint8_t pins[6] = {9, 10,12,8,18,17};
    #else
      uint8_t pins[6] = {14, 12, 13, 25, 33, 32};
    #endif
      return Pins(pins);
    }
 
    YvezI2C(const YvezI2C &) = delete;
    YvezI2C(CRGB* leds, int clock_pin, int latch_pin, const Pins& pins = DefaultPins());  // FastLED bit timings. See embedded python script in chipsets.h for how to calculate these.

    ~YvezI2C();
    void showPixels();
    void waitForDrawComplete();

    // Disable copy constructor and assignment operator
    YvezI2C() = delete;
    YvezI2C(YvezI2C &&) = delete;
    YvezI2C &operator=(const YvezI2C &) = delete;

private:
};


FASTLED_NAMESPACE_END


