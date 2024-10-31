#ifndef __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERKERNELMEMORYMAPSUBSTITUTE_HH
#define __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERKERNELMEMORYMAPSUBSTITUTE_HH
#include <concepts>

#include "../FinalisableTestDoubles.hh"
#include "../InitialisableTestDoubles.hh"

namespace smeg::tests::unit::kernel::crt
{
	template <
		typename TRamSectionsInitialiser = InitialisableTestDoubles,
		typename TCodeSectionsInitialiser = InitialisableTestDoubles,
		typename TCodeSectionsFinaliser = FinalisableTestDoubles>
	class LinkerKernelMemoryMapSubstitute
	{
	private:
		TRamSectionsInitialiser ramSectionsInitialisableOrFactory;
		TCodeSectionsInitialiser codeSectionsInitialisableOrFactory;
		TCodeSectionsFinaliser codeSectionsFinalisableOrFactory;

	public:
		LinkerKernelMemoryMapSubstitute(
			TRamSectionsInitialiser ramSectionsInitialisableOrFactory,
			TCodeSectionsInitialiser codeSectionsInitialisableOrFactory,
			TCodeSectionsFinaliser codeSectionsFinalisableOrFactory) :
			ramSectionsInitialisableOrFactory(ramSectionsInitialisableOrFactory),
			codeSectionsInitialisableOrFactory(codeSectionsInitialisableOrFactory),
			codeSectionsFinalisableOrFactory(codeSectionsFinalisableOrFactory)
		{
		}

		auto getInitialiserForRamSections(void) const
		{
			if constexpr (std::same_as<TRamSectionsInitialiser, InitialisableTestDoubles>)
				return this->ramSectionsInitialisableOrFactory.dummy();
			else
				return this->ramSectionsInitialisableOrFactory;
		}

		template <typename T>
		auto withInitialiserForRamSections(T initialiser) const
		{
			return LinkerKernelMemoryMapSubstitute<T, TCodeSectionsInitialiser, TCodeSectionsFinaliser>(
				initialiser,
				this->codeSectionsInitialisableOrFactory,
				this->codeSectionsFinalisableOrFactory);
		}

		auto getInitialiserForCodeSections(void) const
		{
			if constexpr (std::same_as<TCodeSectionsInitialiser, InitialisableTestDoubles>)
				return this->codeSectionsInitialisableOrFactory.dummy();
			else
				return this->codeSectionsInitialisableOrFactory;
		}

		template <typename T>
		auto withInitialiserForCodeSections(T initialiser) const
		{
			return LinkerKernelMemoryMapSubstitute<TRamSectionsInitialiser, T, TCodeSectionsFinaliser>(
				this->ramSectionsInitialisableOrFactory,
				initialiser,
				this->codeSectionsFinalisableOrFactory);
		}

		auto getFinaliserForCodeSections(void) const
		{
			if constexpr (std::same_as<TCodeSectionsFinaliser, FinalisableTestDoubles>)
				return this->codeSectionsFinalisableOrFactory.dummy();
			else
				return this->codeSectionsFinalisableOrFactory;
		}

		template <typename T>
		auto withFinaliserForCodeSections(T finaliser) const
		{
			return LinkerKernelMemoryMapSubstitute<TRamSectionsInitialiser, TCodeSectionsInitialiser, T>(
				this->ramSectionsInitialisableOrFactory,
				this->codeSectionsInitialisableOrFactory,
				finaliser);
		}
	};
}

#endif
