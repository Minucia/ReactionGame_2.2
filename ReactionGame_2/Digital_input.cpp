
#include <iostream>
#include "Digital_input.h"
#include "piproxy.h"
#include "Game_logic.h"

Digital_input::Digital_input(int pin) : pin_{ pin }
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
		// TODO it would be nice to exit the game here
	}
	wiringPiSetup();
	pinMode(pin_, INPUT);
	pullUpDnControl(pin_, PUD_DOWN); //pull to ground
}

Digital_input::Digital_input(Digital_input && other) noexcept
{
	//pilfer other's resource
	pin_ = other.pin_;
	manage_io_ = other.manage_io_;

	//set other inactive --> release other's resource
	other.manage_io_.is_active_ = false;
}

Digital_input & Digital_input::operator=(Digital_input && other) noexcept
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

Digital_input::~Digital_input()
{
	if (manage_io_.is_active_)
		manage_io_.release(pin_);
}

