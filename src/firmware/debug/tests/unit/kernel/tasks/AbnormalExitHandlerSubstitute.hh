#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_ABNORMALEXITHANDLERSUBSTITUTE_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_ABNORMALEXITHANDLERSUBSTITUTE_HH
#include <exception>
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
			std::pair<Dummy<const Exception &>, bool>,
			std::pair<Dummy<const std::exception &>, bool>
		> onExceptionReturnValue;

		std::shared_ptr<CallRecorder<>> onUnknownExceptionCalls;
		bool onUnknownExceptionReturnValue;

	public:
		AbnormalExitHandlerSubstitute(
			std::shared_ptr<CallRecorder<const std::string>> onExceptionSmegExceptionOverloadCalls,
			std::shared_ptr<CallRecorder<const std::string>> onExceptionStandardExceptionOverloadCalls,
			std::shared_ptr<CallRecorder<>> onUnknownExceptionCalls) :
			onExceptionCalls(std::make_tuple(
				std::make_pair(dummy<const Exception &>(), onExceptionSmegExceptionOverloadCalls),
				std::make_pair(dummy<const std::exception &>(), onExceptionStandardExceptionOverloadCalls))),
			onExceptionReturnValue(std::make_tuple(
				std::make_pair(dummy<const Exception &>(), false),
				std::make_pair(dummy<const std::exception &>(), false))),
			onUnknownExceptionCalls(onUnknownExceptionCalls)
		{
		}

		template <typename T>
		auto &stubOnExceptionReturnValue(bool returnValue)
		{
			std::get<std::pair<Dummy<T>, bool>>(this->onExceptionReturnValue).second = returnValue;
			return *this;
		}

	private:
		template <typename T>
		bool _onException(T exception) noexcept
		{
			using CallRecorderPair = std::pair<Dummy<T>, std::shared_ptr<CallRecorder<const std::string>>>;
			std::get<CallRecorderPair>(this->onExceptionCalls).second->calledWith(exception.what());

			using ReturnValuePair = std::pair<Dummy<T>, bool>;
			return std::get<ReturnValuePair>(this->onExceptionReturnValue).second;
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

		auto &stubOnUnknownExceptionReturnValue(bool returnValue)
		{
			this->onUnknownExceptionReturnValue = returnValue;
			return *this;
		}

		bool onUnknownException(void) noexcept
		{
			this->onUnknownExceptionCalls->calledWith();
			return this->onUnknownExceptionReturnValue;
		}

		const CallRecorder<> &callsToOnUnknownException(void) noexcept { return *this->onUnknownExceptionCalls; }
	};
}

#endif
