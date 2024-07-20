#ifndef __SMEG_KERNEL_CHAINEDINITIALISATION_HH
#define __SMEG_KERNEL_CHAINEDINITIALISATION_HH
#include <tuple>
#include "IInitialisable.hh"

namespace smeg::kernel
{
	template <IInitialisable... TInitialisers>
	class ChainedInitialisation
	{
	private:
		std::tuple<TInitialisers...> initialisers;

	public:
		ChainedInitialisation(TInitialisers... sequenceOfInitialisers)
			: initialisers{sequenceOfInitialisers...}
		{
		}

		void initialise(void) const
		{
			auto callInitialiser = [](auto &...initialisable) { (initialisable.initialise(), ...); };
			std::apply(callInitialiser, this->initialisers);
		}

		void initialise(void)
		{
			auto callInitialiser = [](auto &...initialisable) { (initialisable.initialise(), ...); };
			std::apply(callInitialiser, this->initialisers);
		}
	};
}

#endif
