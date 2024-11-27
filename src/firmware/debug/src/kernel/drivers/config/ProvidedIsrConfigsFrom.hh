#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_PROVIDEDISRCONFIGSFROM_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_PROVIDEDISRCONFIGSFROM_HH
#include <tuple>

#include "../../tuples/TupleProjection.hh"
#include "IDriverConfig.hh"
#include "IHaveConfigForDrivers.hh"
#include "IHaveConfigForProvidedIsrs.hh"

namespace smeg::kernel::drivers::config
{
	using namespace smeg::kernel::tuples;

	template <typename TConfig>
	class ProvidedIsrConfigsFrom
	{
	public:
		using PerConfig = std::tuple<>;
	};

	template <>
	class ProvidedIsrConfigsFrom<std::tuple<>>
	{
	public:
		using PerConfig = std::tuple<>;
	};

	template <IHaveConfigForProvidedIsrs TDriverConfig>
	class ProvidedIsrConfigsFrom<TDriverConfig>
	{
	public:
		using PerConfig = TDriverConfig::ProvidedIsrs;
	};

	template <IDriverConfig... TDriverConfigs>
	class ProvidedIsrConfigsFrom<std::tuple<TDriverConfigs...>>
	{
	private:
		template <typename T>
		struct FromDriverConfig
		{
			using AsTuple = ProvidedIsrConfigsFrom<T>::PerConfig;
		};

	public:
		using PerConfig = TupleProjection<std::tuple<TDriverConfigs...>, FromDriverConfig>::Output;
	};

	template <IHaveConfigForDrivers TKernelConfig>
	class ProvidedIsrConfigsFrom<TKernelConfig>
	{
	private:
		template <typename T>
		struct FromKernelConfig
		{
			using AsTuple = ProvidedIsrConfigsFrom<T>::PerConfig;
		};

	public:
		using PerConfig = TupleProjection<typename TKernelConfig::Drivers, FromKernelConfig>::Output;
	};

	template <typename... TKernelConfigs>
	class ProvidedIsrConfigsFrom<std::tuple<TKernelConfigs...>>
	{
	private:
		template <typename T>
		struct FromKernelConfig
		{
			using AsTuple = ProvidedIsrConfigsFrom<T>::PerConfig;
		};

	public:
		using PerConfig = TupleProjection<std::tuple<TKernelConfigs...>, FromKernelConfig>::Output;
	};
}

#endif
