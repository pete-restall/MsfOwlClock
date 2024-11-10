#ifndef __SMEG_KERNEL_TASKS_DEFAULTAPIFACTORY_HH
#define __SMEG_KERNEL_TASKS_DEFAULTAPIFACTORY_HH
#include <tuple>

namespace smeg::kernel::tasks
{
	template <typename... TApis>
	class DefaultApiFactory
	{
	private:
		template <typename TApi>
		struct Ensure
		{
			using TupleOfExplicitlyRequiredApis = std::tuple<TApis...>;
			using CompilationErrorIfTupleDoesNotContainT = decltype(std::get<TApi>(TupleOfExplicitlyRequiredApis{}));

			static constexpr bool isExplicitlyRequiredByTask = true;
		};

	public:
		template <typename TApi>
		constexpr auto create(void) const
		{
			if constexpr (Ensure<TApi>::isExplicitlyRequiredByTask)
				return TApi();
		}
	};
}

#endif
