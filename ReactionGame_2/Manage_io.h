#pragma once

#include <vector>

class Manage_io
{
friend class Digital_output;
friend class Digital_input;

public:
	Manage_io(bool is_active);
	void reserve(int pin) const;
	void release(int pin) const;

private:
	bool is_active_;
	static std::vector<int> reserved_pins_; 
};