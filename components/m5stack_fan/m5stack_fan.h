#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m5stack_fan {

// Register definitions from M5Stack Fan Module v1.1
static const uint8_t FAN_CONTROL_REG = 0x00;        // Enable/disable fan
static const uint8_t FAN_PWM_DUTY_CYCLE_REG = 0x20; // PWM duty cycle (0-100%)
static const uint8_t FAN_RPM_REG = 0x30;            // RPM reading (2 bytes)

class M5StackFan : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  
  void set_speed(uint8_t speed);
  uint8_t get_speed();

 protected:
  uint8_t current_speed_{0};
};

}  // namespace m5stack_fan
}  // namespace esphome
