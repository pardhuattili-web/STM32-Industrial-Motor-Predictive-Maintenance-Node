# Test Plan

## Measurement Tests

| ID | Test | Expected result |
|---|---|---|
| M01 | Normal temperature/current/vibration | Stable values and NORMAL state |
| M02 | Temperature above warning limit | WARNING state |
| M03 | Temperature above critical limit | FAULT state |
| M04 | Excess vibration | Vibration fault |
| M05 | Excess current | Over-current fault |

## Fault-State Tests

| ID | Test | Expected result |
|---|---|---|
| F01 | One noisy sample over threshold | No immediate FAULT |
| F02 | Persistent threshold exceedance | FAULT |
| F03 | Fault condition clears | RECOVERY |
| F04 | Stable recovery window completes | NORMAL |
| F05 | Sensor invalid | Sensor fault/diagnostic bit |

## Modbus Tests

| ID | Test | Expected result |
|---|---|---|
| B01 | Read registers 40001–40008 | Correct scaled data |
| B02 | Invalid slave address | No response |
| B03 | Invalid function | Exception response |
| B04 | Corrupted CRC | Frame rejected |
| B05 | Repeated polling | Stable responses |

## Integration Evidence

Before presenting the project, add:

- STM32CubeIDE build screenshot
- RS-485 hardware photo
- Modbus analyzer screenshot
- State-machine test results
- Sensor data log
- Short demo video

## Validation Status

This repository is a reference firmware/documentation scaffold. Physical sensor and motor validation should be completed and documented before claiming field accuracy.
