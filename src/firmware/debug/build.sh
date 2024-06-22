#!/bin/bash
CC_PREFIX="/opt/arm/local/cortex-m4f/bin/arm-none-eabi-";
CC="${CC_PREFIX}g++";
CC_ARCHFLAGS="-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard";
CC_FLAGS="-Wall -pedantic -std=c++23 -g -O2 ${CC_ARCHFLAGS}";
OBJCOPY="${CC_PREFIX}objcopy";
MCU="stm32l432kc";
KERNEL_MCU_DIR="st/stm32/stm32l432kc";

if [ "x${1}" == "xclean" ]; then
	find ./ -iname "*.o" -exec rm \{\} \;
	find ./ -iname "*.a" -exec rm \{\} \;
	rm build/out/debug.{elf,hex,bin};
else
	pushd kernel;
	pushd crt0/mcu/arm/cortex/m4;
	${CC} ${CC_FLAGS} -c *.cc;
	popd;
	pushd "crt0/mcu/${KERNEL_MCU_DIR}";
	${CC} ${CC_FLAGS} -c *.cc;
	popd;

	${CC} ${CC_FLAGS} -c *.cc;
	popd;
	ar rcs build/out/libcrt0.a $(find kernel/crt0/ -name "*.o" );
	ar rcs build/out/libkernel.a $(find kernel/ -name "*.o" ! -wholename "kernel/crt0/*" );

	${CC} ${CC_FLAGS} -c *.cc;
	${CC} ${CC_FLAGS} -nostartfiles -Lbuild/out -o build/out/debug.elf *.o -lkernel -Wl,--whole-archive -lcrt0 -Wl,--no-whole-archive "-Tkernel/crt0/mcu/${KERNEL_MCU_DIR}/${MCU}.ld";
	${OBJCOPY} -O ihex build/out/debug.elf build/out/debug.hex;
	${OBJCOPY} -O binary build/out/debug.elf build/out/debug.bin;
fi;
