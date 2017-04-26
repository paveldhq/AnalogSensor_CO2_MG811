#ifndef CO2_MG811_h
#define CO2_MG811_h

#include <Arduino.h>

namespace AnalogSensor {
class CO2_MG811
{
  public:
    /**
     * Constructor
     */
    CO2_MG811(int pin);
    
    /**
     * Constructor
     */
    CO2_MG811(int pin, float inertia, int tries);
    
    /**
     * Returns the PPM concentration
     */
    int read();

    /**
     * Calibrates the start point of 400
     */    
    void calibrate();

    /**
     * Returns the voltage
     */
    int getVoltage();
  private:
    /**
     * Internal initialization
     */
    void init();

    int _pin;
    int _inertia;
    int _tries;
    int _co2_v;
    
    double _co2_a;
    double _co2ppm;
};
}
#endif