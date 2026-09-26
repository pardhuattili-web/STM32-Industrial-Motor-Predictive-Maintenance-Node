# Firmware Architecture

## Data Flow

```
Sensors
  |
  v
Sensor Interface
  |
  v
Filter / Scale
  |
  v
Feature Extraction
  |
  +--------------------+
  |                    |
  v                    v
Health Monitor      Fault FSM
  |                    |
  +---------+----------+
            |
            v
      Modbus Register Map
            |
            v
      RS-485 / Modbus RTU
```

## Module Responsibilities

### sensor_if
Provides a hardware-independent interface for temperature, vibration, and current measurements. The reference scaffold may return simulated values until real sensors are selected.

### health_monitor
Converts measurements into normalized severity indicators and calculates the 0–100 health score.

### fault_fsm
Implements NORMAL, WARNING, FAULT, and RECOVERY states with persistent sample counters to avoid reacting to a single noisy sample.

### modbus_map
Maintains the application register image that a Modbus RTU slave stack can expose to an external PLC, HMI, or PC master.

## Design Principles

- Keep sensor access independent from diagnostics.
- Keep fault decisions deterministic and testable.
- Avoid blocking work in time-critical acquisition code.
- Use fixed-point/integer register values for Modbus transport.
- Separate physical calibration from business logic.
