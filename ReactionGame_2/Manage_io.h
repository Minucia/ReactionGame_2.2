#pragma once

#include <vector>
#include "Digital_output.h"

class Manage_io {
public:
	Manage_io(bool is_active);
	void reserve(int pin) const;
	void release(int pin) const;

private:
	bool is_active_;
	static std::vector<int> reserved_pins_;

friend Digital_output;
};