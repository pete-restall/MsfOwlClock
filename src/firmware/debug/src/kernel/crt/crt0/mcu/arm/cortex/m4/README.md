# ARM Cortex M4* Implementation Details

## Interrupts
Microcontrollers based on ARM M4* profiles have a set of 15 common, MCU-agnostic interrupts that have been defined by ARM, as well as peripheral interrupts that are MCU- and manufacturer-specific.  The vector table for all of the ARM interrupts is in `IsrVectorTable.cc`; there will be a corresponding table of peripheral interrupts provided by each of the specific M4*-based implementations.  It is the job of the linker script to merge both tables.

Interrupt Service Routines (ISRs) are provided by the MCU-specific parts of Drivers and are wired into the vector table based on the value of their configured `irq` (`static constexpr`) member.  Only drivers that are required / in-use will have their ISRs placed into the vector table.  There are two default implementations provided, `UnhandledIsr` and `ReservedIsr`, that are placed into the vector table if there is none provided by a driver for the given IRQ.

There is one special, non-driver, non-unhandled, non-reserved ISR handler for ARM Cortex M4* implementations, which is the `_resetHandler`.  This is the entrypoint after reset and is provided by each of the MCU-specific implementations.

## Syscalls
Kernel 'syscalls' are implemented with the `svc` opcode, which in turn is handled by Interrupt Service Routine (ISR) with IRQ 11 (vector 10).  An implementation of this ISR is provided by the `syscall` driver found in `kernel/drivers/kernel/syscall`, along with MCU-agnostic APIs to abstract the details from other drivers.  The 8-bit operand to the `svc` opcode is unused at this time and set to `0x00`; the only way to use it from within the ISR is by reading and parsing the opcode at runtime meaning it is of limited utility due to the inefficiency and complexity.  Instead, register `r7` is used for the purpose of identifying the required operation.

Register `r7` contains the ID of the system call as that is the defacto standard for ARM-based processors due to various historical factors, instruction encoding and ABI compatibility.  The ISR will use `r7` to look up and dispatch to an appropriate handler.  The number itself is simply an implementation detail of the ARM mechanism, used only as a unique token for identifying what operation the caller has requested.  It is determined at compile-time from the registered syscall handlers and not used by the kernel iteself.  As such, do not rely on this number being any particular value or even constant across compilations, which is why it needs to be determined via the `TSyscallFor<T>::id` template parameter.

A syscall always havs one parameter, which is a pointer to a data structure somewhere in the Task's address space.  This structure can be either `const` or non-`const` depending on the requirements of the handler.  The argument is stored in register `r0` which fits nicely with the ARM ABI and so the optimiser / register allocator should be able to use this nicely.

The above mechanism for invoking syscalls (ie. adapting the kernel 'syscall' concept to the ARM `svc` opcode) is encapsulated by the `SyscallPrimitive` class, in turn used directly by the public `SyscallApi`.
