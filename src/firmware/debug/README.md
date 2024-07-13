TODO - Make notes on architecture (high-level overviews), building, using, etc.  This README is currently just an ad-hoc collection of notes.

The lowest level consists of three libraries:
1. `libcrt0` - microcontroller-specific bootstrapping and linker scripts.  Named `crt0` because GCC expects a translation unit called `crt0.o` somewhere in the link files; requires `whole-archive` linking so do not include anything more than 100% necessary in this library.  The dependencies point to `libkernel`.
2. `libcrt` - generic `picolibc`, `libstdc++`, `libsupc++` glue not tied to a specific microcontroller.  Requires `whole-archive` linking so do not include anything more than 100% necessary in this library.  The dependencies point to `libkernel`.
3. `bare-metal` - standalone register maps and utilities for the specific microcontroller target; no dependencies since dependents point towards this.

The next level is the kernel, `libkernel`.

---

To build, grab my (DebugDue fork)[https://github.com/pete-restall/DebugDue] to create the ARM Cortex M4F cross-compiler and toolchain.  That can be built using something like:
```
$ make download-tarballs-from-internet

$ sudo make CROSS_TOOLCHAIN_DIR=/opt/arm/local/cortex-m4f CROSS_TOOLCHAIN_BUILD_DIR=/tmp/cortex-m4f-gcc-test TOOLCHAIN_TARGET_CPU=cortex-m4f --no-builtin-variables --warn-undefined-variables --output-sync=recurse -j 8 all
```
The target CPU and toolchain triplet are actually hacked into the Makefile, so make sure they're `cortex-m4f` and `arm-none-eabi`, respectively, before building.

A PIC32MM (MIPS) cross-toolchain can also be built using `pic32mm` as a target and `mips-mti-elf` as the triplet:
```
$ make download-tarballs-from-internet

$ sudo make CROSS_TOOLCHAIN_DIR=/opt/microchip/local/pic32mm CROSS_TOOLCHAIN_BUILD_DIR=/tmp/pic32mm-gcc-test TOOLCHAIN_TARGET_CPU=pic32mm --no-builtin-variables --warn-undefined-variables --output-sync=recurse -j 8 all
```

---

Make sure `OpenOCD` is installed for debugging; the `cortex-debug` extension to VSCode can be used to debug / step through an attached device via `gdb`.

---

Install the `meson` build system:
```
$ pip install --user meson
```

Setup the build system:
```
$ meson setup build/meson/out/native --native-file build/meson/common.ini --native-file build/meson/native.ini
$ meson setup build/meson/out/stm32l432kc --cross-file build/meson/common.ini --cross-file build/meson/stm32l432kc.ini
$ meson setup build/meson/out/pic32cx1025sg41100 --cross-file build/meson/common.ini --cross-file build/meson/pic32cx1025sg41100.ini
```

To build, use something like:
```
$ meson compile -C build/meson/out/stm32l432kc
```

---

Install the `mettle` testing framework; see the [installation instructions](https://github.com/jimporter/mettle/blob/master/doc/install.md).
Clone the repository and then do something like:
```
$ pip install --user bfg9000
$ 9k build/
$ cd build
$ ninja
$ sudo ninja install
```

It needs to be accessible via `pkg-config`, so make sure `PKG_CONFIG_PATH` has been set accordingly.

---

Spent a fruitless few days trying to convert the headers into modules but the toolchain support isn't quite there yet so reverted.  Learnings / problems not solved:
* Simply using `-std=c++23` is not enough, compilation and linking also requires `-fmodules-ts`.
* Ninja can't figure out the dependencies and ordering (note - required GCC flag `-fdeps-format=p1689r5`, from GCC 14 onwards, prevents the `inputs may not also have inputs` error) and so the build has to be run several times in succession to get them all built.
* Cryptic or opaque errors when dependencies were missing.
* Visibility and reachability doesn't seem to be correct in the GCC implementation - in fact this is one area that the GCC release notes point out as incomplete.
* Problems with concepts; the header-based concept constraints on template parameters seem to work, but when converted to modules, they do not (GCC complains about such things as `T` not conforming to `destructible` when constraining against `input_iterator`, but `destructible` does not appear to be a sub-constraint of `input_iterator` according to cppreference.com).
* System headers need to be specially built upfront prior to using them, which is also difficult to work into Meson.  Basically the following needs to be run (the list of headers):
```
$ pushd build/meson/out/stm32l432kc
$ /opt/arm/local/cortex-m4f/bin/arm-none-eabi-g++ -std=c++23 -fno-rtti -O2 -g -fmodules-ts -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -xc++-system-header algorithm cstdint concepts iterator tuple -c
$ popd
```
