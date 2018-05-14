
#include <iostream>
#include <algorithm>

#include "Manage_io.h"

Manage_io::Manage_io()
{
}

void Manage_io::reserve(int pin)
{
	if (std::find(reserved_pins_.begin(), reserved_pins_.end(), pin) != reserved_pins_.end)
		reserved_pins_.push_back(pin);
	else
		std::cout << "Pin already taken." << std::endl; //error should be handled in the future
	
}

void Manage_io::release(int pin)
{
	reserved_pins_.erase(std::remove(reserved_pins_.begin(), reserved_pins_.end(), pin), reserved_pins_.end());
}
