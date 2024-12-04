// This is an ultra simple software servo driver. For best
// results, use with a timer0 interrupt to refresh() all
// your servos once every 20 milliseconds!
// Written by Limor Fried for Adafruit Industries, BSD license

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Adafruit_SoftServo.h"
/**
 * @brief Construct a new Adafruit_SoftServo::Adafruit_SoftServo object
 *
 */
Adafruit_SoftServo::Adafruit_SoftServo(void) {
  isAttached = false;
  servoPin = 255;
  angle = 90;
}
/**
 * @brief Attacht to a supplied pin
 *
 * @param pin The pin to attach to for controlling the servo
 */
void Adafruit_SoftServo::attach(uint8_t pin) {
  servoPin = pin;
  angle = 90;
  max_angle = 180;
  isAttached = true;
  pinMode(servoPin, OUTPUT);
}
/**
 * @brief Detach from the supplied pin
 *
 */
void Adafruit_SoftServo::detach(void) {
  isAttached = false;
  pinMode(servoPin, INPUT);
}
/**
 * @brief Get the attachment status of the pin
 *
 * @return boolean true: a pin is attached false: no pin is attached
 */
boolean Adafruit_SoftServo::attached(void) { return isAttached; }
/**
 * @brief Update the servo's angle setting and the corresponding pulse width
 *
 * @param a The target servo angle
 */
void Adafruit_SoftServo::write(uint16_t a) {
  angle = a;

  if (!isAttached)
    return;
  micros = map(a, 0, max_angle, 1000, 2000 * max_angle // 180);  // 2000 was used for 180 max
}

/**
 * @brief Set the max angle this servo can go to. Some new servos go to 360
 *
 * @param a The max supported servo angle (e.g. 180, 360)
 */
void Adafruit_SoftServo::set_max_angle(uint16_t a) {
  max_angle = a;
}


/**
 * @brief Return the currently set angle
 *
 */
uint16_t Adafruit_SoftServo::get_angle(void) {
  return angle;
}

/**
 * @brief Pulse the control pin for the amount of time determined when the angle
 * was set with `write`
 *
 */
void Adafruit_SoftServo::refresh(void) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(micros);
  digitalWrite(servoPin, LOW);
}
