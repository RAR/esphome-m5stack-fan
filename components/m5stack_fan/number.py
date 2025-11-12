import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import CONF_ID, ICON_FAN, UNIT_PERCENT
from . import M5StackFan, m5stack_fan_ns

CONF_M5STACK_FAN_ID = "m5stack_fan_id"

M5StackFanNumber = m5stack_fan_ns.class_("M5StackFanNumber", number.Number, cg.Component)

CONFIG_SCHEMA = number.number_schema(
    M5StackFanNumber,
    icon=ICON_FAN,
    unit_of_measurement=UNIT_PERCENT,
).extend(
    {
        cv.GenerateID(CONF_M5STACK_FAN_ID): cv.use_id(M5StackFan),
    }
)


async def to_code(config):
    var = await number.new_number(config, min_value=0, max_value=100, step=1)
    await cg.register_component(var, config)
    
    parent = await cg.get_variable(config[CONF_M5STACK_FAN_ID])
    cg.add(var.set_parent(parent))
