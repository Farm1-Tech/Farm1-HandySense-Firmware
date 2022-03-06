#include <Arduino.h>
#include "Farm1.h"

// Temp & Humi
#include <Artron_SHT20.h>
#include <Adafruit_SHT31.h>
#include <DHT22.h>

// Temp
#include <OneWire.h>
#include <DallasTemperature.h>

// Soil
#include <ESP32AnalogRead.h>

// Light
#include <BH1750.h>
#include <Max44009.h>

// Class Template
#define TYPE_TEMPERATURE (1 << 0)
#define TYPE_HUMIDITY    (1 << 1)
#define TYPE_SOIL        (1 << 2)
#define TYPE_LIGHT       (1 << 3)

class Sensor_Base {
  public:
    virtual const uint8_t getType() = 0;
    virtual const char* getLabel() = 0;

    virtual int begin() {
      return 0;
    };

    virtual float getValue(uint8_t type) = 0;
};

// =========== Temperature Sensor ===========
// SHT20 
class _SHT20 : Sensor_Base {
  private:
    Artron_SHT20 *sht20 = NULL;

  public:
    const char* getLabel() {
      return "SHT20 (I2C)";
    }

    const uint8_t getType() override {
      return TYPE_TEMPERATURE | TYPE_HUMIDITY;
    }

    int begin() {
      if (!sht20) {
        sht20 = new Artron_SHT20(&Wire);
      }
      return sht20->begin() ? 0 : -1;
    }
    
    float getValue(uint8_t type) {
      if (type == TYPE_TEMPERATURE) {
        return sht20->readTemperature();
      }
      if (type == TYPE_HUMIDITY) {
        return sht20->readHumidity();
      }

      return 0.0;
    }
} SHT20_Sensor;

// SHT30
class _SHT30 : Sensor_Base {
  private:
    Adafruit_SHT31 *sht30 = NULL;

  public:
    const char* getLabel() {
      return "SHT30 (I2C, Address: 0x44)";
    }

    const uint8_t getType() override {
      return TYPE_TEMPERATURE | TYPE_HUMIDITY;
    }

    int begin() {
      if (!sht30) {
        sht30 = new Adafruit_SHT31();
      }

      return sht30->begin(0x44) ? 0 : -1;
    }
    
    float getValue(uint8_t type) {
      if (type == TYPE_TEMPERATURE) {
        return sht30->readTemperature();
      }
      if (type == TYPE_HUMIDITY) {
        return sht30->readHumidity();
      }

      return 0.0;
    }
} SHT30_Sensor;

// XY-MD02
#define MODE_SEND HIGH
#define MODE_RECV LOW

static uint16_t CRC16(uint8_t *buf, int len) {
	uint16_t crc = 0xFFFF;
	for (uint16_t pos = 0; pos < len; pos++) {
		crc ^= (uint16_t)buf[pos]; // XOR byte into least sig. byte of crc
		for (int i = 8; i != 0; i--) { // Loop over each bit
			if ((crc & 0x0001) != 0)
			{			   // If the LSB is set
				crc >>= 1; // Shift right and XOR 0xA001
				crc ^= 0xA001;
			}
			else
			{			   // Else LSB is not set
				crc >>= 1; // Just shift right
			}
		}
	}

	return crc;
}

static float readXY_MD02(uint8_t start_addr) {
	pinMode(RS485_DIR, OUTPUT);
	digitalWrite(RS485_DIR, MODE_RECV);

	Serial2.begin(9600, SERIAL_8N1, RS485_RX, RS485_TX); // Rx, Tx
	Serial2.setTimeout(200);

	uint8_t buff[] = {
		0x01, // Devices Address
		0x04, // Function code
		0x00, // Start Address HIGH
		start_addr, // 0x01, // Start Address LOW
		0x00, // Quantity HIGH
		0x01, // 0x02, // Quantity LOW
		0,	  // CRC LOW
		0	  // CRC HIGH
	};

	uint16_t crc = CRC16(&buff[0], 6);
	buff[6] = crc & 0xFF;
	buff[7] = (crc >> 8) & 0xFF;

	digitalWrite(RS485_DIR, MODE_SEND);
	Serial2.write(buff, sizeof(buff));
	Serial2.flush(); // wait MODE_SEND completed
	digitalWrite(RS485_DIR, MODE_RECV);

	if (Serial2.find("\x01\x04")) {
		while(!Serial2.available()) delay(1);

		uint8_t n = Serial2.read();
		// if (n != 4) {
		if (n != 2) {
			Serial.printf("Error data size : %d\n", n);
			return -20;
		}

		float value = ((uint16_t)(Serial2.read() << 8) | Serial2.read()) / 10.0;

		return value;
	}
	
	Serial.println("ERROR Timeout");
	return -10;
}

