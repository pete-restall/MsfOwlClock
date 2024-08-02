#include "kernel/Userspace.hh"
#include "kernel/drivers/GpioDriver/Userspace.hh"
#include "kernel/drivers/SoftwareDelayDriver/Userspace.hh"

using namespace smeg::kernel::userspace;
using namespace smeg::kernel::drivers::gpio_driver::userspace;
using namespace smeg::kernel::drivers::software_delay_driver::userspace;

namespace restall::msf_owl_clock::debug
{
	class BlinkyBlinkyTask
	{
	private:
		BlockingSoftwareDelay<500ms> delay;
		GpioSharedPin<DigitalOutput, 81> led;

	public:
		BlinkyBlinkyTask(KernelApi<GpioDriver, SoftwareDelayDriver> &&kernel) :
			delay(kernel.usingSoftwareDelayDriver().createFrom<decltype(delay)>()),
			led(kernel.usingGpioDriver().getPinFrom<decltype(led)>())
		{
		}

		void run(void)
		{
			this->delay.wait();
			this->led.toggle();
		}
	};
}
