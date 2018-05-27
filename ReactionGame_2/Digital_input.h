#pragma once

#include "Manage_io.h"

class Digital_input
{
public:
	Digital_input(int pin);

	Digital_input(const Digital_input& other) = delete; //copy-constructor
	Digital_input(Digital_input&& other) noexcept; //move-constructor
	Digital_input& operator=(const Digital_input& other) = delete; //copy-assignment operator
	Digital_input& operator=(Digital_input&& other) noexcept; //move-assignment operator
	~Digital_input(); //destructor

private:
	int pin_;
	Manage_io manage_io_{ true };
};
