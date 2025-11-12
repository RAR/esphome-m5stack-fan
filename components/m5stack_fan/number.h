#pragma once

#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "m5stack_fan.h"

namespace esphome {
namespace m5stack_fan {

class M5StackFanNumber : public number::Number, public Component {
 public:
  void set_parent(M5StackFan *parent) { this->parent_ = parent; }
  void setup() override;
  void dump_config() override;

 protected:
  void control(float value) override;
  M5StackFan *parent_;
};

}  // namespace m5stack_fan
}  // namespace esphome
