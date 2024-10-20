#ifndef __SMEG_KERNEL_CRT_ENTRYPOINT_HH
#define __SMEG_KERNEL_CRT_ENTRYPOINT_HH
#include "ICrt0Environment.hh"

extern void blinkyBlinky(void);

namespace smeg::kernel::crt
{
	template <ICrt0Environment TCrt0Environment>
	class Entrypoint
	{
	private:
		const TCrt0Environment environment;

	public:
		Entrypoint(const TCrt0Environment crt0Environment) noexcept :
			environment(crt0Environment)
		{
		}

		[[gnu::noreturn]] // TODO: THIS SHOULD BE CONDITIONAL - IF RUNNING ON HOST (IE. TESTS) THEN IT SHOULD BE RETURNABLE...
		void run(void) const noexcept
		{
			// TODO: give a bootloader an opportunity - firmware upgrades will need to be done in stages.  If one stage fails, we can tell where.  To initiate a firmware update:
			//   1. erase a block in the application's .text (linker script provides the range)  The first two words of this block are the 'bootloader magic bytes' - if something goes wrong after erasing even the first bit, the magic bytes will be damaged
			//   2. write the intermediate bootloader into the (erased block + 16 bytes)
			//   3. write the address of the intermediate bootloader entrypoint into (erased block + 12 bytes) - the word at (erased block + 8 bytes) is reserved
			//   4. write the bootloader magic bytes (0x736d6567, 0x68656164) into (erased block + 0 bytes)
			//   5. reset ?
			//
			// On booting, we thus need to:
			//   1. if bootloader magic bytes == (0x534d4547, 0x48454144), jump to the application
			//   2. if bootloader magic bytes == (0x534d4547, *), the new kernel bootloader is working, so call that
			//   3. if bootloader magic bytes == (*, 0x68656164), load the intermediate bootloader address (erased block + 12 bytes) and jump to it
			//   4. if bootloader magic bytes are anything else then the application is corrupted but the kernel bootloader should still be working, so call that
			//
			// When the intermediate bootloader is invoked, write the kernel portion of the firmware:
			//   1. erase and write the non-vector and non-bootloader locations
			//   2. erase the vector table and bootloader and write those, then set the first magic byte to 0x534d4547
			// *** NOTE THAT IT IS POSSIBLE TO BRICK THE DEVICE IF STEP 2 FAILS, IF, FOR EXAMPLE, POWER IS LOST ***
			// *** FOR THE PIC32CX DEVICE, THERE IS SPECIFIC FUNCTIONALITY TO HELP THIS - THE 'BKSWRST' COMMAND AND BANKED FLASH, WHICH WOULD PRECLUDE THE
			//     NEED FOR THE INTERMEDIATE BOOTLOADER ENTIRELY ***
			//
			// When the kernel bootloader needs to do its work, erase and write the application portion of the firmware, then set the second magic byte to 0x48454144
			//
			// The reading of the kernel config, the app initialisation, jumping to the app, etc. all need to be done in a separate (non-inline) method so the
			// kernel doesn't try using corrupted application state during the firmware upgrade process.  This all relies on having anything in 'libkernel',
			// 'libcrt' and 'libcrt0' self-contained (including exception tables, dependent libgcc / libstdc++ library code, etc.)


			// can TDD this up:
			// 1. expect crt0Environment.getBootloader() is called and run - ONLY IF NOT PREVIOUSLY INITIALISED (EG. MULTI-CORE CONFIGURATION)
			// 2. expect kernel RAM sections from crt0Environment are initialised - ONLY IF NOT PREVIOUSLY INITIALISED (EG. MULTI-CORE CONFIGURATION)
			// 3. expect kernel code sections from crt0Environment are initialised - ONLY IF NOT PREVIOUSLY INITIALISED (EG. MULTI-CORE CONFIGURATION)
			// 4. expect TaskRunnerFor<TCrt0Environment::Config, 0>::run() is called
			// 5. expect crt0Environment.reset(KernelResetReasons.UnexpectedTaskRunnerReturn) is called



			// The plan...
			// initialise the kernel (bss, data, init)
			// initialise the kernel structures based on kernel config
			// revoke kernel privileges and then continue initialisation:
			//   initialise app bss, data and init
			//   call app

			// TODO: WE'RE NOW AT A POINT WHERE THINGS RUN AGAIN IN HARDWARE - TIDY ALL THIS UP AND START TDD-ING IT...
			auto kernelMemoryMap = this->environment.getLinkerMemoryMap().getLinkerMemoryMapForKernel();
			kernelMemoryMap.getInitialiserForRamSections().initialise();
			kernelMemoryMap.getInitialiserForCodeSections().initialise();

			auto appMemoryMap = this->environment.getLinkerMemoryMap().getLinkerMemoryMapForApp();
			appMemoryMap.getInitialiserForRamSections().initialise();
			appMemoryMap.getInitialiserForCodeSections().initialise();
			//blinkyBlinky();

			// need a big try...catch around this to comply with noexcept
			while (1)
				;;
		}
	};
}

