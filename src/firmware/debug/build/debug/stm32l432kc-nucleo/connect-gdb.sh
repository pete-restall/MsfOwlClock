#!/bin/bash
/opt/arm/local/cortex-m4f/bin/arm-none-eabi-gdb -q ../debug.elf <<EOF
target remote localhost:3333
monitor reset init
monitor arm semihosting enable
monitor targets
monitor stm32l4x mass_erase 0
monitor flash write_bank 0 ../debug.bin 0
monitor reset run
EOF
