# DryGASCON128k32-arm-cortex-m
Self contained DryGASCON128k32 AEAD and Hash, optimized for ARM Cortex-M CPUs

## Properties
- Probably the lowest code size on Cortex-M
- Probably the fastest on Cortex-M
- Constant time implementation
- Leverage the algorithmic protection against side channel and fault attacks provided by DryGASCON
    - key recovery by DPA claimed to be impossible.
    - key recovery by SPA may be possible with a very good measurement setup. Add light "hiding" countermeasure if needed.
    - key recovery by DFA and SIFA claimed to be impossible.

## Code size
Code size in bytes, results may vary slightly depending on how you call the functions.

|      | Cortex-M0 | Cortex-M3 | Cortex-M4 | Cortex-M7 |
|:----:|:---------:|:---------:|:---------:|:---------:|
| HASH | 1244      | 1184      | 1184      | 1184      |  
| AEAD | 1500      | 1416      | 1408      | 1408      |  
| BOTH | 1656      | 1600      | 1632      | 1568      |  

### Measurement method:
Figures are obtained by setting VALIDATION=0 and changing constants DO_HASH and DO_AEAD in test/test.cpp
Example for Cortex-M4: output of build with platformio's defaults
````
#define DO_HASH 0
#define DO_AEAD 0
RAM:   [          ]   2.7% (used 3488 bytes from 131072 bytes)
Flash: [=         ]   8.3% (used 43628 bytes from 524288 bytes)

#define DO_HASH 1
#define DO_AEAD 0
RAM:   [          ]   2.7% (used 3488 bytes from 131072 bytes)
Flash: [=         ]   8.5% (used 44812 bytes from 524288 bytes)

#define DO_HASH 0
#define DO_AEAD 1
RAM:   [          ]   2.7% (used 3488 bytes from 131072 bytes)
Flash: [=         ]   8.6% (used 45036 bytes from 524288 bytes)

#define DO_HASH 1
#define DO_AEAD 1
RAM:   [          ]   2.7% (used 3488 bytes from 131072 bytes)
Flash: [=         ]   8.6% (used 45260 bytes from 524288 bytes)
````

## Warning
This code has been stripped of all sanity checks. If the inputs are not as
expected, you will get garbage as output.

Requirements on inputs:
- AEAD input and output buffers shall not overlap
- AEAD key is 32 bytes (so called `fast profile`)
    - 16 lsb can be anything
    - 16 msb shall encode unique 32 bit words
