# Motor Health Model

## Inputs

| Signal | Reference range | Contribution |
|---|---|---|
| Temperature | application-specific | Thermal severity |
| Vibration | application-specific | Mechanical severity |
| Current | application-specific | Load/electrical severity |

## Severity

Each signal is converted to a bounded penalty from 0 to 100.

For a generic signal x with warning threshold w and critical threshold c:

```
penalty = 0                  when x <= w
penalty = 50 * (x-w)/(c-w) when w < x < c
penalty = 100                when x >= c
```

The exact implementation should be tuned for the actual motor and sensor.

## Combined Health Score

```
health = 100
         - Wt * temp_penalty
         - Wv * vib_penalty
         - Wi * current_penalty
```

The score is clamped to 0–100.

Reference weights:

- Temperature: 0.35
- Vibration: 0.40
- Current: 0.25

These are starting values, not a validated maintenance model.

## Interpretation

| Score | State |
|---:|---|
| 80–100 | Normal |
| 60–79 | Observe |
| 30–59 | Warning |
| 0–29 | Critical |

Use application-specific validation before treating these values as maintenance limits.
