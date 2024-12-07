#ifndef __SMEG_KERNEL_CRT_CRT0_DEFAULTCRT0KERNELCONFIG_HH
#define __SMEG_KERNEL_CRT_CRT0_DEFAULTCRT0KERNELCONFIG_HH
#include <array>
#include <cstddef>
#include <tuple>

#include "../../IMcuCoreTraits.hh"
#include "../../KernelPerCoreInitialisationTask.hh"
#include "../../drivers/config/ITupleOfDriverConfigs.hh"

namespace smeg::kernel::crt::crt0
{
	using namespace smeg::kernel::drivers::config;

	template <IMcuCoreTraits TMcuCoreTraits, std::size_t IsrStackNumberOfSlots, typename TMemorySection, ITupleOfDriverConfigs TDriverConfigs>
	class DefaultCrt0KernelConfig
	{
	private:
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
		using McuCoreTraits = TMcuCoreTraits;
		using Drivers = TDriverConfigs;
		using Tasks = std::array<KernelInitialisation, TMcuCoreTraits::numberOfMcuCores>; // TODO: Maybe we need to parameterise KernelInitialisation<CoreId> so we can have a task-based SchedulingConfig.CoreAffinity and then the Entrypoint can determine which core it is running on and execute the appropriate core-specific task.
	};
}

#endif
