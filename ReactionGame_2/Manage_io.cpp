#include "Manage_io.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

std::vector<int> Manage_io::reserved_pins_{};

void Manage_io::reserve(int pin) const
{
	if (std::find(reserved_pins_.begin(), reserved_pins_.end(), pin) == reserved_pins_.end())
		reserved_pins_.push_back(pin);
	else
		throw std::runtime_error("Pin has already been reserved!");
	
}

void Manage_io::release(int pin) const
{
	reserved_pins_.erase(std::remove(reserved_pins_.begin(), reserved_pins_.end(), pin), reserved_pins_.end());
}
