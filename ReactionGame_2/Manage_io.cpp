
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "Manage_io.h"


std::vector<int> Manage_io::reserved_pins_{}; //constructing a vector


Manage_io::Manage_io(bool is_active) : is_active_{ is_active }
{
}

void Manage_io::reserve(int pin) const
{
	if (std::find(reserved_pins_.begin(), reserved_pins_.end(), pin) == reserved_pins_.end()) //if pin is free
		reserved_pins_.push_back(pin);
	else
		throw std::runtime_error("Pin has already been reserved!");
}

void Manage_io::release(int pin) const
{
	//is_active_ = false;
	reserved_pins_.erase(std::remove(reserved_pins_.begin(), reserved_pins_.end(), pin), reserved_pins_.end());
}
