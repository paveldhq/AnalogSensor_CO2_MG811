#include "CO2_MG811.h"

#ifndef CO2_MG811_DEBUG
#define CO2_MG811_DEBUG false
#endif

const int co2_b = 600;
const int co2_d = 400;

namespace AnalogSensor {
  /**
   * Constructor
   */
  CO2_MG811::CO2_MG811(int pin) {
    CO2_MG811(pin, 0.99, 10);
  }
    
  /**
   * Constructor
   */
  CO2_MG811::CO2_MG811(int pin, float inertia, int tries) {
      this->_inertia = inertia;
      this->_tries = tries;
      this->_pin = pin;
      this->init();
  }

  void CO2_MG811::calibrate() {
      #if CO2_MG811_DEBUG
      Serial.println("Starting calibration...");
      #endif
      this->read();

      #if CO2_MG811_DEBUG
      Serial.print("Calibration. Old a: ");
      Serial.print(this->_co2_a);
      #endif

      this->_co2_a = this->_co2_v + co2_b;
      this->_co2ppm = co2_d;

      #if CO2_MG811_DEBUG
      Serial.print(", New a: ");
      Serial.println(_co2_a);
      #endif
  }

  void CO2_MG811::init() {
    #if CO2_MG811_DEBUG
    Serial.println("Starting initialization...");
    #endif
  
    this->_co2_a = 1500;
    this->_co2ppm = co2_d;
  }

  int CO2_MG811::getVoltage(){
    return this->_co2_v;
  }
    
    /**
     * Returns the PPM concentration
     */
    int CO2_MG811::read() {
      int v = 0;

      analogRead(this->_pin);
      for (int i = 0; i < _tries; i++)
      {
        v += analogRead(_pin);
        delay(20);
      }

      this->_co2_v = (1 - this->_inertia) * (v * 5000.0) / ( 1024.0 * this->_tries) + this->_co2_v * this->_inertia;
      double co2_exp = (this->_co2_a - this->_co2_v) / co2_b;
      this->_co2ppm = pow(co2_d, co2_exp);

      #if CO2_MG811_DEBUG
      Serial.print("Exponent: ");
      Serial.println(co2_exp);
      Serial.println("CO2 == ");
      Serial.print(_co2_v);
      Serial.println(" mV");
      Serial.print(_co2ppm);
      Serial.println(" ppm");
      #endif

    return this->_co2ppm;
  }
}