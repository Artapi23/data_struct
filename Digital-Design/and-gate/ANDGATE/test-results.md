# AND Gate — Test Run Results

## Tools

- Simulator: **GHDL 6.0.0**
- VHDL standard: **VHDL-2008** (`--std=08`)

## Source files

- `design.vhd` — AND gate implementation
- `testbench.vhd` — `AND_GATE_TB` testbench

## Commands run

```powershell
ghdl -a --std=08 design.vhd
ghdl -a --std=08 testbench.vhd
ghdl -e --std=08 AND_GATE_TB
ghdl -r --std=08 AND_GATE_TB --vcd=and_gate.vcd --stop-time=50ns
```

## Compilation and simulation status

| Step | Result |
|---|---|
| Analyze `design.vhd` | Passed |
| Analyze `testbench.vhd` | Passed |
| Elaborate `AND_GATE_TB` | Passed |
| Run simulation | Passed — no errors |

## Simulation results

| Time | A | B | Y |
|---:|---:|---:|---:|
| 0 ns | 0 | 0 | 0 |
| 10 ns | 0 | 1 | 0 |
| 20 ns | 1 | 0 | 0 |
| 30 ns | 1 | 1 | 1 |

All four input combinations produce the expected AND-gate output.

## Waveform

The simulation generated `and_gate.vcd`. It can be opened in a waveform viewer such as GTKWave.
