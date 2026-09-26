# STM32 Industrial Motor Predictive Maintenance Node

> **Industrial embedded systems project | STM32 + Embedded C + RS-485 + Modbus RTU**

A modular STM32 monitoring node for detecting abnormal industrial motor conditions from temperature, vibration, and electrical-current signals. The firmware converts raw measurements into filtered engineering values, calculates a lightweight motor health score, runs a fault state machine, and exposes diagnostic data through an RS-485/Modbus RTU interface.

The design is suitable for a **portfolio/reference implementation** and can be connected to real sensors after the board-specific ADC, I²C/SPI, and RS-485 transceiver configuration is completed.

## Problem Statement

Industrial motors can degrade gradually through overheating, excessive vibration, abnormal current draw, bearing wear, imbalance, or poor operating conditions. A compact embedded monitoring node can continuously observe these signals and flag abnormal trends before they become equipment failures.

## Objectives

- Periodically sample motor temperature, vibration, and current.
- Apply simple digital filtering to noisy signals.
- Extract diagnostic indicators from sensor data.
- Calculate an interpretable motor health score.
- Detect and classify abnormal conditions.
- Maintain a fault/state machine with recovery behavior.
- Publish measurements through Modbus RTU over RS-485.
- Keep the firmware modular enough to replace simulated inputs with real sensors.

## System Architecture

```
Temperature Sensor ─┐
Vibration Sensor ───┼──> Sensor Acquisition
Current Sensor ─────┘          |
                               v
                       Filtering / Scaling
                               |
                               v
                      Feature Extraction
                               |
                               v
                    Health Score + Fault FSM
                         |              |
                         v              v
                  Local Diagnostics   Modbus Map
                                       |
                                       v
                                  RS-485 / Modbus
                                       |
                                       v
                                  PC / PLC / HMI
```

## Target Platform

| Item | Selection |
|---|---|
| MCU | STM32 family |
| Language | Embedded C |
| IDE | STM32CubeIDE |
| Analog input | ADC / DMA |
| Digital sensors | I²C / SPI |
| Serial interface | UART |
| Field bus | RS-485 |
| Protocol | Modbus RTU |
| Storage | Optional internal Flash |
| Debug | SWD + UART |

> Exact STM32 part number, pinout, ADC channel, sensor model, and RS-485 transceiver should be selected during hardware integration.

## Repository Structure

```
STM32-Industrial-Motor-Predictive-Maintenance-Node/
├── README.md
├── docs/
│   ├── architecture.md
│   ├── health_model.md
│   ├── modbus_register_map.md
│   └── test_plan.md
└── firmware/
    ├── Inc/
    │   ├── sensor_if.h
    │   ├── health_monitor.h
    │   ├── fault_fsm.h
    │   └── modbus_map.h
    └── Src/
        ├── sensor_if.c
        ├── health_monitor.c
        ├── fault_fsm.c
        └── modbus_map.c
```

## Diagnostic Parameters

- Temperature (°C)
- Vibration level
- Motor current (A)
- Vibration trend
- Current deviation from nominal
- Temperature severity
- Overall health score (0–100)
- Active fault code
- Operating state

## Health Score

```
Health = 100 - (temperature_penalty
                + vibration_penalty
                + current_penalty)
```

Each penalty is clamped before combination so one noisy measurement cannot produce an arbitrary score. Weighting and thresholds are documented in `docs/health_model.md` and should be calibrated for the actual motor and sensor set.

## Fault State Machine

```
        +-------+
        | NORMAL|
        +---+---+
            |
     threshold exceeded
            v
      +-----+------+
      |   WARNING  |
      +-----+------+
            |
   persistent/critical fault
            v
      +-----+------+
      |    FAULT   |
      +-----+------+
            |
       condition clears
            v
        RECOVERY
            |
      stable samples
            v
         NORMAL
```

## Modbus RTU

The node acts as a **Modbus RTU slave** over RS-485.

| Register | Parameter | Format |
|---:|---|---|
| 40001 | Temperature | °C × 10 |
| 40002 | Vibration | units × 100 |
| 40003 | Current | A × 10 |
| 40004 | Health score | 0–100 |
| 40005 | Fault code | enum |
| 40006 | State | enum |
| 40007 | Sample counter | 16-bit |
| 40008 | Device status | bit field |

See `docs/modbus_register_map.md` for the complete map and scaling rules.

## Development Roadmap

### Phase 1 — Sensor Layer
- [x] Repository structure
- [x] Diagnostic data model
- [ ] ADC acquisition
- [ ] Vibration sensor driver
- [ ] Temperature sensor driver
- [ ] Current sensor scaling

### Phase 2 — Signal Processing
- [ ] Moving-average filtering
- [ ] Vibration metric extraction
- [ ] Current baseline calculation
- [ ] Temperature severity calculation
- [ ] Health-score calculation

### Phase 3 — Fault Logic
- [ ] Threshold detection
- [ ] Fault state machine
- [ ] Hysteresis/persistence
- [ ] Fault/event logging

### Phase 4 — Industrial Communication
- [ ] UART/RS-485 driver
- [ ] Modbus RTU framing
- [ ] CRC validation
- [ ] Register map implementation
- [ ] Exception responses

### Phase 5 — Reliability
- [ ] Watchdog
- [ ] Sensor timeout handling
- [ ] Configuration persistence
- [ ] Maintenance counter
- [ ] Long-duration logging

## Validation Strategy

1. Feed synthetic sensor values into the firmware.
2. Verify filtering and health calculations.
3. Sweep values across warning/fault thresholds.
4. Validate state transitions and hysteresis.
5. Validate Modbus register values and CRC behavior.
6. Connect a USB-to-RS-485 interface or PLC simulator.
7. Only then integrate approved industrial sensors and a controlled motor test setup.

The repository should only claim real sensor accuracy after the selected sensors and calibration procedure have been physically validated.

## Portfolio Skills Demonstrated

- Embedded C
- STM32 firmware architecture
- ADC and sensor interfacing
- Digital filtering
- Fault/state-machine design
- Predictive-maintenance concepts
- RS-485
- Modbus RTU
- Diagnostics and telemetry
- Industrial automation concepts

## Future Extensions

- FFT-based vibration analysis
- Bearing-fault indicators
- TinyML anomaly detection
- Ethernet/Modbus TCP gateway
- CAN bridge
- Web dashboard
- SD-card logging
- FreeRTOS task-based architecture
- Cloud telemetry

## Status

**Architecture + reference firmware scaffold**

Hardware-specific drivers and physical motor validation remain to be completed for the chosen STM32 board and sensors.

## Author

**Pardhu Attili**

GitHub: [@pardhuattili-web](https://github.com/pardhuattili-web)
