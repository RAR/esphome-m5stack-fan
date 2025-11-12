# ESPHome M5Stack Fan Module v1.1 Component

ESPHome component for the M5Stack Fan Module v1.1 (SKU: M017-A).

## Features

- I2C communication with STM32F0 microcontroller
- Speed control 0-100%
- Speed readback sensor
- Compatible with ESP-IDF and Arduino frameworks

## Hardware

The M5Stack Fan Module v1.1 uses a STM32F0 microcontroller at I2C address `0x88`. The fan speed is controlled by writing a single byte (0-100) to register `0x00`, and the current speed can be read from the same register.

**Documentation:** https://docs.m5stack.com/en/module/Module%20Fan%20v1.1

## Installation

Add this repository as an external component in your ESPHome configuration:

```yaml
external_components:
  - source: github://RAR/esphome-m5stack-fan
    components: [ m5stack_fan ]
```

## Configuration

### Basic Configuration

```yaml
i2c:
  sda: 32
  scl: 33
  scan: true

m5stack_fan:
  id: my_fan

number:
  - platform: m5stack_fan
    m5stack_fan_id: my_fan
    name: "Fan Speed"
    id: fan_speed_control

sensor:
  - platform: m5stack_fan
    m5stack_fan_id: my_fan
    update_interval: 10s
    speed:
      name: "Fan Speed Readback"
```

### Configuration Variables

#### M5Stack Fan Component

- **id** (*Optional*, ID): Manually specify the ID for this component.

#### Number Platform

- **m5stack_fan_id** (*Required*, ID): The ID of the M5Stack Fan component.
- **name** (*Required*, string): The name of the number entity.
- All other options from [Number](https://esphome.io/components/number/index.html)

#### Sensor Platform

- **m5stack_fan_id** (*Required*, ID): The ID of the M5Stack Fan component.
- **update_interval** (*Optional*, Time): How often to poll the fan speed. Defaults to 60s.
- **speed** (*Optional*): Speed sensor configuration
  - **name** (*Required*, string): The name of the sensor.
  - All other options from [Sensor](https://esphome.io/components/sensor/index.html)

## Usage

The number entity allows you to control the fan speed from 0% to 100%. The sensor entity reports the current fan speed by reading back from the hardware.

In Home Assistant, the fan will appear as a number slider that you can adjust. You can also control it via automations:

```yaml
# Home Assistant automation example
automation:
  - alias: "Cool down when hot"
    trigger:
      - platform: numeric_state
        entity_id: sensor.temperature
        above: 30
    action:
      - service: number.set_value
        target:
          entity_id: number.fan_speed
        data:
          value: 100
```

## License

MIT License

## Author

- **RAR** - [GitHub](https://github.com/RAR)
