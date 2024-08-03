#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_ABNORMALEXITHANDLERSUBSTITUTE_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_ABNORMALEXITHANDLERSUBSTITUTE_HH
#include <exception>
#include <list>
#include <memory>
#include <string>
#include <tuple>
#include <utility>

#include "kernel/Exception.hh"

#include "../../CallRecorder.hh"

namespace smeg::tests::unit::kernel::tasks
{
	using namespace smeg::kernel;

	class AbnormalExitHandlerSubstitute
	{
	private:
		template <typename T> struct Dummy { };

		template <typename T>
		static auto dummy(void) { return Dummy<T>{}; }

		std::tuple<
			std::pair<Dummy<const Exception &>, std::shared_ptr<CallRecorder<const std::string>>>,
			std::pair<Dummy<const std::exception &>, std::shared_ptr<CallRecorder<const std::string>>>
		> onExceptionCalls;

		std::tuple<
			std::pair<Dummy<const Exception &>, std::list<bool>>,
			std::pair<Dummy<const std::exception &>, std::list<bool>>
		> onExceptionReturnValues;

		std::shared_ptr<CallRecorder<>> onUnknownExceptionCalls;
		std::list<bool> onUnknownExceptionReturnValues;

	public:
		AbnormalExitHandlerSubstitute(
			std::shared_ptr<CallRecorder<const std::string>> onExceptionSmegExceptionOverloadCalls,
			std::shared_ptr<CallRecorder<const std::string>> onExceptionStandardExceptionOverloadCalls,
			std::shared_ptr<CallRecorder<>> onUnknownExceptionCalls) :
			onExceptionCalls(std::make_tuple(
				std::make_pair(dummy<const Exception &>(), onExceptionSmegExceptionOverloadCalls),
				std::make_pair(dummy<const std::exception &>(), onExceptionStandardExceptionOverloadCalls))),
			onExceptionReturnValues(std::make_tuple(
				std::make_pair(dummy<const Exception &>(), std::list<bool>{}),
				std::make_pair(dummy<const std::exception &>(), std::list<bool>{}))),
			onUnknownExceptionCalls(onUnknownExceptionCalls)
		{
		}

		template <typename T>
		auto &stubOnExceptionReturnValue(bool returnValue, int numberOfTimes = 1)
		{
			auto &returnValues(std::get<std::pair<Dummy<T>, std::list<bool>>>(this->onExceptionReturnValues).second);
			for (int i = 0; i < numberOfTimes; i++)
				returnValues.push_back(returnValue);

			return *this;
		}

	private:
		template <typename T>
		bool _onException(T exception) noexcept
		{
			using CallRecorderPair = std::pair<Dummy<T>, std::shared_ptr<CallRecorder<const std::string>>>;
			std::get<CallRecorderPair>(this->onExceptionCalls).second->calledWith(exception.what());

			using ReturnValuePair = std::pair<Dummy<T>, std::list<bool>>;
			auto &returnValues(std::get<ReturnValuePair>(this->onExceptionReturnValues).second);

			if (returnValues.empty())
				return false;

			bool returnValue(returnValues.front());
			returnValues.pop_front();
			if (returnValues.empty())
				returnValues.push_back(returnValue);

			return returnValue;
		}

	public:
		bool onException(const Exception &exception) noexcept
		{
			return this->_onException<const Exception &>(exception);
		}

		bool onException(const std::exception &exception) noexcept
		{
			return this->_onException<const std::exception &>(exception);
		}

		template <typename T>
		const CallRecorder<const std::string> &callsToOnException(void) noexcept
		{
			using CallRecorderPair = std::pair<Dummy<T>, std::shared_ptr<CallRecorder<const std::string>>>;
			return *std::get<CallRecorderPair>(this->onExceptionCalls).second;
		}

		auto &stubOnUnknownExceptionReturnValue(bool returnValue, int numberOfTimes = 1)
		{
			for (int i = 0; i < numberOfTimes; i++)
				this->onUnknownExceptionReturnValues.push_back(returnValue);

			return *this;
		}

		bool onUnknownException(void) noexcept
		{
			this->onUnknownExceptionCalls->calledWith();

			if (this->onUnknownExceptionReturnValues.empty())
				return false;

			bool returnValue(this->onUnknownExceptionReturnValues.front());
			this->onUnknownExceptionReturnValues.pop_front();
			if (this->onUnknownExceptionReturnValues.empty())
				this->onUnknownExceptionReturnValues.push_back(returnValue);

			return returnValue;
		}

		const CallRecorder<> &callsToOnUnknownException(void) noexcept { return *this->onUnknownExceptionCalls; }
	};
}

#endif
