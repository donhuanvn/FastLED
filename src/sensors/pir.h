#pragma once

#include <stdint.h>

#include "digital_pin.h"
#include "fl/ptr.h"
#include "ui.h"

#include "namespace.h"


namespace fl {

// A passive infrared sensor common on amazon.
// Instantiating this class will create a ui Button when
// compiling using the FastLED web compiler.
class Pir {
  public:
    Pir(int pin);
    bool detect();
    operator bool() { return detect(); }

  private:
    Button mButton;
    DigitalPin mPin;
};

// An advanced PIR that incorporates time to allow for latching and transitions fx. This is useful
// for detecting motion and the increasing the brightness in response to motion.
// Example:
//   #define PIR_LATCH_MS 15000  // how long to keep the PIR sensor active after a trigger
//   #define PIR_RISING_TIME 1000  // how long to fade in the PIR sensor
//   #define PIR_FALLING_TIME 1000  // how long to fade out the PIR sensor
//   PirAdvanced pir(PIN_PIR, PIR_LATCH_MS, PIR_RISING_TIME, PIR_FALLING_TIME);
//   void loop() {
//      uint8_t bri = pir.transition(millis());
//      FastLED.setBrightness(bri * brightness.as<float>());
//   }

class PirAdvanced {
  public:
    PirAdvanced(int pin, uint32_t latchMs = 0, uint32_t risingTime = 0, uint32_t fallingTime = 0);
    bool detect(uint32_t now);  // Just detects on and off.
    // When off this will be 0.
    // When on this will be a value between 0 and 255, defined by the transition params
    // risingTime and fallingTime which are passed into the constructor.
    uint8_t transition(uint32_t now);  // Detects on and off and also applies transitions.

    // Activate the PIR sensor. This is useful for starting the PIR sensor on startup.
    void activate(uint32_t now) { mLastTrigger = now; }

  private:
    Pir mPir;
    uint32_t mLatchMs;
    uint32_t mRisingTime;
    uint32_t mFallingTime; 
    uint32_t mLastTrigger;
    bool mLastState;
    uint8_t mLastTransition = 0;
};

} // namespace fl
