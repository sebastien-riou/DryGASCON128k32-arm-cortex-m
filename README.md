# DryGASCON128k32-arm-cortex-m
Self contained DryGASCON128k32 AEAD and Hash, optimized for ARM Cortex-M CPUs.

This repository also provides a validation suite usable for any DryGASCON128k32 implementation.

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
| HASH | 1316      | 1256      | 1272      | 1284      |  
| AEAD | 1580      | 1488      | 1496      | 1508      |  
| BOTH | 1708      | 1648      | 1656      | 1672      |  

### Measurement method:
Figures are obtained by setting `VALIDATION`=0 and changing constants `DO_HASH` and `DO_AEAD` in `src/test/test.cpp`
Example for Cortex-M7: output of build with platformio's defaults
````
#define DO_HASH 0
#define DO_AEAD 0
Flash: [          ]   3.0% (used 63752 bytes from 2097152 bytes)

#define DO_HASH 1
#define DO_AEAD 0
Flash: [          ]   3.1% (used 65036 bytes from 2097152 bytes)

#define DO_HASH 0
#define DO_AEAD 1
Flash: [          ]   3.1% (used 65260 bytes from 2097152 bytes)

#define DO_HASH 1
#define DO_AEAD 1
Flash: [          ]   3.1% (used 65424 bytes from 2097152 bytes)
````

## Warning
This code has been stripped of all sanity checks. If the inputs are not as
expected, you will get garbage as output.

Requirements on inputs:
- AEAD input and output buffers shall not overlap
- AEAD key is 32 bytes (so called `fast profile`)
    - 16 lsb can be anything
    - 16 msb shall encode unique 32 bit words

## How to build ?
This repository is a ready to use platformio project. If you wish to use something else, you can have a look at platformio.ini for hints, it is self explanatory.

---

NOTE: The project uses `mbed` or `arduino` framework depending on the target. Those frameworks are not needed at all if you just want to insert DryGASCON into your project. 

---

Other implementations of DryGASCON can be found here: [DryGASCON](https://github.com/sebastien-riou/DryGASCON).