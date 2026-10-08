# pico-rtos

A small real-time operating system for the Arm Cortex-M0+, written in C and
assembly with no vendor SDK, and a handheld game console that runs on it.

I'm building it to learn how embedded software works below the library level:
what runs before `main`, how hardware is driven through registers, and how a
processor switches between tasks.

**Status: early.** The repository currently holds the bit-manipulation helpers
and their tests. Nothing has run on a board yet.

## What's here

| Path | What it is |
|---|---|
| `include/bits.h` | Helpers to set, clear, toggle and test single bits, and to read or replace a group of bits inside a 32-bit register value |
| `test/test_bits.c` | Tests for those helpers that run on a laptop |

## Run the tests

No board needed, only a C compiler:

```sh
gcc -std=c11 -Wall -Wextra -Iinclude test/test_bits.c -o test_bits
./test_bits
```

## Roadmap

### Version 1: the kernel

- [x] Bit-manipulation helpers with laptop tests
- [ ] Start-up code, vector table and linker script
- [ ] Clock setup and an LED blink through raw register writes
- [ ] UART driver for serial output
- [ ] Timer interrupt (SysTick)
- [ ] Context switching and a pre-emptive round-robin scheduler
- [ ] Sleep and semaphores
- [ ] Fault handler that prints the processor's registers

### Version 2: the console

- [ ] I2C driver
- [ ] SSD1306 display driver with text and simple graphics
- [ ] Button input with debouncing
- [ ] Sound through a piezo buzzer
- [ ] A game with its logic, display, sound and input as separate tasks

## Hardware

- Raspberry Pi Pico H (RP2040, dual Arm Cortex-M0+; this project uses one core)
- Raspberry Pi Debug Probe, for SWD debugging and serial output
- 0.96" 128x64 OLED display (SSD1306, I2C)
- Push buttons and a piezo buzzer

## References

- [RP2040 datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
- [Armv6-M Architecture Reference Manual](https://developer.arm.com/documentation/ddi0419/latest/)
