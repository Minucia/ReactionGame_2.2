
#include <iostream>
#include <fstream>
#include <thread>
#include "Game_logic.h"
#include "piproxy.h"

using namespace std;


Game_logic::Game_logic(Game_data& game_data) : 
	led_reaction_{ game_data.led_reaction_pin_, LOW },
	led_player1_{ game_data.led1_pin_, LOW },
	led_player2_{ game_data.led2_pin_, LOW },
	button_player1_{ game_data.button1_pin_ },
	button_player2_{ game_data.button2_pin_ },
	game_{ game_data },
	states_{States::preperation}
{
}

void Game_logic::play()
{
	cout << "Welcome to reaction game!\n" << endl;

	read_player_names();

	read_num_rounds();


	while (game_.running())
	{
		play_round();
	}
}

void Game_logic::read_player_names()
{
	string input;
	cout << "Player 1, please enter your name." << endl;
	getline(cin, input);
	player1_.set_name(input);
	cout << "Hello " << player1_.get_name() << ".\n" << endl;

	cout << "Player 2, please enter your name." << endl;
	getline(cin, input);
	player2_.set_name(input);
	cout << "Hello " << player2_.get_name() << ".\n" << endl;
}

void Game_logic::read_num_rounds() const
{
	string input;
	cout << "How many rounds would you like to play?" << endl;
	getline(cin, input);
	stringstream in_str{ input };
	int number;
	in_str >> number;
	game_.set_rounds_to_play(number);
	cout << "You are going to play " << game_.get_rounds_to_play() << " rounds. Let's start!" << endl;
}

void Game_logic::play_round()
{
	switch (states_)
	{
	case States::preperation:
		{
			prepare_round();
		}
		break;

	case States::reaction_led:
		{
			toggle_reaction_led();
		}
		break;

	case States::result:
		{
			check_round_results();
		}
		break;

	case States::finish:
		{
			finish_game();
		}
		break;

	default:
		{
			cout << "That wasn't supposed to happen." << endl;
		}
		break;
	}
}

void Game_logic::prepare_round()
{
	game_.increase_played_rounds();
	if (game_.get_played_rounds() > game_.get_rounds_to_play())
		states_ = States::finish;
	else
	{
		led_player1_.turn_off();
		led_player2_.turn_off();
		led_reaction_.turn_off();

		cout << "Current score: " << player1_.get_name() << " [" << player1_.get_score() << " : "
			<< player2_.get_score() << "] " << player2_.get_name() << endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));
		cout << "Get ready!" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Go!" << endl;

		static constexpr auto minimum_wait = 5;
		static constexpr auto maximum_wait = 10;
		game_.set_desired_delay(rand() % (maximum_wait + 1 - minimum_wait) + minimum_wait); //setting a random delay between 5 and 10 seconds
		using s = std::chrono::seconds;
		game_.set_delay_start(std::chrono::duration_cast<s>(std::chrono::system_clock::now().time_since_epoch()).count());

		states_ = States::reaction_led;
	}
}

void Game_logic::toggle_reaction_led()
{
	using s = std::chrono::seconds;
	game_.set_actual_delay(std::chrono::duration_cast<s>(std::chrono::system_clock::now().time_since_epoch()).count() - game_.get_delay_start());

	if (game_.get_actual_delay() >= game_.get_desired_delay()) //waiting for random 5 to 10 seconds
		led_reaction_.turn_on();

	static constexpr int64_t termination_time = 3;
	if (game_.get_actual_delay() - game_.get_desired_delay() >= termination_time) //if no one presses a button for 3 seconds, the game terminates
		states_ = States::finish;
	else if(game_.get_button1_flag() || game_.get_button2_flag())
		states_ = States::result;

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void Game_logic::check_round_results()
{
	if (game_.get_button1_flag())
	{
		if (led_reaction_.get_state() == HIGH)
		{
			led_reaction_.turn_off();
			on_player_faster(player1_, led_player1_);
		}
		else if (led_reaction_.get_state() == LOW)
		{
			on_player_too_fast(player2_, player1_, led_player2_);
		}

		game_.set_button1_flag(false);
		game_.set_button2_flag(false);
	}
	else if (game_.get_button2_flag())
	{
		if (led_reaction_.get_state() == HIGH)
		{
			led_reaction_.turn_off();
			on_player_faster(player2_, led_player2_);
		}
		else if (led_reaction_.get_state() == LOW)
		{
			on_player_too_fast(player1_, player2_, led_player1_);
		}

		game_.set_button1_flag(false);
		game_.set_button2_flag(false);
	}
}

void Game_logic::both_leds_blink() //both player_leds blink for 5 seconds
{
	for (int i = 0; i < 5; i++)
	{
		led_player1_.turn_on();
		led_player2_.turn_on();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		led_player1_.turn_off();
		led_player2_.turn_off();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void Game_logic::on_player_faster(Player& player, Digital_output& led_player)
{
	player.increase_score();
	cout << player.get_name() << " gets a point." << endl;
	led_player.turn_on_3_sec();
	states_ = States::preperation;
}

void Game_logic::on_player_too_fast(Player& winner, Player& loser, Digital_output& winner_led)
{
	winner.increase_score();
	cout << "Not so fast " << loser.get_name() << ". " << winner.get_name() << " gets a point." << endl;
	winner_led.turn_on_3_sec();
	states_ = States::preperation;
}

void Game_logic::finish_game()
{
	if (game_.get_played_rounds() <= game_.get_rounds_to_play())
	{
		led_reaction_.turn_off();
		cout << "The game terminated due to inactivity." << endl;
	}
	else
	{
		cout << "Current score: " << player1_.get_name() << " [" << player1_.get_score() << " : "
			<< player2_.get_score() << "] " << player2_.get_name() << endl;
		if (player1_.get_score() > player2_.get_score())
		{
			cout << player1_.get_name() << " wins!" << endl;
			led_player1_.blink_5_sec();
		}
		else if (player2_.get_score() > player1_.get_score())
		{
			cout << player2_.get_name() << " wins!" << endl;
			led_player2_.blink_5_sec();
		}
		else
		{
			std::cout << "It's a tie!" << std::endl;
			both_leds_blink();
		}
	}

	game_.stop(true);
}