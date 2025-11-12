#include "sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace m5stack_fan {

static const char *const TAG = "m5stack_fan.sensor";

void M5StackFanSensor::update() {
  if (this->parent_ == nullptr) {
    return;
  }
  
  uint8_t speed = this->parent_->get_speed();
  
  if (this->speed_sensor_ != nullptr) {
    this->speed_sensor_->publish_state(speed);
  }
}

}  // namespace m5stack_fan
}  // namespace esphome
