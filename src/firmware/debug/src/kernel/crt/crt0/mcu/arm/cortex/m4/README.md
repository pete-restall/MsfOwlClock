# ARM Cortex M4* Implementation Details
TODO

## Interrupts
TODO

## Syscalls
Kernel 'syscalls' are implemented with the `svc` opcode, which in turn is handled by the `Isrs::svCall()` Interrupt Service Routine (ISR).  The 8-bit operand is unused at this time and set to `0x00`; the only way to use it from within the ISR is by reading and parsing the opcode at runtime meaning it is of limited utility due to the inefficiency and complexity.  Instead, register `r7` is used for the purpose of identifying the required operation.

Register `r7` contains the ID of the system call as it is the defacto standard for ARM-based processors due to various historical factors, instruction encoding and ABI compatibility.  The ISR will use `r7` to look up and dispatch to an appropriate handler.  The number itself is simply an implementation detail of the ARM mechanism, used only as a unique token for identifying what operation the caller has requested.  It is determined at compile-time from the registered syscall handlers and not used by the kernel iteself.  As such, do not rely on this number being any particular value or even constant across compilations, which is why it needs to be determined via the `TSyscallFor<T>::id` template parameter.

A syscall can have zero or one parameters.  For syscalls with a single parameter, the register `r0` contains the argument.  This fits nicely with the ARM ABI and so the optimiser / register allocator should be able to use this nicely.

The argument in `r0` can either be interpreted as either an unsigned 32-bit integer passed by value, `std::uint32_t`, or a 32-bit pointer to a struct for richer and / or more numerous argument passing.  The struct can be either `const` or non-`const` depending on the requirements of the handler.

The above mechanism for invoking syscalls (ie. adapting the kernel 'syscall' concept to the ARM `svc` opcode) is encapsulated by the `SyscallPrimitive` class.
