#include "esphome.h"
#include <VL53L1X.h>

class VL53L1XSensor : public PollingComponent, public Sensor {
 public:
  VL53L1X sensor;

  VL53L1XSensor() : PollingComponent(500) {}

  void setup() override {
    Wire.begin();
    sensor.setTimeout(500);
    if (!sensor.init()) {
      ESP_LOGE("VL53L1X", "Failed to detect and initialize sensor!");
      mark_failed();
      return;
    }
    sensor.setDistanceMode(VL53L1X::Long);
    sensor.setMeasurementTimingBudget(50000);
    sensor.startContinuous(500);
    ESP_LOGI("VL53L1X", "Sensor initialized successfully!");
  }

  void update() override {
    uint16_t distance = sensor.read();
    if (sensor.timeoutOccurred()) {
      ESP_LOGW("VL53L1X", "Sensor timeout!");
      return;
    }
    publish_state(distance);
  }
};
