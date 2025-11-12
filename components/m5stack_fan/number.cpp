#include "number.h"
#include "esphome/core/log.h"

namespace esphome {
namespace m5stack_fan {

static const char *const TAG = "m5stack_fan.number";

void M5StackFanNumber::setup() {
  // Read initial speed from fan module
  float speed = this->parent_->get_speed();
  this->publish_state(speed);
}

void M5StackFanNumber::dump_config() {
  ESP_LOGCONFIG(TAG, "M5Stack Fan Speed Control:");
  ESP_LOGCONFIG(TAG, "  Current Speed: %.0f%%", this->state);
}

void M5StackFanNumber::control(float value) {
  // Convert float to uint8_t and set fan speed
  uint8_t speed = static_cast<uint8_t>(value);
  
  if (this->parent_->set_speed(speed)) {
    this->publish_state(value);
    ESP_LOGD(TAG, "Fan speed set to %.0f%%", value);
  } else {
    ESP_LOGW(TAG, "Failed to set fan speed to %.0f%%", value);
  }
}

}  // namespace m5stack_fan
}  // namespace esphome
