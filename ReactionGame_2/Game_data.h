#pragma once

#include <chrono>

class Game_data {
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
	Game_data(bool loop, bool button1_flag, bool button2_flag, int played_rounds, int rounds_to_play, int64_t desired_delay, int64_t delay_start, int64_t actual_delay);

	void set_loop(bool loop);
	bool get_loop() const;
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



/*
// ____________________________ Enumerations ____________________________

enum class States { preperation, reaction_led, result, finish };


// ____________________________ Global variables - comment out ____________________________

static constexpr auto led1_pin = 8;
static constexpr auto led2_pin = 9;
static constexpr auto led_reaction_pin = 7;
static constexpr auto button1_pin = 0;
static constexpr auto button2_pin = 2;
static constexpr auto minimum_wait = 5;
static constexpr auto maximum_wait = 10;
static constexpr int64_t termination_time = 3;

States states = States::preperation;

bool loop = true;
bool button1_flag = false;
bool button2_flag = false;

int played_rounds;

int64_t desired_delay;
int64_t delay_start;
int64_t actual_delay;
*/
