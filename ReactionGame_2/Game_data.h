#pragma once

#include <chrono>

class Game_data
{
friend class Game_logic;

private:
	bool loop_;
	bool button1_flag_;
	bool button2_flag_;

	int played_rounds_;
	int rounds_to_play_;

	int64_t desired_delay_;
	int64_t delay_start_;
	int64_t actual_delay_;

public:
	int led1_pin_;
	int led2_pin_;
	int led_reaction_pin_;
	int button1_pin_;
	int button2_pin_;


	Game_data(bool loop, bool button1_flag, bool button2_flag, int played_rounds, int rounds_to_play,
		int64_t desired_delay, int64_t delay_start, int64_t actual_delay,
		int led1_pin, int led2_pin, int led_reaction_pin, int button1_pin, int button2_pin);

	void read_json();

	void stop(bool loop);
	bool running() const;
	void set_button1_flag(bool button1_flag);
	bool get_button1_flag() const;
	void set_button2_flag(bool button2_flag);
	bool get_button2_flag() const;

	void reset_played_rounds();
	void increase_played_rounds();
	int get_played_rounds() const;
	void set_rounds_to_play(int rounds_to_play);
	int get_rounds_to_play() const;

	void set_desired_delay(int64_t desired_delay);
	int64_t get_desired_delay() const;
	void set_delay_start(int64_t delay_start);
	int64_t get_delay_start() const;
	void set_actual_delay(int64_t actual_delay);
	int64_t get_actual_delay() const;
};