/*
The Kernel is a library comprising some modular parts:
	Tasks
		* Tasks and their resources need to be statically defined, which cannot change (no dynamic Task definition / creation)
		* an Idle Task must always be defined and it will not be pre-empted by SysTick; it will have the lowest priority and if it terminates then it will be restarted - exiting due to exception can have a policy attached (for example, to restart the MCU)
		* need a block of RAM for use as a stack (including context saving); the stack can be shared to allow Task overlay on termination, but obviously only one Task at a time can use the stack
		* need an API into the kernel and any APIs for any drivers that are used (all statically declared)
		* state - running, runnable / not blocked, runnable / blocked, terminated / not blocked, terminated / blocked (ie. stack in use by another Task)
		* module-specific state, eg:
			* the Dispatcher will require a pointer to a chain of context-saving objects
			* some drivers may require semaphores, etc. for resource allocation
			* statistics, for example the Scheduler may wish to priorise based on expected time left to run (quickest task first, for example, to increase throughput)
		* priority - implicit in which Scheduler queue the task is in (no explicit per-Task state needed)

	Task Scheduler
		Dispatcher
			Task Execution Lifecycle (uspace)
				* entrypoint for _all Tasks_, the PC is initally set to the Lifecycle's run() method when a Task is (re)started
				* constructs the instance of ITask(env), calls ITask.run(), destructs the ITask instance; on termination (normal and exception), execute a termination strategy which may, for example, schedule the same task to be re-started

			Task Execution Context Management
				Kernel task stack (MSP in ARM) needs to be sufficiently large for (context saving space * irq priorities) for worst-case nested exception handling

				Context Switcher (kspace)
					* in ARM systems, assign syscall the highest interrupt priority so it will never be interrupted during context switching; reduce priority for non-context-switch syscalls

		***** TODO - FIGURE OUT HOW THIS IS GOING TO WORK.  THIS ISN'T QUITE RIGHT...
					* one instance of the context switcher per CPU (one Idle Task is also going to be required per CPU)
					* constructed with a Task Control Block for the Idle Task
					* constructed with an array of pointers (a queue) to Task Control Blocks
					* one method - switchToNext() - to pop the next entry from the queue and switch contexts; if there is no next entry, run the Idle Task
					* the scheduler needs to update the queue to include calls to itself

*** HOW DOES SCHEDULER FIT INTO ALL OF THIS ?  ONE SCHEDULER TASK PER CPU, TOO ?

				Bootstrapping the Context Switching (kspace)
					* for ARM, leave MSP as-is; this is the current top-of-stack required for interrupts; make sure the MSP is sized as (irq priorities * context saving space + each irq stack requirement + bootstrapped auto variables); would be better to calculate this out rather than hard-code it in the linker
					* call the TaskRunner with the first task in KernelConfig

				TaskRunner (kspace)
					* takes a TaskLifecycle and a TaskControlBlock
					* for ARM, set the current SP to PSP and to the top of the first kernel task's stack
					* for ARM, set the link register to an exit handler that does a svc (syscall on MIPS, etc.) to remove the task from the scheduling (disable it); another syscall should allow re-enabling the task if desired
					* call a chain of (trusted) Kernel modules (ie. memory protection, power saving, etc.) for bootstrapping.  Basically driver-specific chain of method calls
					* drop into uspace if the task has an unprivileged flag set
					* create a TaskLifecycle for the task and run() it

				Context Saving (kspace)
					* needs to be able to call various other (trusted) Kernel modules (ie. memory protection, power saving, etc.)  Basically driver-specific chain of method calls
					* the chain of context-saving routines to call is Task-specific but the first is the CPU register pushing
					* this needs to be done via an svc or pendsvc

				Context Restoration (kspace)
					* needs to be able to call various other (trusted) Kernel modules (ie. memory protection, power saving, etc.)  Basically driver-specific chain of method calls
					* the chain of context-restoring routines to call is Task-specific but the last is the CPU register popping / PC load
					* can assume never interrupted
					* this needs to be done by an svc or pendsvc

		Pre-emption (kspace)
			* Tick Timer (not necessarily SysTick for ARM) - requires an ISR; last thing to be initialised by the kernel.  Also optional - time-slicing is an optional (KernelConfig) feature.
			* define an SVCALL (or equivalent) for 'yield', which does the same thing as the Tick Timer ISR; other SVCALLs will be available, but a 'yield' jumps to the Scheduler prioritisation routine

		Prioritisation (kspace)
			* the Task priority is implicit in which queue the task is in (no explicit per-Task state needed)
			* context switcher takes first runnable / not blocked Task from the head of the highest-priority queue
			* scheduler determines what the priority queues look like
			Managing task priorities (uspace)

	Memory Manager

	APIs
		Kernel-facing
		App-facing

	Drivers
		Kernelspace
			* ISRs - if they affect the state of Tasks then they will need to call the Scheduler to find the next prioritised Task to run
			* Kernel-facing API

		Userspace
			* Tasks for managing the driver
			* App-facing API

Startup tasks (probably _resetHandler ?):
	Ensure CCR.STKALIGN is set correctly (to 1) to enforce 8-byte stack alignment - do this as soon as possible, in the _resetHandler really...
	Ensure FPCCR.ASPEN and FPCCR.LSPEN are set correctly:
		Original thought was (1 and 1) to ensure lazy FP stacking for ISR entry (faster for use-cases that don't touch FP; which the kernel should not)
	Configure both SVCall and PendSV with the same, highest exception priority (0).

isrSystick()
	; probably need to treat this as a watchdog - every time a context switch occurs (just before the 'bx LR') then clear out so the task gets a full quantum
	; would that stop an 'svcall' followed by an 'isrSystick' though ?  That scenario could cause the 'isrSvcall' to skip over a task if called back-to-back
	if currentTask != schedulerTask
		pendsv 0x????

svcall 0x????
isrSvcall() ; this is the highest priority interrupt
	nextTask = currentTask->next // TODO: if pendsv is back-to-back (eg. 'yield' followed by 'isrSystick') then this could skip a task
	if (!nextTask)
		nextTask = schedulerTask;

	if currentTask == nextTask {
		// just return from interrupt - no context switch is required
	}

	currentTask->saveContext() {
		mrs r0, psp
		isb

		tst LR, #0x10
		it eq
			vstmdbeq r0!, {s16-s31} ; push the floating-point registers if the caller was using the FPU (LR & 0x10) - 112 BYTES OF STACK REQUIRED !!!

		; See ARMv7 Technical Reference Manual, b1-531 - what if stmdb gets interrupted by higher priority ISR ?  Double-check it resumes or restarts...
		stmdb r0!, {r4-r11, LR}; push r4-r11 to process stack (r0-3, r12, r14(LR), PC, xpsr are pushed by the MCU on ISR entry; LR seems to be pushed again to allow easy context restoration - the initial value is SP+0x14), r0 contains process stack pointer
		store 'r0' into currentTask->stackPointer ; r0 is 'top of (process) stack' from the previous 'stmdb'
		currentTask->onContextSwitchedOut()
	}

	nextTask->restoreContext() {
		currentTask = nextTask ; need to get stack pointer of highestPriorityTask into r0
		currentTask->onContextSwitchedIn()

		ldmia r0!, {r4-r11} ; can get LR if pushed above, or from r0+0x14 ?
		tst LR, #0x10
		it eq
			vldmiaeq r0!, {s16-s31} ; pop the floating-point registers if the caller was using the FPU (LR & 0x10) - 112 BYTES OF STACK REQUIRED !!!

		msr psp, r0
		isb
		bx LR
	}
*/



