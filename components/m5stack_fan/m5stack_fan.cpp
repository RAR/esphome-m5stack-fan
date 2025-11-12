#include "m5stack_fan.h"
#include "esphome/core/log.h"

namespace esphome {
namespace m5stack_fan {

static const char *const TAG = "m5stack_fan";

void M5StackFan::setup() {
  ESP_LOGCONFIG(TAG, "Setting up M5Stack Fan Module...");
  
  // Set PWM frequency to 48kHz (value 3)
  if (!this->write_byte(FAN_PWM_FREQUENCY_REG, 3)) {
    ESP_LOGE(TAG, "Failed to set PWM frequency");
    this->mark_failed();
    return;
  }
  
  // Enable the fan (write 1 to control register)
  if (!this->write_byte(FAN_CONTROL_REG, 1)) {
    ESP_LOGE(TAG, "Failed to enable fan module");
    this->mark_failed();
    return;
  }
  
  // Initialize fan to 0% speed
  if (!this->set_speed(0)) {
    ESP_LOGE(TAG, "Failed to initialize fan speed");
    this->mark_failed();
    return;
  }
  
  ESP_LOGCONFIG(TAG, "M5Stack Fan Module initialized successfully");
}

void M5StackFan::dump_config() {
  ESP_LOGCONFIG(TAG, "M5Stack Fan Module:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with M5Stack Fan failed!");
  }
  ESP_LOGCONFIG(TAG, "  Current Speed: %d%%", this->current_speed_);
}

bool M5StackFan::set_speed(uint8_t speed) {
  // Clamp speed to 0-100
  if (speed > 100) {
    speed = 100;
  }
  
  // Write speed value to PWM duty cycle register (0x20)
  if (!this->write_byte(FAN_PWM_DUTY_CYCLE_REG, speed)) {
    ESP_LOGW(TAG, "Failed to write speed to fan module");
    return false;
  }
  
  this->current_speed_ = speed;
  ESP_LOGD(TAG, "Set fan speed to %d%%", speed);
  return true;
}

uint8_t M5StackFan::get_speed() {
  uint8_t speed = 0;
  
  // Read current speed from PWM duty cycle register (0x20)
  if (!this->read_byte(FAN_PWM_DUTY_CYCLE_REG, &speed)) {
    ESP_LOGW(TAG, "Failed to read speed from fan module");
    return this->current_speed_;  // Return cached value on error
  }
  
  this->current_speed_ = speed;
  return speed;
}

}  // namespace m5stack_fan
}  // namespace esphome
