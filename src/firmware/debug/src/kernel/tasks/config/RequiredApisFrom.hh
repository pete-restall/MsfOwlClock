#ifndef __SMEG_KERNEL_TASKS_CONFIG_REQUIREDAPISFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_REQUIREDAPISFROM_HH
#include <tuple>

#include "../../tuples/TupleProjection.hh"
#include "../../tuples/Unique.hh"
#include "../AppToDriverApis.hh"
#include "../DriverToDriverApis.hh"
#include "../DriverToKernelApis.hh"
#include "../ITask.hh"
#include "IHaveConfigForTasks.hh"
#include "ITaskConfig.hh"

namespace smeg::kernel::tasks::config
{
	using namespace smeg::kernel::tuples;

	template <template <typename...> typename TRequiredApis, typename... T>
	class RequiredApisFrom;

	template <template <typename...> typename TRequiredApis, ITaskWithoutRequiredApis TTask>
	class RequiredApisFrom<TRequiredApis, TTask>
	{
	public:
		using Types = std::tuple<>;
	};

	template <template <typename...> typename TRequiredApis, ITaskWithAnyRequiredApisExcept<TRequiredApis> TTask>
	class RequiredApisFrom<TRequiredApis, TTask>
	{
	public:
		using Types = std::tuple<>;
	};

	template <template <typename...> typename TRequiredApis, ITaskWithRequiredApis<TRequiredApis> TTask>
	class RequiredApisFrom<TRequiredApis, TTask>
	{
	private:
		template <typename... TApis>
		struct From;

		template <typename... TApis>
		struct From<TRequiredApis<TApis...>>
		{
			using AsTuple = std::tuple<TApis...>;
		};

	public:
		using Types = Unique<typename From<typename TTask::RequiredApis>::AsTuple>;
	};

	template <template <typename...> typename TRequiredApis, ISimpleTaskConfig TTaskConfig>
	class RequiredApisFrom<TRequiredApis, TTaskConfig>
	{
	public:
		using Types = Unique<typename RequiredApisFrom<TRequiredApis, typename TTaskConfig::Type>::Types>;
	};

	template <template <typename...> typename TRequiredApis, ISimpleOverlaidTasksConfig TTaskConfig>
	class RequiredApisFrom<TRequiredApis, TTaskConfig>
	{
	private:
		template <ITask TTask>
		struct FromTypes
		{
			using AsTuple = typename RequiredApisFrom<TRequiredApis, TTask>::Types;
		};

	public:
		using Types = Unique<typename TupleProjection<typename TTaskConfig::Types, FromTypes>::Output>;
	};

	template <template <typename...> typename TRequiredApis, IConfiguredOverlaidTasksConfig TTaskConfig>
	class RequiredApisFrom<TRequiredApis, TTaskConfig>
	{
	private:
		template <IOverlaidTaskConfig TConfig>
		struct FromConfigs
		{
			using AsTuple = typename RequiredApisFrom<TRequiredApis, typename TConfig::Type>::Types;
		};

	public:
		using Types = Unique<typename TupleProjection<typename TTaskConfig::Configs, FromConfigs>::Output>;
	};

	template <template <typename...> typename TRequiredApis, IHaveConfigForTasks TConfig>
	class RequiredApisFrom<TRequiredApis, TConfig>
	{
	private:
		template <ITaskConfig TTaskConfig>
		struct FromTaskConfigs
		{
			using AsTuple = typename RequiredApisFrom<TRequiredApis, TTaskConfig>::Types;
		};

	public:
		using Types = Unique<typename TupleProjection<typename TConfig::Tasks, FromTaskConfigs>::Output>;
	};

	template <typename T>
	using RequiredAppToDriverApisFrom = RequiredApisFrom<AppToDriverApis, T>;

	template <typename T>
	using RequiredDriverToDriverApisFrom = RequiredApisFrom<DriverToDriverApis, T>;

	template <typename T>
	using RequiredDriverToKernelApisFrom = RequiredApisFrom<DriverToKernelApis, T>;
}

#endif
