#pragma once

#include "Manage_io.h"

class Digital_output {
private:
	int pin_;
	std::shared_ptr<Manage_io> ptr_pi_pins_;

public:
	bool state_;

	Digital_output(int pin, std::shared_ptr<Manage_io> ptr_pi_pins, bool state);
	void turn_on();
	void turn_off();
	void turn_on_3_sec();
	void blink_5_sec();
	bool get_state() const;

	Digital_output(const Digital_output& other) = default; //copy-constructor
	Digital_output(Digital_output&& other) = default; //move-constructor
	Digital_output& operator=(const Digital_output &rhs) = default; //copy-assignment operator
	Digital_output& operator=(Digital_output &&rhs) = default; //move-assignment operator
	~Digital_output(); //destructor
};

