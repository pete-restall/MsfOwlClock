#include "Crt0KernelConfig.hh"
#include "KernelConfigs.hh"

//
// TODO: This whole concept of 'crt0-task-stacks', 'kernel-task-stacks', etc. can also be refined so that there is only a single file for these.
// The idea is to use the same concept as Drivers providing APIs, ISRs and Syscalls - we can export MemoryRegions from the Configs.  The configs
// will basically need to look something like:
//
//   struct SpecialMemoryRegionConfig
//   {
//       using Type = SpecialMemoryRegion;
//       static constexpr auto linkerSectionName = ".kernel.whatever.special.stack";
//   };
//
using namespace smeg::kernel::crt::crt0::mcu::st::stm32;
using Crt0KernelConfig = stm32l432kc::Crt0KernelConfig<stm32l432kc::KernelConfigs>;

#include "../../../../crt0-task-stacks.cc"
