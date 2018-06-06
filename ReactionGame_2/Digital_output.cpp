
#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include "Game_data.h"
#include "Digital_output.h"
#include "Manage_io.h"
#include "piproxy.h"


Digital_output::Digital_output(int pin, bool state) : pin_{ pin }
{
	try
	{
		manage_io_.reserve(pin);
	}
	catch (std::runtime_error& re)
	{
		std::cerr << "\n**** Exception was thrown: " << re.what() << std::endl;
		std::cerr << "**** Please check your pins before continuing the game!" << std::endl;
		std::cerr << "****************************************************************\n" << std::endl;
		// TODO one day: it would be nice to exit the game here
	}
	wiringPiSetup();
	pinMode(pin_, OUTPUT);
	digitalWrite(pin_, state);
}

void Digital_output::turn_on()
{
	digitalWrite(pin_, HIGH);
}

void Digital_output::turn_off()
{
	digitalWrite(pin_, LOW);
}

void Digital_output::turn_on_3_sec()
{
		digitalWrite(pin_, HIGH);
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		digitalWrite(pin_, LOW);
}

void Digital_output::blink_5_sec()
{
	for (int i = 0; i < 5; i++)
	{
		digitalWrite(pin_, HIGH);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		digitalWrite(pin_, LOW);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

bool Digital_output::get_state() const
{
	return digitalRead(pin_);
}

Digital_output::Digital_output(Digital_output&& other) noexcept
{
	//pilfer other's resource
	pin_ = other.pin_;
	manage_io_ = other.manage_io_;

	//set other inactive --> release other's resource
	other.manage_io_.is_active_ = false;
}

Digital_output& Digital_output::operator=(Digital_output&& other) noexcept
{
	if (this != &other) //avoiding self-assignment
	{
		//set current object inactive --> release current object's resource
		manage_io_.is_active_ = false;

		//pilfer other's resource
		manage_io_ = other.manage_io_;
		pin_ = other.pin_;

		//set other inactive --> release other's resource
		other.manage_io_.is_active_ = false;
	}
	return *this;
}

Digital_output::~Digital_output()
{
	if (manage_io_.is_active_)
		manage_io_.release(pin_);
}