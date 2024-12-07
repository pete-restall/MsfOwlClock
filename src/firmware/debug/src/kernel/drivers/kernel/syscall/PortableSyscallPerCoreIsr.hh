#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISR_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISR_HH
#include <cstdint>

#include "kernel/IHandleSyscall.hh"

namespace smeg::kernel::drivers::kernel::syscall
{
	using namespace smeg::kernel;

	template <typename TSyscallHandlers>
	class PortableSyscallPerCoreIsr;

	template <IHandleSyscallWithAnyArg... TSyscallHandlers>
	class PortableSyscallPerCoreIsr<std::tuple<TSyscallHandlers...>>
	{
	public:
		void onInterrupt(void *argsPtr, std::uint32_t id) noexcept
		{
		// argsPtr will contain a pointer to the TSyscall instance; this should be checked prior to dispatch to ensure it is within the current task's stack /
		// memory area; this test also includes the size of the structure (but by necessity, this method cannot extend to validating the contents).  Basically
		// encapsulate this in some form of 'currentTaskControlBlock.isValidUserspaceMemoryBlock(argsPtr, sizeOfArgsInBytes)'.

		// id will contain the ID of the Syscall, which is used for dispatching to the relevant Syscall Handler - can also be used for type size lookup.

		// exceptions, invalid syscall IDs and memory access errors should result in a call to something that logs and terminates the task (a 'default handler' ?)

		// each core has its own tuple of Syscall Handlers for holding processor-specific state.

		// all of this functionality can be written in a platform-agnostic (ie. easily tested) way.

/*
Thoughts on dispatching Syscalls to handlers in a generic fashion, although this includes the no-arg and integer-arg variants which are no longer desired:

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>

template <typename T>
concept IIsrContext = true;

struct IsrContext
{

//	IsrContext(void); // easily see disassembly without iostream clutter
//	~IsrContext(void);

	IsrContext(void)
	{
		std::cout << "ISR Context created" << std::endl;
	}

	~IsrContext(void)
	{
		std::cout << "ISR Context destroyed" << std::endl;
	}
};

struct X { std::string value{"X"}; };
struct Y { std::string value{"Y"}; };

template <IIsrContext TContext>
struct A
{
	std::string id{"A"};
	void doSomething(TContext &isr, std::uint32_t x) { std::cout << "A: " << "this=" << this->id << ", arg=" << x << std::endl; }
};

template <IIsrContext TContext>
struct B
{
	std::string id{"B"};
	void doSomething(TContext &isr, X &x) { std::cout << "B: " << "this=" << this->id << ", arg=" << x.value << std::endl; }
};

template <IIsrContext TContext>
struct C
{
	std::string id{"C"};
	void doSomething(TContext &isr, const Y &y) { std::cout << "C: " << "this=" << this->id << ", arg=" << y.value << std::endl; }
};

template <IIsrContext TContext>
struct Unknown
{
	std::string id{"Unknown"};
	void doSomething(TContext &isr) { std::cout << "UNKNOWN: this=" << this->id << std::endl; }
};

std::tuple<
	A<IsrContext>,
	B<IsrContext>,
	C<IsrContext>,
	Unknown<IsrContext>> handlers;

template <IIsrContext TContext>
struct DummyHandler
{
	void doSomething(TContext &, void *);
};

using Handler = DummyHandler<IsrContext>;
using HandlerInstancePtr = Handler *;
using HandlerMethodPtr = decltype(&Handler::doSomething);
using HandlerPtr = std::pair<HandlerInstancePtr, HandlerMethodPtr>;

template <std::size_t Index, typename T>
static constexpr auto handlerPtr(T &handlers)
{
	return HandlerPtr
	{
		reinterpret_cast<HandlerInstancePtr>(&std::get<Index>(handlers)),
		reinterpret_cast<HandlerMethodPtr>(&std::tuple_element_t<Index, T>::doSomething)
	};
}

std::array handlerPtrs
{
	handlerPtr<0>(handlers),
	handlerPtr<1>(handlers),
	handlerPtr<2>(handlers),
	handlerPtr<3>(handlers)
};

void doSomething(std::uint32_t index, void *arg)
{
	// for the actual kernel, the handlers array needs to be per-CPU, so that 'this' allows storing state in a concurrent-safe manner
	auto handlerPtr = index < handlerPtrs.size()
		? handlerPtrs[index]
		: handlerPtrs[handlerPtrs.size() - 1];

	IsrContext context;
	std::invoke(handlerPtr.second, handlerPtr.first, context, arg);
}

int main(int argc, char *argv[])
{
	X x;
	Y y;
	std::uint32_t z(42);
	doSomething(3, &x);
	doSomething(2, &y);
	doSomething(1, &x);
	doSomething(0, reinterpret_cast<void *>(z));
	return 0;
}
*/
		}
	};
}

#endif
