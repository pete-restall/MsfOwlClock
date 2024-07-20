#ifndef __SMEG_KERNEL_CHAINEDFINALISATION_HH
#define __SMEG_KERNEL_CHAINEDFINALISATION_HH
#include <tuple>
#include "IFinalisable.hh"

namespace smeg::kernel
{
	template <IFinalisable... TFinalisers>
	class ChainedFinalisation
	{
	private:
		std::tuple<TFinalisers...> finalisers;

	public:
		ChainedFinalisation(TFinalisers... sequenceOfFinalisers)
			: finalisers{sequenceOfFinalisers...}
		{
		}

		void finalise(void) const
		{
			auto callFinaliser = [](auto &...finalisable) { (finalisable.finalise(), ...); };
			std::apply(callFinaliser, this->finalisers);
		}

		void finalise(void)
		{
			auto callFinaliser = [](auto &...finalisable) { (finalisable.finalise(), ...); };
			std::apply(callFinaliser, this->finalisers);
		}
	};
}

#endif
