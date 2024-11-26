#ifndef __SMEG_KERNEL_KERNEL_MCUDEFS_HH
#define __SMEG_KERNEL_KERNEL_MCUDEFS_HH

#ifndef SMEG_MCU_RELATIVE_PATH
#error "SMEG_MCU_RELATIVE_PATH needs to be defined on the command-line; this is of a form similar to mcu/<architecture>/<mcu>"
#endif

#ifndef SMEG_MCU_RELATIVE_NAMESPACE
#error "SMEG_MCU_RELATIVE_NAMESPACE needs to be defined on the command-line; this is of a form similar to mcu::<architecture>::<mcu>"
#endif

#ifndef __SMEG_STRINGIFY
#define __SMEG_STRINGIFY(x) #x
#endif

#define _SMEG_MCU_RELATIVE_HEADER(headerPath, headerFilename) __SMEG_STRINGIFY(headerPath/headerFilename)
#define SMEG_MCU_RELATIVE_HEADER(headerFilename) _SMEG_MCU_RELATIVE_HEADER(SMEG_MCU_RELATIVE_PATH, headerFilename)

#define _SMEG_MCU_CRT0_HEADER(headerPath, headerFilename) __SMEG_STRINGIFY(kernel/crt/crt0/headerPath/headerFilename)
#define SMEG_MCU_CRT0_HEADER(headerFilename) _SMEG_MCU_CRT0_HEADER(SMEG_MCU_RELATIVE_PATH, headerFilename)

#define SMEG_MCU_CONFIG_HEADER_FOR_DRIVER_IMPLEMENTATIONS _SMEG_MCU_CRT0_HEADER(SMEG_MCU_RELATIVE_PATH, KernelConfigs.hh)
#define SMEG_MCU_KERNEL_CONFIGS_FOR_DRIVER_IMPLEMENTATIONS ::smeg::kernel::crt::crt0::SMEG_MCU_RELATIVE_NAMESPACE::KernelConfigs

#endif
