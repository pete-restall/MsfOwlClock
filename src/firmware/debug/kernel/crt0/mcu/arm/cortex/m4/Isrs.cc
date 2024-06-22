#include "Isrs.hh"

namespace smeg::kernel::crt0::mcu::arm::cortex::m4
{
	[[gnu::weak]]
	void Isrs::defaultIsr(void) noexcept
	{
		// TODO: ABORT WITH REASON
		while (1)
			;;
	}

	[[gnu::weak]]
	void Isrs::reservedIsr(void) noexcept
	{
		// TODO: ABORT WITH REASON
		while (1)
			;;
	}

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_DEFAULT_ISR_NAME)]]
	void Isrs::nmi(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_DEFAULT_ISR_NAME)]]
	void Isrs::hardFault(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_DEFAULT_ISR_NAME)]]
	void Isrs::memManage(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_DEFAULT_ISR_NAME)]]
	void Isrs::busFault(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_DEFAULT_ISR_NAME)]]
	void Isrs::usageFault(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_RESERVED_ISR_NAME)]]
	void Isrs::reserved7(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_RESERVED_ISR_NAME)]]
	void Isrs::reserved8(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_RESERVED_ISR_NAME)]]
	void Isrs::reserved9(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_RESERVED_ISR_NAME)]]
	void Isrs::reserved10(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_DEFAULT_ISR_NAME)]]
	void Isrs::svCall(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_DEFAULT_ISR_NAME)]]
	void Isrs::debugMonitor(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_RESERVED_ISR_NAME)]]
	void Isrs::reserved13(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_DEFAULT_ISR_NAME)]]
	void Isrs::pendsv(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__ARM_CORTEX_M4_DEFAULT_ISR_NAME)]]
	void Isrs::sysTick(void) noexcept;
}
