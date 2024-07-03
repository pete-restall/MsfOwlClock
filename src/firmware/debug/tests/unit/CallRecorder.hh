#ifndef __SMEG_TESTS_UNIT_CALLRECORDER_HH
#define __SMEG_TESTS_UNIT_CALLRECORDER_HH
#include <atomic>
#include <ranges>
#include <tuple>
#include <vector>

namespace smeg::tests::unit
{
	template<typename... TArgs>
	class CallRecorder
	{
		public: typedef std::vector<int>::size_type CallCountInt;

private:
		std::atomic<CallCountInt> &callSequence;
		std::vector<std::tuple<CallCountInt, TArgs...>> calls;

public:
		CallRecorder(std::atomic<CallCountInt> &callSequenceCounter) noexcept :
			callSequence(callSequenceCounter),
			calls(std::vector<std::tuple<CallCountInt, TArgs...>>())
		{
		}

		void calledWith(TArgs... args)
		{
			this->calls.push_back(std::make_tuple(++this->callSequence, args...));
		}

		CallCountInt count(void) const
		{
			return this->calls.size();
		}

		auto getCallSequences(void) const
		{
			return this->calls | std::views::transform([](auto &&x) noexcept { return std::get<0>(x); });
		}
	};
}

#endif
