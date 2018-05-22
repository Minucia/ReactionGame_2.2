
#include "piproxy.h"
#include <chrono>
#include <thread>

#include "Digital_output.h"
#include "Manage_io.h"


Digital_output::Digital_output(int pin, bool state) : 
	pin_{ pin }
{
	manage_io_.reserve(pin);
	wiringPiSetup();
	pinMode(pin_, OUTPUT);
	digitalWrite(pin_, state);
}

void Digital_output::turn_on()
{
	digitalWrite(pin_, HIGH);
}

void Digital_output::turn_off()
{
	digitalWrite(pin_, LOW);
}

void Digital_output::turn_on_3_sec()
{
		digitalWrite(pin_, HIGH);
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		digitalWrite(pin_, LOW);
}

void Digital_output::blink_5_sec()
{
	for (int i = 0; i < 5; i++)
	{
		digitalWrite(pin_, HIGH);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		digitalWrite(pin_, LOW);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

bool Digital_output::get_state() const
{
	return digitalRead(pin_);
}

Digital_output::Digital_output(Digital_output&& other) noexcept : 
pin_{ other.pin_ },
manage_io_{ other.manage_io_ }
{
	// MFA TODO for you, miss neuhold & mister soukup
	// MFA you want to move the ownership of the pin here. how could you do that?
}

Digital_output& Digital_output::operator=(Digital_output&& rhs) noexcept
{
	// MFA TODO for you, miss neuhold & mister soukup
	return *this;
}

Digital_output::~Digital_output()
{
	manage_io_.release(pin_);
}
