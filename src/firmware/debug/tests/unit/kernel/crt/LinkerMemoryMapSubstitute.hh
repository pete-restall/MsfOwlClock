#ifndef __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERMEMORYMAPSUBSTITUTE_HH
#define __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERMEMORYMAPSUBSTITUTE_HH
#include <concepts>

#include "LinkerAppMemoryMapTestDoubles.hh"
#include "LinkerKernelMemoryMapTestDoubles.hh"

namespace smeg::tests::unit::kernel::crt
{
	template <
		typename TKernelMemoryMap = LinkerKernelMemoryMapTestDoubles,
		typename TAppMemoryMap = LinkerAppMemoryMapTestDoubles>
	class LinkerMemoryMapSubstitute
	{
	private:
		TKernelMemoryMap kernelMemoryMapOrFactory;
		TAppMemoryMap appMemoryMapOrFactory;

	public:
		LinkerMemoryMapSubstitute(
			TKernelMemoryMap kernelMemoryMapOrFactory,
			TAppMemoryMap appMemoryMapOrFactory) :
			kernelMemoryMapOrFactory(kernelMemoryMapOrFactory),
			appMemoryMapOrFactory(appMemoryMapOrFactory)
		{
		}

		auto getLinkerMemoryMapForKernel(void) const
		{
			if constexpr (std::same_as<TKernelMemoryMap, LinkerKernelMemoryMapTestDoubles>)
				return this->kernelMemoryMapOrFactory.dummy();
			else
				return this->kernelMemoryMapOrFactory;
		}

		template <typename T>
		auto withLinkerMemoryMapForKernel(T memoryMap) const
		{
			return LinkerMemoryMapSubstitute<T, TAppMemoryMap>(
				memoryMap,
				this->appMemoryMapOrFactory);
		}

		auto getLinkerMemoryMapForApp(void) const
		{
			if constexpr (std::same_as<TAppMemoryMap, LinkerAppMemoryMapTestDoubles>)
				return this->appMemoryMapOrFactory.dummy();
			else
				return this->appMemoryMapOrFactory;
		}

		template <typename T>
		auto withLinkerMemoryMapForApp(T memoryMap) const
		{
			return LinkerMemoryMapSubstitute<TKernelMemoryMap, T>(
				this->kernelMemoryMapOrFactory,
				memoryMap);
		}
	};
}

#endif
