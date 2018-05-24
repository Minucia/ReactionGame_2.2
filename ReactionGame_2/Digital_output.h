#pragma once

#include "Manage_io.h"

class Digital_output {
private:
	int pin_;
	Manage_io manage_io_{ true };

public:
	Digital_output(int pin, bool state);
	void turn_on();
	void turn_off();
	void turn_on_3_sec();
	void blink_5_sec();
	bool get_state() const;

	Digital_output(const Digital_output& other) = delete; //copy-constructor
	Digital_output(Digital_output&& other) noexcept; //move-constructor
	Digital_output& operator=(const Digital_output& other) = delete; //copy-assignment operator
	Digital_output& operator=(Digital_output&& other) noexcept; //move-assignment operator
	~Digital_output(); //destructor
};