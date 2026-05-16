# GSS Control Firmware

Firmware for the **GSS (Gate Stress Switching) controller** running on an **STM32G474RE** with **ChibiOS 21.11**.

The firmware provides a USB CDC shell for:
- running gate-stress PWM test batches,
- reading accumulated cycle counts,
- measuring gate supply rails,
- selecting DUT relays,
- reading board ID and firmware version,
- entering DFU/reset.

## Repository Layout

- `main.c` / `main.h` - startup, USB CDC shell, system commands (`status`, `stop`, `dfu`, `reset`)
- `gss.c` / `gss.h` - GSS test logic, HRTIM configuration, ADC supply measurement, DUT and ID commands
- `usbcfg.c` / `usbcfg.h` - USB device configuration
- `board/` - board and pin configuration
- `cfg/` - ChibiOS/MCU configuration headers

## Requirements

- ARM GCC toolchain (`arm-none-eabi-*`)
- GNU Make
- ChibiOS 21.11 source tree available at:
  - `../../chibios2111` (relative to this repository root)

> Note: `Makefile` expects the ChibiOS tree at the path above via `CHIBIOS = ../../chibios2111`.

## Build

From repository root:

```bash
make
```

Build artifacts are generated in `./build`.

## Flash / Debug

The repository contains launch configurations in `debug/` for OpenOCD-based flash/run/debug workflows.

## USB Shell Commands

After connecting over USB CDC and opening a terminal:

- `GSS_test <cycles> <freq_hz> <duty>`
  - Run one test batch (blocks until complete).
  - Example: `GSS_test 100000 1000 0.5`
- `GSS_cycles`
  - Print total accumulated cycle count.
- `measure_supply`
  - Print measured gate supplies (`POS:+xx.xx NEG:yy.yy`).
- `measure_DUT <0-8>`
  - Select DUT relay (`0` deselects all).
- `ID`
  - Print board serial + firmware version (`GSS,SN:XX,VER:x.y`).
- `status`
  - Print currently running test status.
- `stop`
  - Stop active test output.
- `dfu`
  - Reboot into USB DFU bootloader.
- `reset`
  - Software reset.

## Notes

- Firmware version string is defined in `gss.h` (`GSS_FW_VERSION`).
- HRTIM outputs and ADC/DUT/ID pin usage are documented in `gss.h` and `main.h`.
