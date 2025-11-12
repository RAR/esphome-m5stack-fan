import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    ICON_FAN,
    STATE_CLASS_MEASUREMENT,
    UNIT_PERCENT,
)
from . import M5StackFan, m5stack_fan_ns

CONF_M5STACK_FAN_ID = "m5stack_fan_id"
CONF_SPEED = "speed"

M5StackFanSensor = m5stack_fan_ns.class_(
    "M5StackFanSensor", sensor.Sensor, cg.PollingComponent
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(M5StackFanSensor),
        cv.GenerateID(CONF_M5STACK_FAN_ID): cv.use_id(M5StackFan),
        cv.Optional(CONF_SPEED): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            icon=ICON_FAN,
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
).extend(cv.polling_component_schema("60s"))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    parent = await cg.get_variable(config[CONF_M5STACK_FAN_ID])
    cg.add(var.set_parent(parent))
    
    if speed_config := config.get(CONF_SPEED):
        sens = await sensor.new_sensor(speed_config)
        cg.add(var.set_speed_sensor(sens))