/*

USE TEMPLATE SPECIALISATION FOR PARSING THE CONFIG OBJECT.  THIS ALLOWS USERS TO SPECIFY THE BARE MINIMUM CONFIG AND ALLOWS SENSIBLE DEFAULTS.
IF THERE IS NO createBootloader() METHOD PRESENT THEN WE CAN USE A DEFAULT BOOTLOADER; IF THERE IS A createBootloader() METHOD PRESENT THEN IT CAN BE USED
TO CREATE / CONFIGURE A GIVEN BOOTLOADER.  BASICALLY COMPILE-TIME DEPENDENCY INJECTION...

OR...THE USER JUST CREATES THE SPECIALISATIONS THEMSELVES, IN A config SUBDIRECTORY.  THIS COULD BE A BIT SERVICE-LOCATOR-Y (UURGH).

OR...THE bootloader PROPERTY IS OF A GIVEN TYPE, SAY, SpecialBootloaderConfig, SuperSpecialBootloaderConfig, ETC. AND THEN THE BOOTLOADER IMPLEMENTATIONS
PROVIDE THEIR OWN FACTORY SPECIALISATIONS FOR THESE CONFIG TYPES - PROBABLY THE BEST WAY FOR CONFIGS.

THREE DIFFERENT TECHNIQUES FOR THREE DIFFERENT USE-CASES.

---

#include <concepts>
#include <iostream>

template <typename T>
concept IBootloaderConfig = requires(const T &obj)
{
	{ obj.magic } -> std::convertible_to<int>;
};

class DefaultBootloader
{
public:
	void run(void)
	{
		std::cout << "Default bootloader..." << std::endl;
	}
};

class SpecialBootloader
{
private:
	int magic;

public:
	SpecialBootloader(int magic) :
		magic(magic)
	{
	}

	void run(void)
	{
		std::cout << "Special bootloader (" << this->magic << ") !!!" << std::endl;
	}
};

template <typename TConfig>
class BootloaderFactory
{
private:
	const TConfig config;

public:
	BootloaderFactory(const TConfig &config) :
		config(config)
	{
	}

	DefaultBootloader createBootloader(void)
	{
		return DefaultBootloader();
	}
};

template <IBootloaderConfig TConfig>
class BootloaderFactory<TConfig>
{
private:
	const TConfig config;

public:
	BootloaderFactory(const TConfig &config) :
		config(config)
	{
	}

	SpecialBootloader createBootloader(void)
	{
		return SpecialBootloader(this->config.magic);
	}
};

class Config
{
public:
	int magic = 42;
};

int main(int argc, char *argv[])
{
	Config config;
	BootloaderFactory factory(config);
	factory.createBootloader().run();
	return 0;
}

*/

#endif
