#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERINITARRAYSECTION_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERINITARRAYSECTION_HH
#include <algorithm>
#include <concepts>
#include <iterator>

namespace smeg::kernel::crt::crt0::linker
{
	typedef void (*LinkerInitArrayEntry)(void) noexcept;

	template<typename TPtr>
	concept ILinkerInitArrayEntryIterator =
		std::input_iterator<TPtr> &&
		std::is_same_v<std::iter_value_t<TPtr>, LinkerInitArrayEntry>;

	template<ILinkerInitArrayEntryIterator TPtr>
	class LinkerInitArraySection
	{
private:
		TPtr alignedStart;
		TPtr alignedPastEnd;

public:
		LinkerInitArraySection(TPtr start, TPtr pastEnd) :
			alignedStart(start),
			alignedPastEnd(pastEnd)
		{
		}

		void initialise(void) const noexcept
		{
			std::for_each(this->alignedStart, this->alignedPastEnd, [](auto &&init) noexcept { init(); });
		}
	};
}

#endif
