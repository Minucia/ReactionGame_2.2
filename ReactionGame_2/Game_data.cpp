
#include "Game_data.h"


Game_data::Game_data(bool loop, bool button1_flag, bool button2_flag, int played_rounds, int rounds_to_play, int64_t desired_delay, int64_t delay_start, int64_t actual_delay) :
	loop_{ loop }, button1_flag_{ button1_flag }, button2_flag_{ button2_flag }, played_rounds_{ played_rounds }, rounds_to_play_{ rounds_to_play }, desired_delay_ {
	desired_delay
}, delay_start_{ delay_start }, actual_delay_{ actual_delay }
{
}

void Game_data::set_loop(bool loop)
{
	loop_ = loop;
}

bool Game_data::get_loop() const
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