class _XY_MD02 : Sensor_Base {
  private:
    Adafruit_SHT31 *sht30 = NULL;

  public:
    const char* getLabel() {
      return "XY-MD02 (RS485, ID: 1)";
    }

    const uint8_t getType() override {
      return TYPE_TEMPERATURE | TYPE_HUMIDITY;
    }

    float getValue(uint8_t type) {
      if (type == TYPE_TEMPERATURE) {
        return readXY_MD02(0x01);
      }
      if (type == TYPE_HUMIDITY) {
        return readXY_MD02(0x02);
      }

      return 0.0;
    }
} XY_MD02_Sensor;

// DHT22 / AM2301
class _DHT22 : Sensor_Base {
  private:
    DHT *dht = NULL;

  public:
    const char* getLabel() {
      return "DHT22 (D3)";
    }

    const uint8_t getType() override {
      return TYPE_TEMPERATURE | TYPE_HUMIDITY;
    }

    int begin() {
      if (!dht) {
        dht = new DHT();
      }

      dht->setDHTgpio((gpio_num_t) D3);

      return 0;
    }
    
    float getValue(uint8_t type) {
      int ret = dht->readDHT();\
      if (ret != DHT_OK) {
        return ret;
      }

      if (type == TYPE_TEMPERATURE) {
        return dht->getTemperature();
      }
      if (type == TYPE_HUMIDITY) {
        return dht->getHumidity();
      }

      return 0.0;
    }
} DHT22_Sensor;

// DS18B20
class _DS18B20 : Sensor_Base {
  private:
    OneWire *oneWire = NULL;
    DallasTemperature *sensors = NULL;

  public:
    const char* getLabel() {
      return "DS18B20 (D3)";
    }

    const uint8_t getType() override {
      return TYPE_TEMPERATURE;
    }

    int begin() {
      if (!oneWire) {
        oneWire = new OneWire(D3);
      }
      if (!sensors) {
        sensors = new DallasTemperature(oneWire);
      }

      sensors->begin();

      return 0;
    }
    
    float getValue(uint8_t type) {
      sensors->requestTemperatures(); 

      if (type == TYPE_TEMPERATURE) {
        return sensors->getTempCByIndex(0);
      }

      return 0.0;
    }
} DS18B20_Sensor;

// =========== Soil Sensor ===========
// Capacitive Soil Moisture Sensor V1.2
class _CapacitiveSoilMoistureSensorV1_2 : Sensor_Base {
  private:
    ESP32AnalogRead *adc = NULL;

  public:
    const char* getLabel() {
      return "Capacitive Soil Moisture Sensor V1.2 (A1)";
    }

    const uint8_t getType() override {
      return TYPE_SOIL;
    }

    int begin() {
      if (!adc) {
        adc = new ESP32AnalogRead();
      }
      adc->attach(A1);
      
      return 0;
    }

    float getValue(uint8_t type) {
      float value = -1;
      if (type == TYPE_SOIL) {
        float realVolt = adc->readVoltage() / 3.3f * 9.9f;
        // Serial.printf("Volt = %.02f\n", realVolt);

        value = ((realVolt - 1.5f) / (2.8f - 1.5f)) * 100.0f;
        value = 100.0f - (value);
        value = min(max(value, 0.0f), 100.0f);
      }

      return value;
    }
} CapacitiveSoilMoistureSensorV1_2_Sensor;

// JXBS-3001-TR
bool readJXBS_3001_TR(uint8_t start_addr) {
	pinMode(RS485_DIR, OUTPUT);
	digitalWrite(RS485_DIR, MODE_RECV);

	Serial2.begin(9600, SERIAL_8N1, RS485_RX, RS485_TX); // Rx, Tx
	Serial2.setTimeout(200);

	uint8_t buff[] = {
		0x01, // Devices Address
		0x03, // Function code
		0x00, // Start Address HIGH
		start_addr, // 0x01, // Start Address LOW
		0x00, // Quantity HIGH
		0x01, // 0x02, // Quantity LOW
		0,	  // CRC LOW
		0	  // CRC HIGH
	};

	uint16_t crc = CRC16(&buff[0], 6);
	buff[6] = crc & 0xFF;
	buff[7] = (crc >> 8) & 0xFF;

	digitalWrite(RS485_DIR, MODE_SEND);
	Serial2.write(buff, sizeof(buff));
	Serial2.flush(); // wait MODE_SEND completed
	digitalWrite(RS485_DIR, MODE_RECV);

	if (Serial2.find("\x01\x03")) {
		while(!Serial2.available()) delay(1);

		uint8_t n = Serial2.read();
		// if (n != 4) {
		if (n != 2) {
			Serial.printf("Error data size : %d\n", n);
			return -20;
		}

		return ((uint16_t)(Serial2.read() << 8) | Serial2.read()) / 10.0;
	}
	
	Serial.println("ERROR Timeout");
	return -10;
}

