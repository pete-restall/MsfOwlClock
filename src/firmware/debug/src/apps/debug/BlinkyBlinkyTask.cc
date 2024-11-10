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
		RequiredApis apis;
		BlockingSoftwareDelay<500ms> delay;
		GpioSharedPin<DigitalOutput, 81> led;

	public:
		using RequiredApis = AppToDriverApis<GpioDriverApi, SoftwareDelayDriverApi>;

		BlinkyBlinkyTask(RequiredApis &&apis) :
			apis(apis),
			delay(apis.get<SoftwareDelayDriverApi>().createDelayFrom<decltype(delay)>()),
			led(apis.get<GpioDriverApi>().getPinFrom<decltype(led)>())
		{
		}

		void run(void)
		{
			this->delay.wait();
			this->led.toggle();
		}
	};
}
