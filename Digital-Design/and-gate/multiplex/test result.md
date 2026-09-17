# Multiplexer 16-to-1 — Test Result

## Configuration

| Signal | Value |
|---|---|
| Input `d[15:0]` | `1010_1100_0101_0011` |
| Select `sel[3:0]` | Tested from `0000` to `1111` |
| Test interval | 10 ns per selection |

The multiplexer output follows `y = d(sel)`.

## Results

| Time (ns) | `sel` | Selected input | Expected `y` |
|---:|:---:|:---:|:---:|
| 0 | `0000` | `d(0)` | `1` |
| 10 | `0001` | `d(1)` | `1` |
| 20 | `0010` | `d(2)` | `0` |
| 30 | `0011` | `d(3)` | `0` |
| 40 | `0100` | `d(4)` | `1` |
| 50 | `0101` | `d(5)` | `0` |
| 60 | `0110` | `d(6)` | `1` |
| 70 | `0111` | `d(7)` | `0` |
| 80 | `1000` | `d(8)` | `0` |
| 90 | `1001` | `d(9)` | `0` |
| 100 | `1010` | `d(10)` | `1` |
| 110 | `1011` | `d(11)` | `1` |
| 120 | `1100` | `d(12)` | `0` |
| 130 | `1101` | `d(13)` | `1` |
| 140 | `1110` | `d(14)` | `0` |
| 150 | `1111` | `d(15)` | `1` |

## Conclusion

The 16-to-1 multiplexer correctly selects the input bit identified by `sel`.
