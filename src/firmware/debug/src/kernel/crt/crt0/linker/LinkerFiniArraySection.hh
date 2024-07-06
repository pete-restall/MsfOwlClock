#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERFINIARRAYSECTION_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERFINIARRAYSECTION_HH
#include <algorithm>
#include <concepts>
#include <iterator>

namespace smeg::kernel::crt::crt0::linker
{
	typedef void (*LinkerFiniArrayEntry)(void) noexcept;

	template<typename TPtr>
	concept ILinkerInitArrayEntryIterator =
		std::input_iterator<TPtr> &&
		std::is_same_v<std::iter_value_t<TPtr>, LinkerFiniArrayEntry>;

// TODO: MAKE A CONCEPT OF ILinkerAppFiniArray = INonConstFinalisable (basically INonConstInitialisable but different method name)
// THE ACTUAL LinkerAppFiniArray CAN THEN BE WRITTEN (TDD) WITH A finalise() METHOD THAT REVERSE-ITERATES A CONSTRUCTOR-PASSED SET OF FUNCTION POINTERS AND CALLS THEM - SIMILAR TO THE BSS AND DATA INITIALISATION
// THEN THE GENERIC LinkerMemoryMap(IInitialisableMemorySection...) WITH ITS OWN initialise() THAT JUST CALLS ChainedInitialisation.initialise()
// THEN REFACTOR EVERYTHING INTO MODULES TO REMOVE THE DEPENDENCY ON HEADERS, WHICH SHOULD ALSO ALLOW HIDING OF THE __linker_* CONSTANTS...
	class LinkerFiniArraySection
	{
public:
	};
}

#endif
