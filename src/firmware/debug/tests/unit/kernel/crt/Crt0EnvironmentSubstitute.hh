#ifndef __SMEG_TESTS_UNIT_KERNEL_CRT_CRT0ENVIRONMENTSUBSTITUTE_HH
#define __SMEG_TESTS_UNIT_KERNEL_CRT_CRT0ENVIRONMENTSUBSTITUTE_HH
#include <concepts>
#include <tuple>

#include "../tasks/config/DummyTaskConfig.hh"
#include "BootloaderTestDoubles.hh"
#include "LinkerMemoryMapTestDoubles.hh"

namespace smeg::tests::unit::kernel::crt
{
	using namespace smeg::tests::unit::kernel::tasks::config;

	template <
		typename TLinkerMemoryMap = LinkerMemoryMapTestDoubles,
		typename TBootloader = BootloaderTestDoubles,
		typename TTasks = std::tuple<DummyTaskConfig<1>>>
	class Crt0EnvironmentSubstitute
	{
	private:
		TLinkerMemoryMap linkerMemoryMapOrFactory;
		TBootloader bootloaderOrFactory;

	public:
		Crt0EnvironmentSubstitute(
			TLinkerMemoryMap linkerMemoryMapOrFactory,
			TBootloader bootloaderOrFactory) :
			linkerMemoryMapOrFactory(linkerMemoryMapOrFactory),
			bootloaderOrFactory(bootloaderOrFactory)
		{
		}

		struct Config
		{
			using Tasks = TTasks;
		};

		auto getLinkerMemoryMap(void) const
		{
			if constexpr (std::same_as<TLinkerMemoryMap, LinkerMemoryMapTestDoubles>)
				return this->linkerMemoryMapOrFactory.dummy();
			else
				return this->linkerMemoryMapOrFactory;
		}

		template <typename T>
		auto withLinkerMemoryMap(T linkerMemoryMap) const
		{
			return Crt0EnvironmentSubstitute<T, TBootloader, TTasks>(linkerMemoryMap, this->bootloaderOrFactory);
		}

		auto getBootloader(void) const
		{
			if constexpr (std::same_as<TBootloader, BootloaderTestDoubles>)
				return this->bootloaderOrFactory.dummy();
			else
				return this->bootloaderOrFactory;
		}

		template <typename T>
		auto withBootloader(T bootloader) const
		{
			return Crt0EnvironmentSubstitute<TLinkerMemoryMap, T, TTasks>(this->linkerMemoryMapOrFactory, bootloader);
		}
	};
}

#endif
