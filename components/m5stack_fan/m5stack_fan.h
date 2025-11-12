#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m5stack_fan {

class M5StackFan : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  // Set fan speed (0-100%)
  bool set_speed(uint8_t speed);
  
  // Get current fan speed
  uint8_t get_speed();

 protected:
  uint8_t current_speed_{0};
};

}  // namespace m5stack_fan
}  // namespace esphome
