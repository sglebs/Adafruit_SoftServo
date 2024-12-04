// This is an ultra simple software servo driver. For best
// results, use with a timer0 interrupt to refresh() all
// your servos once every 20 milliseconds!
// Written by Limor Fried for Adafruit Industries, BSD license

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
/**
 * @brief Class for basic software servo control
 *
 */
class Adafruit_SoftServo {
public:
  Adafruit_SoftServo(void);
  void attach(uint8_t pin);
  void detach();
  boolean attached();
  void write(uint16_t a);
  void refresh(void);
  uint16_t get_angle(void);
  void set_max_angle(uint16_t a);

private:
  boolean isAttached;
  uint8_t servoPin;
  uint16_t angle; // newer motors can go to 360
  uint16_t max_angle; // newer motors can go to 360
  uint16_t micros;
};
