#include <algorithm>
#include <cstdint>

extern void blinkyBlinky(void) noexcept;

typedef void (*const InitFuncPtr)(void); // TODO: THE noexcept CAN BE TAKEN OFF ONCE DEBUGGING SUITABLY ADVANCED...

extern "C"
{
	extern const InitFuncPtr __linker_code_flash_kernel_initArray_start;
	extern const InitFuncPtr __linker_code_flash_kernel_initArray_pastEnd;

	extern const InitFuncPtr __linker_code_flash_kernel_finiArray_start;
	extern const InitFuncPtr __linker_code_flash_kernel_finiArray_pastEnd;

	extern const InitFuncPtr __linker_code_flash_application_initArray_start;
	extern const InitFuncPtr __linker_code_flash_application_initArray_pastEnd;

	extern const InitFuncPtr __linker_code_flash_application_finiArray_start;
	extern const InitFuncPtr __linker_code_flash_application_finiArray_pastEnd;

	extern std::uint32_t __linker_sram_bss_retained16k_kernel_start;
	extern std::uint32_t __linker_sram_bss_retained16k_kernel_pastEnd;
	extern std::uint32_t __linker_sram_data_retained16k_kernel_start;
	extern std::uint32_t __linker_sram_data_retained16k_kernel_pastEnd;
	extern std::uint32_t __linker_sram_data_retained16k_kernel_lmaStart;
	extern std::uint32_t __linker_sram_bss_retained16k_kernel_start;
	extern std::uint32_t __linker_sram_bss_retained16k_kernel_pastEnd;
	extern std::uint32_t __linker_sram_data_retained16k_application_start;
	extern std::uint32_t __linker_sram_data_retained16k_application_pastEnd;
	extern std::uint32_t __linker_sram_data_retained16k_application_lmaStart;
	extern std::uint32_t __linker_sram_bss_retained16k_application_start;
	extern std::uint32_t __linker_sram_bss_retained16k_application_pastEnd;
	extern std::uint32_t __linker_sram_data_kernel_start;
	extern std::uint32_t __linker_sram_data_kernel_pastEnd;
	extern std::uint32_t __linker_sram_data_kernel_lmaStart;
	extern std::uint32_t __linker_sram_bss_kernel_start;
	extern std::uint32_t __linker_sram_bss_kernel_pastEnd;
	extern std::uint32_t __linker_sram_data_application_start;
	extern std::uint32_t __linker_sram_data_application_pastEnd;
	extern std::uint32_t __linker_sram_data_application_lmaStart;
	extern std::uint32_t __linker_sram_bss_application_start;
	extern std::uint32_t __linker_sram_bss_application_pastEnd;

	[[noreturn]]
	[[gnu::naked]]
	void _entrypoint(void) noexcept
	{
		// TODO
		// need a big try...catch around this to comply with noexcept; constructors could throw...
		// call __initialiseMcuBeforeCrt() or something ?  That can do such things as...
		//   store reset reason (BOR, POR, MCLR, software reset, fault, etc.) / flags / whatever
		//   set FPU mode for C compatibility
		//
		// platform-agnostic stuff:
		//   initialise various bss / data segments
		//   call init sections
		//   call kernel to initialise and run itself, the microcontroller, the application, any bootloaders, etc.
		//   call equivalent of exit(whateverCode) to 'exit' with a successful code - if we're not in kernel mode then we'll need to just loop forever...

		std::fill(&__linker_sram_bss_retained16k_kernel_start, &__linker_sram_bss_retained16k_kernel_pastEnd, 0x00000000);
		std::fill(&__linker_sram_bss_retained16k_application_start, &__linker_sram_bss_retained16k_application_pastEnd, 0x00000000);
		std::fill(&__linker_sram_bss_kernel_start, &__linker_sram_bss_kernel_pastEnd, 0x00000000);
		std::fill(&__linker_sram_bss_application_start, &__linker_sram_bss_application_pastEnd, 0x00000000);

		std::copy_n(&__linker_sram_data_retained16k_kernel_lmaStart,
			&__linker_sram_data_retained16k_kernel_pastEnd - &__linker_sram_data_retained16k_kernel_start,
			&__linker_sram_data_retained16k_kernel_start);

		std::copy_n(&__linker_sram_data_retained16k_application_lmaStart,
			&__linker_sram_data_retained16k_application_pastEnd - &__linker_sram_data_retained16k_application_start,
			&__linker_sram_data_retained16k_application_start);

		std::copy_n(&__linker_sram_data_kernel_lmaStart,
			&__linker_sram_data_kernel_pastEnd - &__linker_sram_data_kernel_start,
			&__linker_sram_data_kernel_start);

		std::copy_n(&__linker_sram_data_application_lmaStart,
			&__linker_sram_data_application_pastEnd - &__linker_sram_data_application_start,
			&__linker_sram_data_application_start);

		std::for_each(
			&__linker_code_flash_kernel_initArray_start,
			&__linker_code_flash_kernel_initArray_pastEnd,
			[](auto &initFunction) { initFunction(); });

		std::for_each(
			&__linker_code_flash_application_initArray_start,
			&__linker_code_flash_application_initArray_pastEnd,
			[](auto &initFunction) { initFunction(); });

		std::for_each(
			std::reverse_iterator(&__linker_code_flash_application_finiArray_pastEnd),
			std::reverse_iterator(&__linker_code_flash_application_finiArray_start),
			[](auto &finiFunction) { finiFunction(); });

		std::for_each(
			std::reverse_iterator(&__linker_code_flash_kernel_finiArray_pastEnd),
			std::reverse_iterator(&__linker_code_flash_kernel_finiArray_start),
			[](auto &finiFunction) { finiFunction(); });

//		blinkyBlinky();
		exit(0);

		__builtin_unreachable();
	}
};

extern "C"
{
	void *__dso_handle(nullptr);
	void *sbrk(void) { return reinterpret_cast<void *>(-1); }

// exit() calls __call_exitprocs and then _exit(); we need to trap __call_exitprocs() to only destroy application-created stuff methinks, so the kernel can continue running to shutdown properly.  Although should be fine if not using global objects, so maybe just provide a hook for it so it's not hidden away ?
// Can't override __call_exitprocs (unless we __wrap it), so maybe just making sure the kernel uses no statics is sufficient...
// Overriding exit() is also not possible as it's not weak.  However, __call_exitprocs() is weak if picolibc is built with '_LITE_EXIT'.  Investigate at some point...
}

static int __xxx = 0;

class Xxx
{
private:
	static volatile int x;

public:
	Xxx()
	{
		x = ++__xxx;
	}

	~Xxx()
	{
		x -= __xxx--;
	}
};

volatile int Xxx::x;

class Yyy
{
private:
	static volatile int y;

public:
	Yyy()
	{
		y = ++__xxx;
	}

	~Yyy()
	{
		y -= __xxx--;
	}
};

volatile int Yyy::y;

class Zzz
{
private:
	static volatile int z;

public:
	Zzz()
	{
		z = ++__xxx;
	}

	~Zzz()
	{
		z -= __xxx--;
	}
};

volatile int Zzz::z;

static Xxx xxx;
static Yyy yyy;
static Zzz zzz;
