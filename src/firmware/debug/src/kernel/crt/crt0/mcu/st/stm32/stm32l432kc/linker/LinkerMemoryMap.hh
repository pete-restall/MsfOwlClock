#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERMEMORYMAP_HH
#include "../../../../../linker/LinkerBssMemoryMap.hh"
#include "../../../../../linker/LinkerKernelInitArray.hh"
#include "../../../../../linker/LinkerKernelFiniArray.hh"
#include "LinkerKernelMemoryMap.hh"
#include "LinkerKernelSramBss.hh"
#include "LinkerKernelSramRetained16kBss.hh"

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	using namespace smeg::kernel::crt::crt0::linker;

	class LinkerMemoryMap
	{
public:
		LinkerKernelMemoryMap getLinkerMemoryMapForKernel(void) const
		{
			return LinkerKernelMemoryMap(
				LinkerKernelInitArray(),
				LinkerKernelFiniArray()
				LinkerBssMemoryMap(
					LinkerKernelSramRetained16kBss(),
					LinkerKernelSramBss())

				LinkerDataMemoryMap(
					LinkerKernelSramRetained16kData(),
					LinkerKernelSramData(),

				LinkerKernelStack()));
		}

#if false
		LinkerAppMemoryMap getLinkerMemoryMapForApp(void) const
		{
			return LinkerAppMemoryMap(
				LinkerAppInitArray(),
				LinkerAppFiniArray()
				LinkerBssMemoryMap(
					LinkerAppSramRetained16kBss(),
					LinkerAppSramBss())

				LinkerDataMemoryMap(
					LinkerAppSramRetained16kData(),
					LinkerAppSramData()));
		}
#endif
	};
}

#endif
