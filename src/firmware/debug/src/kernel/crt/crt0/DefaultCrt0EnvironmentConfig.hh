#ifndef __SMEG_KERNEL_CRT_CRT0_DEFAULTCRT0ENVIRONMENTCONFIG_HH
#define __SMEG_KERNEL_CRT_CRT0_DEFAULTCRT0ENVIRONMENTCONFIG_HH
#include <cstdint>
#include "../../KernelPerCoreInitialisationTask.hh" // TODO: WE ALSO NEED A TRANSLATION UNIT TO DEFINE THE STACKS FOR THE CRT0 (LIKE THE stubs/kernel-task-stacks) - WILL NEED TO BE IN THE MCU-SPECIFIC SECTION
#include "IsrStackMemorySection.hh"

namespace smeg::kernel::crt::crt0
{
	template <std::size_t NumberOfCores, std::size_t IsrStackNumberOfSlots>
	class DefaultCrt0EnvironmentConfig
	{
	private:
		static_assert(NumberOfCores > 0, "The microcontroller must have at least 1 core (CPU)");

		struct KernelInitialisation
		{
			using Types = std::tuple<KernelPerCoreInitialisationTask>;

			struct Stack
			{
				using MemorySection = IsrStackMemorySection;
				static constexpr auto numberOfSlots = IsrStackNumberOfSlots;
			};
		};

	public:
		using Tasks = std::tuple<KernelInitialisation>; // TODO: REPEAT THIS NumberOfCores TIMES; this can be TDD'd
	};
}

#endif
