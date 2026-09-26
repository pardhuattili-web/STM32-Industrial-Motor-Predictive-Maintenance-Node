# Modbus RTU Register Map

## Node Configuration

- Slave address: 0x01
- Serial interface: UART + RS-485 transceiver
- Reference mode: 8 data bits, even parity, 1 stop bit
- Function code: 0x03 for holding-register reads

## Holding Registers

| Address | Parameter | Scaling | Notes |
|---:|---|---:|---|
| 40001 | Temperature | x10 | 0.1 °C |
| 40002 | Vibration | x100 | 0.01 engineering units |
| 40003 | Motor current | x10 | 0.1 A |
| 40004 | Health score | x1 | 0–100 |
| 40005 | Fault code | x1 | enum |
| 40006 | Fault state | x1 | enum |
| 40007 | Sample counter | x1 | wraps at 65535 |
| 40008 | Device status | bit field | status flags |
| 40009 | Warning count | x1 | accumulated |
| 40010 | Fault count | x1 | accumulated |

## Fault Codes

| Code | Meaning |
|---:|---|
| 0 | No active fault |
| 1 | Over-temperature |
| 2 | Excessive vibration |
| 3 | Over-current |
| 4 | Sensor timeout |
| 5 | Sensor out of range |

## State Codes

| Code | Meaning |
|---:|---|
| 0 | NORMAL |
| 1 | WARNING |
| 2 | FAULT |
| 3 | RECOVERY |

## Device Status Bits

| Bit | Meaning |
|---:|---|
| 0 | Temperature sensor valid |
| 1 | Vibration sensor valid |
| 2 | Current sensor valid |
| 3 | Modbus link active |
| 4 | Warning active |
| 5 | Fault active |
| 6 | Data ready |
