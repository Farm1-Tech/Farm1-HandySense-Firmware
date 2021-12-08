#include "Artron_SHT20.h"

Artron_SHT20::Artron_SHT20(TwoWire* wire) : _wire(wire) {

}

bool Artron_SHT20::begin() {
    return write(0b11111110) == 0;
}

float Artron_SHT20::readTemperature() {
    uint8_t buff[3];
    if (this->read(0b11110011, buff, 3, 100) != 0) { // Trigger T measurement, no hold master, wait 100 mS for measurement
      // Serial.printf("SHT20 Read Temperature measurement fail\n");
      return -999;
    }

    return -46.85 + 175.72 * (int)((buff[0] << 8) | buff[1]) / (float)pow(2, 16);
}

float Artron_SHT20::readHumidity() {
    uint8_t buff[3];
    if (this->read(0b11110101, buff, 3, 100) != 0) { // Trigger RH measurement, no hold master, wait 100 mS for measurement
      // Serial.printf("SHT20 Read Humidity measurement fail\n");
      return -999;
    }

    return -6 + 125 * (int)((buff[0] << 8) | buff[1]) / (float)pow(2, 16);
}

int Artron_SHT20::write(uint8_t command, uint8_t *data, uint8_t len) {
  this->_wire->beginTransmission(SHT20_ADDR);
  this->_wire->write(command);
  this->_wire->write(data, len);
  int res = this->_wire->endTransmission(true); // Stop

  return res;
}

int Artron_SHT20::read(uint8_t command, uint8_t *data, int len, int stop) {
  this->_wire->beginTransmission(SHT20_ADDR);
  this->_wire->write(command);
  int res = this->_wire->endTransmission(true); // Stop

  if (res != 0) {
    return res;
  }

  delay(stop);

  int n = this->_wire->requestFrom(SHT20_ADDR, len);
  for (int i=0;i<n;i++) {
    data[i] = this->_wire->read();
  }
  
  return n == len ? 0 : -1;
}
