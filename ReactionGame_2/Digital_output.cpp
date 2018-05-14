
#include <wiringPi.h>
#include <chrono>
#include <thread>

#include "Digital_output.h"
#include "Manage_io.h"


Digital_output::Digital_output(int pin, std::shared_ptr<Manage_io> ptr_pi_pins, bool state) : pin_{ pin }, ptr_pi_pins_{ ptr_pi_pins }, state_ { state }
{
	ptr_pi_pins_->reserve(pin);
	wiringPiSetup();
	pinMode(pin_, OUTPUT);
	digitalWrite(pin_, state_);
}

void Digital_output::turn_on()
{
	digitalWrite(pin_, HIGH);
	state_ = HIGH;
}

void Digital_output::turn_off()
{
	digitalWrite(pin_, LOW);
	state_ = LOW;
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
	return state_; //digitalRead(pin_);
}

Digital_output::~Digital_output()
{
	ptr_pi_pins_->release(pin_);
}
