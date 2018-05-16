#include "Game_logic.h"
#include <iostream>
#include "piproxy.h"
#include <thread>

using namespace std;

static constexpr auto led1_pin = 8;
static constexpr auto led2_pin = 9;
static constexpr auto led_reaction_pin = 7;

Game_logic::Game_logic(Game_data& game_data) : 
	led_reaction_{ led_reaction_pin, LOW },
	led_player1{ led1_pin, LOW },
	led_player2{ led2_pin, LOW },
	game{ game_data },
	states_{States::preperation}
{
}

void Game_logic::play()
{
	// --------------------- User Interface --------------------- 

	cout << "Welcome to reaction game!\n" << endl;

	read_player_names();

	read_num_rounds();


	// --------------------- Statemachine ---------------------

	while (game.running())
	{
		play_round();
	}
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
	game.increase_played_rounds();
	if (game.get_played_rounds() > game.get_rounds_to_play())
		states_ = States::finish;
	else
	{
		led_player1.turn_off();
		led_player2.turn_off();
		led_reaction_.turn_off();

		cout << "Current score: " << player1_.get_name() << " [" << player1_.get_score() << " : "
			<< player2_.get_score() << "] " << player2_.get_name() << endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));
		cout << "Get ready!" << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << "Go!" << endl;

		static constexpr auto minimum_wait = 5;
		static constexpr auto maximum_wait = 10;
		game.set_desired_delay(rand() % (maximum_wait + 1 - minimum_wait) + minimum_wait); //setting a random delay between 5 and 10 seconds
		using s = std::chrono::seconds;
		game.set_delay_start(std::chrono::duration_cast<s>(std::chrono::system_clock::now().time_since_epoch()).count());

		states_ = States::reaction_led;
	}
}

void Game_logic::toggle_reaction_led()
{
	using s = std::chrono::seconds;
	game.set_actual_delay(std::chrono::duration_cast<s>(std::chrono::system_clock::now().time_since_epoch()).count() - game.get_delay_start());

	if (game.get_actual_delay() >= game.get_desired_delay()) //waiting for random 5 to 10 seconds
		led_reaction_.turn_on();

	static constexpr int64_t termination_time = 3;
	if (game.get_actual_delay() - game.get_desired_delay() >= termination_time) //if no one presses a button for 3 seconds, the game terminates
		states_ = States::finish;
	else if(game.get_button1_flag() || game.get_button2_flag())
		states_ = States::result;

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void Game_logic::check_round_results()
{
	if (game.get_button1_flag())
	{
		if (led_reaction_.get_state() == HIGH)
		{
			led_reaction_.turn_off();
			on_player_faster(player1_, led_player1);
		}
		else if (led_reaction_.get_state() == LOW)
		{
			on_player_too_fast(player2_, player1_, led_player2);
		}

		game.set_button1_flag(false);
		game.set_button2_flag(false);
	}
	else if (game.get_button2_flag())
	{
		if (led_reaction_.get_state() == HIGH)
		{
			led_reaction_.turn_off();
			on_player_faster(player2_, led_player2);
		}
		else if (led_reaction_.get_state() == LOW)
		{
			on_player_too_fast(player1_, player2_, led_player1);
		}

		game.set_button1_flag(false);
		game.set_button2_flag(false);
	}
}

void Game_logic::finish_game()
{
	if (game.get_played_rounds() <= game.get_rounds_to_play())
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
			led_player1.blink_5_sec();
		}
		else if (player2_.get_score() > player1_.get_score())
		{
			cout << player2_.get_name() << " wins!" << endl;
			led_player2.blink_5_sec();
		}
		else
		{
			std::cout << "It's a tie!" << std::endl;
			both_leds_blink();
		}
	}

	game.stop(false);
}


void Game_logic::both_leds_blink() //both player_leds blink for 5 seconds
{
	for (int i = 0; i < 5; i++)
	{
		digitalWrite(led1_pin, HIGH);
		digitalWrite(led2_pin, HIGH);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		digitalWrite(led1_pin, LOW);
		digitalWrite(led2_pin, LOW);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void Game_logic::read_player_names()
{
	string input;
	cout << "Player 1, please enter your name." << endl;
	getline(cin, input);
	player1_.set_name(input);
	cout << "Hello " << player1_.get_name() << ". Your button is at pin 0. Your status LED is at pin 8.\n" << endl;

	cout << "Player 2, please enter your name." << endl;
	getline(cin, input);
	player2_.set_name(input);
	cout << "Hello " << player2_.get_name() << ". Your button is at pin 2. Your status_LED is at pin 9.\n" << endl;
}

void Game_logic::read_num_rounds() const
{
	string input;
	cout << "How many rounds would you like to play?" << endl;
	getline(cin, input);
	stringstream in_str{ input };
	int number;
	in_str >> number;
	game.set_rounds_to_play(number);
	cout << "You are going to play " << game.get_rounds_to_play() << " rounds. Let's start!" << endl;
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