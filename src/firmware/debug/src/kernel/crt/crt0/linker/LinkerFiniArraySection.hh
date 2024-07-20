#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERFINIARRAYSECTION_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERFINIARRAYSECTION_HH
#include <algorithm>
#include <concepts>
#include <iterator>

namespace smeg::kernel::crt::crt0::linker
{
	using LinkerFiniArrayEntry = void (*)(void) noexcept;

	template <typename TPtr>
	concept ILinkerFiniArrayEntryIterator =
		std::input_iterator<TPtr> &&
		std::is_same_v<std::iter_value_t<TPtr>, LinkerFiniArrayEntry>;

	template <ILinkerFiniArrayEntryIterator TPtr>
	class LinkerFiniArraySection
	{
	private:
		const TPtr alignedStart;
		const TPtr alignedPastEnd;

	public:
		LinkerFiniArraySection(const TPtr start, const TPtr pastEnd) :
			alignedStart(start),
			alignedPastEnd(pastEnd)
		{
		}

		void finalise(void) const noexcept
		{
			std::for_each(
				std::reverse_iterator(this->alignedPastEnd),
				std::reverse_iterator(this->alignedStart),
				[](auto &&init) noexcept { init(); });
		}
	};
}

#endif
