#ifndef __SMEG_KERNEL_DEFAULTPERCOREAPIFACTORY_HH
#define __SMEG_KERNEL_DEFAULTPERCOREAPIFACTORY_HH
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace smeg::kernel
{
	template <typename TConfig, std::size_t McuCoreId, typename... TApis>
	class DefaultPerCoreApiFactory
	{
	private:
		template <typename TApi>
		struct Ensure
		{
			using TupleOfExplicitlyRequiredApis = std::tuple<TApis...>;
			using CompilationErrorIfTupleDoesNotContainT = decltype(std::get<TApi>(TupleOfExplicitlyRequiredApis{}));

			static constexpr bool isExplicitlyRequiredForInjection = true;
		};

	public:
		template <typename TApi>
		constexpr auto createApi(void) const noexcept(std::is_nothrow_default_constructible_v<TApi>)
		{
			if constexpr (Ensure<TApi>::isExplicitlyRequiredForInjection)
				return TApi(); // TODO: If TApi() also requires APIs, then we'll need some way to descend into its dependencies for creation, too
		}
	};
}

#endif
