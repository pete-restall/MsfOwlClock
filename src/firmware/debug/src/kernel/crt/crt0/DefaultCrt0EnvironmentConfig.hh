#ifndef __SMEG_KERNEL_CRT_CRT0_DEFAULTCRT0ENVIRONMENTCONFIG_HH
#define __SMEG_KERNEL_CRT_CRT0_DEFAULTCRT0ENVIRONMENTCONFIG_HH
#include <cstdint>
#include "../../KernelPerCoreInitialisationTask.hh"
#include "IsrStackMemorySection.hh"

namespace smeg::kernel::crt::crt0
{
	template <std::size_t NumberOfCores, std::size_t IsrStackNumberOfSlots, typename TMemorySection = IsrStackMemorySection>
	class DefaultCrt0EnvironmentConfig
	{
	private:
		static_assert(NumberOfCores > 0, "The microcontroller must have at least 1 core (CPU)");

		struct KernelInitialisation
		{
			using Types = std::tuple<KernelPerCoreInitialisationTask>;

			struct Stack
			{
				using MemorySection = TMemorySection;
				static constexpr auto numberOfSlots = IsrStackNumberOfSlots;
			};
		};

	public:
		using Tasks = std::array<KernelInitialisation, NumberOfCores>;
	};
}

#endif
