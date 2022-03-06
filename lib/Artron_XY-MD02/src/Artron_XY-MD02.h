#include "Arduino.h"

class XY_MD02 {
    private:
        uint8_t _id = 1;
        HardwareSerial *_serial;
    
    public:
        XY_MD02(uint8_t id = 1, HardwareSerial *serial = &Serial2) ;
        bool begin() ;
        float readTemperature() ;
        float readHumidity() ;

};
