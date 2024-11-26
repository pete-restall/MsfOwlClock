#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_DRIVERISRCONFIGSFROM_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_DRIVERISRCONFIGSFROM_HH
#include <tuple>

#include "../../tuples/TupleProjection.hh"
#include "IDriverConfig.hh"
#include "IHaveConfigForDrivers.hh"
#include "IHaveConfigForProvidedIsrs.hh"

namespace smeg::kernel::drivers::config
{
	using namespace smeg::kernel::tuples;

	template <typename TConfig>
	class DriverProvidedIsrConfigsFrom
	{
	public:
		using PerConfig = std::tuple<>;
	};

	template <>
	class DriverProvidedIsrConfigsFrom<std::tuple<>>
	{
	public:
		using PerConfig = std::tuple<>;
	};

	template <IHaveConfigForProvidedIsrs TDriverConfig>
	class DriverProvidedIsrConfigsFrom<TDriverConfig>
	{
	public:
		using PerConfig = TDriverConfig::ProvidedIsrs;
	};

	template <IDriverConfig... TDriverConfigs>
	class DriverProvidedIsrConfigsFrom<std::tuple<TDriverConfigs...>>
	{
	private:
		template <typename T>
		struct FromDriverConfig
		{
			using AsTuple = DriverProvidedIsrConfigsFrom<T>::PerConfig;
		};

	public:
		using PerConfig = TupleProjection<std::tuple<TDriverConfigs...>, FromDriverConfig>::Output;
	};

	template <IHaveConfigForDrivers TKernelConfig>
	class DriverProvidedIsrConfigsFrom<TKernelConfig>
	{
	private:
		template <typename T>
		struct FromKernelConfig
		{
			using AsTuple = DriverProvidedIsrConfigsFrom<T>::PerConfig;
		};

	public:
		using PerConfig = TupleProjection<typename TKernelConfig::Drivers, FromKernelConfig>::Output;
	};

	template <typename... TKernelConfigs>
	class DriverProvidedIsrConfigsFrom<std::tuple<TKernelConfigs...>>
	{
	private:
		template <typename T>
		struct FromKernelConfig
		{
			using AsTuple = DriverProvidedIsrConfigsFrom<T>::PerConfig;
		};

	public:
		using PerConfig = TupleProjection<std::tuple<TKernelConfigs...>, FromKernelConfig>::Output;
	};
}

#endif
