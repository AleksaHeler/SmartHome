#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads(0x48);
const int lightPin = 0;
const int analogTempPin = 1;

void setup_analog(){
  ads.begin();
}

float  get_light(){
  float value;
  value = 1.0 * constrain(map(ads.readADC_SingleEnded(lightPin), 0, 16384, 1000, 0), 0, 1000) / 1000.0;
  return value;
}

float get_analog_temp(){
  unsigned int reading;
  reading = ads.readADC_SingleEnded(analogTempPin);

  float temp;
  temp = log(10000.0*((17400.0/reading - 1)));
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
  temp = temp - 273.15;
  return temp;
}
