#pragma once

#include <vector>

class Manage_io {
public:
	void reserve(int pin) const;
	void release(int pin) const;

private:
	static std::vector<int> reserved_pins_;
};