class _JXBS_3001_TR : Sensor_Base {
  public:
    const char* getLabel() {
      return "JXBS-3001-TR (RS485, ID: 1)";
    }

    const uint8_t getType() override {
      return TYPE_TEMPERATURE | TYPE_SOIL;
    }

    float getValue(uint8_t type) {
      if (type == TYPE_TEMPERATURE) {
        return readJXBS_3001_TR(0x03);
      }
      if (type == TYPE_SOIL) {
        return readJXBS_3001_TR(0x02);
      }

      return 0.0;
    }
} JXBS_3001_TR_Sensor;

// =========== Light Sensor ===========
// BH1750
class _BH1750 : Sensor_Base {
  private:
    BH1750 *lightMeter = NULL;
  
  public:
    const char* getLabel() {
      return "BH1750 (Address: 0x23)";
    }

    const uint8_t getType() override {
      return TYPE_LIGHT;
    }

    int begin() {
      if (!this->lightMeter) {
        this->lightMeter = new BH1750(0x23); // ADDR connect to GND
      }
      
      return this->lightMeter->begin() ? 0 : -1;
    }

    float getValue(uint8_t type) {
      return type == TYPE_LIGHT ? this->lightMeter->readLightLevel() : 0.0;
    }
} BH1750_Sensor;

// MAX44009
class _MAX44009 : Sensor_Base {
  private:
    Max44009 *myLux = NULL;
  
  public:
    const char* getLabel() {
      return "MAX44009 (Address: 0x4A)";
    }

    const uint8_t getType() override {
      return TYPE_LIGHT;
    }

    int begin() {
      if (!this->myLux) {
        this->myLux = new Max44009(0x4A); // ADDR connect to GND
      }
      
      return 0;
    }

    float getValue(uint8_t type) {
      return type == TYPE_LIGHT ? this->myLux->getLux() : 0.0;
    }
} MAX44009_Sensor;
// ===============================

#define SENSOR_COUNT (sizeof(sensor_list) / sizeof(Sensor_Base*))

Sensor_Base *sensor_list[] = {
  // Temperature & Humidity
  (Sensor_Base*)&SHT20_Sensor,
  (Sensor_Base*)&SHT30_Sensor,
  (Sensor_Base*)&DHT22_Sensor,
  (Sensor_Base*)&XY_MD02_Sensor,

  // Temperature
  (Sensor_Base*)&DS18B20_Sensor,

  // Soil
  (Sensor_Base*)&CapacitiveSoilMoistureSensorV1_2_Sensor,
  (Sensor_Base*)&JXBS_3001_TR_Sensor,

  // Light
  (Sensor_Base*)&BH1750_Sensor,
  (Sensor_Base*)&MAX44009_Sensor,
};

static Sensor_Base* findFirstSensorByType(uint8_t type) {
  for (uint8_t i=0;i<SENSOR_COUNT;i++) {
    if ((sensor_list[i]->getType() & type) != 0) {
      return sensor_list[i];
    }
  }

  return NULL;
}

Sensor_Base *temp = NULL;
Sensor_Base *humi = NULL;
Sensor_Base *soil = NULL;
Sensor_Base *light = NULL;

void SensorManager_begin() {
  temp = findFirstSensorByType(TYPE_TEMPERATURE);
  humi = findFirstSensorByType(TYPE_HUMIDITY);
  soil = findFirstSensorByType(TYPE_SOIL);
  light = findFirstSensorByType(TYPE_LIGHT);

  temp->begin();
  humi->begin();
  soil->begin();
  light->begin();
}

float temp_value = 0.0;
float humi_value = 0.0;
float soil_value = 0.0;
float light_value = 0.0;

void SensorManager_runCycle() {
  static uint64_t sensor_read_timer = 0;
  if (((millis() - sensor_read_timer) >= 1000) || (sensor_read_timer == 0)) {
    temp_value = temp->getValue(TYPE_TEMPERATURE);
    humi_value = humi->getValue(TYPE_HUMIDITY);
    soil_value = soil->getValue(TYPE_SOIL);
    light_value = light->getValue(TYPE_LIGHT);

    sensor_read_timer = millis();
  }
}

float Sensor_get_temp() {
  return temp_value;
}

float Sensor_get_humi() {
  return humi_value;
}

float Sensor_get_soil() {
  return soil_value;
}

float Sensor_get_lux() {
  return light_value;
}
