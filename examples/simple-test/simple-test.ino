#include <CO2_MG811.h>

using namespace AnalogSensor;
const int co2_port=A0;
CO2_MG811 * co2_sensor;

void setup() {
  Serial.begin(9600);
  co2_sensor = new CO2_MG811(co2_port, 0.99, 100);
  co2_sensor->calibrate();
}

void loop() {
  int val = co2_sensor->read();
  Serial.print("CO2:");
  Serial.println(val);
}
