#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "m5stack_fan.h"

namespace esphome {
namespace m5stack_fan {

class M5StackFanSensor : public PollingComponent {
 public:
  void set_parent(M5StackFan *parent) { this->parent_ = parent; }
  void set_speed_sensor(sensor::Sensor *sensor) { this->speed_sensor_ = sensor; }
  
  void update() override;

 protected:
  M5StackFan *parent_{nullptr};
  sensor::Sensor *speed_sensor_{nullptr};
};

}  // namespace m5stack_fan
}  // namespace esphome
