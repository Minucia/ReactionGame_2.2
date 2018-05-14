#pragma once

#include <vector>

class Manage_io {
public:
	Manage_io();
	void reserve(int pin);
	void release(int pin);

private:
	static std::vector<int> reserved_pins_;
};

