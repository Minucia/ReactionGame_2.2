
#include "Game_data.h"
#include "json.hpp"

#include <iostream>
#include <fstream>

Game_data::Game_data(bool loop, bool button1_flag, bool button2_flag, int played_rounds, int rounds_to_play,
	int64_t desired_delay, int64_t delay_start, int64_t actual_delay,
	int led1_pin, int led2_pin, int led_reaction_pin, int button1_pin, int button2_pin) :
	loop_{ loop },
	button1_flag_{ button1_flag },
	button2_flag_{ button2_flag },
	played_rounds_{ played_rounds },
	rounds_to_play_{ rounds_to_play },
	desired_delay_ { desired_delay },
	delay_start_{ delay_start },
	actual_delay_{ actual_delay },
	led1_pin_{ led1_pin },
	led2_pin_{ led2_pin },
	led_reaction_pin_{ led_reaction_pin },
	button1_pin_{ button1_pin },
	button2_pin_{ button2_pin }
{
}

void Game_data::read_json()
{
	std::ifstream stream("pins.json");
	nlohmann::json pin_json;
	stream >> pin_json;

	led1_pin_ = pin_json["p1_led"].get<int>();
	led2_pin_ = pin_json["p2_led"].get<int>();
	led_reaction_pin_ = pin_json["state"].get<int>();
	button1_pin_ = pin_json["p1_button"].get<int>();
	button2_pin_ = pin_json["p2_button"].get<int>();

	std::cout << "led1: " << led1_pin_ << std::endl;
	std::cout << "led2: " << led1_pin_ << std::endl;
	std::cout << "btn1: " << button1_pin_ << std::endl;
	std::cout << "btn2: " << button2_pin_ << std::endl;
	std::cout << "status: " << led_reaction_pin_ << std::endl;
}

void Game_data::stop(bool loop)
{
	loop_ = !loop;
}

bool Game_data::running() const
{
	return loop_;
}

void Game_data::set_button1_flag(bool button1_flag)
{
	button1_flag_ = button1_flag;
}

bool Game_data::get_button1_flag() const
{
	return button1_flag_;
}

void Game_data::set_button2_flag(bool button2_flag)
{
	button2_flag_ = button2_flag;
}

bool Game_data::get_button2_flag() const
{
	return button2_flag_;
}

void Game_data::reset_played_rounds()
{
	played_rounds_ = 0;
}

void Game_data::increase_played_rounds()
{
	played_rounds_++;
}

int Game_data::get_played_rounds() const 
{
	return played_rounds_;
}

void Game_data::set_rounds_to_play(int rounds_to_play)
{
	rounds_to_play_ = rounds_to_play;
}

int Game_data::get_rounds_to_play() const
{
	return rounds_to_play_;
}

void Game_data::set_desired_delay(int64_t desired_delay)
{
	desired_delay_ = desired_delay;
}

int64_t Game_data::get_desired_delay() const
{
	return desired_delay_;
}

void Game_data::set_delay_start(int64_t delay_start)
{
	delay_start_ = delay_start;
}

int64_t Game_data::get_delay_start() const
{
	return delay_start_;
}

void Game_data::set_actual_delay(int64_t actual_delay)
{
	actual_delay_ = actual_delay;
}

int64_t Game_data::get_actual_delay() const
{
	return actual_delay_;
}
