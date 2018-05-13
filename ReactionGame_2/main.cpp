

// ____________________________ Includes ____________________________

#include <wiringPi.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
//#include "json.hpp"

#include "Game_data.h"
#include "Player.h"
#include "Digital_output.h"


// ____________________________ Enumeration Class ____________________________

enum class States { preperation, reaction_led, result, finish };
States states = States::preperation;


// ____________________________ Function Prototypes ____________________________

void button_setup();
void button1_pressed();
void button2_pressed();
void both_leds_blink(int pin1, int pin2);


// ____________________________ Global Namespace ____________________________

using namespace std;


// ____________________________ Global Object ____________________________

Game_data game{ true, false, false, 0, 0, 0, 0, 0 }; //setting loop, button1_flag, button2_flag and played_rounds is important


// ____________________________ Main Function ____________________________

int main()
{
	// --------------------- Implementing Objects ---------------------

	Player player1;
	Player player2;

	static constexpr auto led1_pin = 8;
	static constexpr auto led2_pin = 9;
	static constexpr auto led_reaction_pin = 7;

	Digital_output led_player1{ led1_pin, LOW  };
	Digital_output led_player2{ led2_pin, LOW };
	Digital_output led_reaction{ led_reaction_pin, LOW };


	// --------------------- Game Setup --------------------- 

	button_setup();

	player1.reset_score();
	player2.reset_score();


	// --------------------- User Interface --------------------- 

	cout << "Welcome to reaction game!\n" << endl;

	cout << "Player 1, please enter your name." << endl;
	string input;
	getline(cin, input);
	player1.set_name(input);
	cout << "Hello " << player1.get_name() << ". Your button is at pin 0. Your status LED is at pin 8.\n" << endl;

	cout << "Player 2, please enter your name." << endl;
	getline(cin, input);
	player2.set_name(input);
	cout << "Hello " << player2.get_name() << ". Your button is at pin 2. Your status_LED is at pin 9.\n" << endl;

	cout << "How many rounds would you like to play?" << endl;
	getline(cin, input);
	stringstream in_str{ input };
	int number;
	in_str >> number;
	game.set_rounds_to_play(number);
	cout << "You are going to play " << game.get_rounds_to_play() << " rounds. Let's start!" << endl;


	// --------------------- Statemachine ---------------------

	while (game.get_loop())
	{
		switch (states)
		{
		case States::preperation:
		{
			game.increase_played_rounds();
			if (game.get_played_rounds() > game.get_rounds_to_play())
				states = States::finish;
			else
			{
				led_player1.turn_off();
				led_player2.turn_off();
				led_reaction.turn_off();

				cout << "Current score: " << player1.get_name() << " [" << player1.get_score() << " : "
					<< player2.get_score() << "] " << player2.get_name() << endl;

				std::this_thread::sleep_for(std::chrono::seconds(2));
				cout << "Get ready!" << endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
				cout << "Go!" << endl;

				static constexpr auto minimum_wait = 5;
				static constexpr auto maximum_wait = 10;
				game.set_desired_delay( rand() % (maximum_wait + 1 - minimum_wait) + minimum_wait ); //setting a random delay between 5 and 10 seconds
				using s = std::chrono::seconds;
				game.set_delay_start( std::chrono::duration_cast<s>(std::chrono::system_clock::now().time_since_epoch()).count() );
				
				states = States::reaction_led;
			}
		}
		break;

		case States::reaction_led:
		{
			using s = std::chrono::seconds;
			game.set_actual_delay( std::chrono::duration_cast<s>(std::chrono::system_clock::now().time_since_epoch()).count() - game.get_delay_start() );
			
			if (game.get_actual_delay() >= game.get_desired_delay()) //waiting for random 5 to 10 seconds
				led_reaction.turn_on();

			static constexpr int64_t termination_time = 3;
			if (game.get_actual_delay() - game.get_desired_delay() >= termination_time) //if no one presses a button for 3 seconds, the game terminates
				states = States::finish;
		}
		break;

		case States::result:
		{
			if (game.get_button1_flag())
			{
				if (led_reaction.get_state() == HIGH)
				{
					led_reaction.turn_off();
					player1.increase_score();
					cout << player1.get_name() << " gets a point." << endl;
					led_player1.turn_on_3_sec();
					states = States::preperation;
				}
				else if (led_reaction.get_state() == LOW)
				{
					player2.increase_score();
					cout << "Not so fast " << player1.get_name() << ". " << player2.get_name() << " gets a point." << endl;
					led_player2.turn_on_3_sec();
					states = States::preperation;
				}

				game.set_button1_flag(false);
			}
			else if (game.get_button2_flag())
			{
				if (led_reaction.get_state() == HIGH)
				{
					led_reaction.turn_off();
					player2.increase_score();
					cout << player2.get_name() << " gets a point." << endl;
					led_player2.turn_on_3_sec();
					states = States::preperation;
				}
				else if (led_reaction.get_state() == LOW)
				{
					player1.increase_score();
					cout << "Not so fast " << player2.get_name() << ". " << player1.get_name() << " gets a point." << endl;
					led_player1.turn_on_3_sec();
					states = States::preperation;
				}

				game.set_button2_flag(false);
			}
		}
		break;

		case States::finish:
		{
			if (game.get_played_rounds() <= game.get_rounds_to_play())
			{
				led_reaction.turn_off();
				cout << "The game terminated due to inactivity." << endl;
			}
			else
			{
				cout << "Current score: " << player1.get_name() << " [" << player1.get_score() << " : "
					<< player2.get_score() << "] " << player2.get_name() << endl;
				if (player1.get_score() > player2.get_score())
				{
					cout << player1.get_name() << " wins!" << endl;
					led_player1.blink_5_sec();
				}
				else if (player2.get_score() > player1.get_score())
				{
					cout << player2.get_name() << " wins!" << endl;
					led_player2.blink_5_sec();
				}
				else
				{
					cout << "It's a tie!" << endl;
					both_leds_blink(led1_pin, led2_pin);
				}
			}
			
			game.set_loop(false);
		}
		break;

		default:
		{
			cout << "That wasn't supposed to happen." << endl;
		}
		break;
		}
	}
	return 0;
}

// --------------------- Functions ---------------------

void button_setup()
{
	static constexpr auto button1_pin = 0;
	static constexpr auto button2_pin = 2;

	wiringPiSetup();
	pinMode(button1_pin, INPUT);
	pinMode(button2_pin, INPUT);

	pullUpDnControl(button1_pin, PUD_DOWN); //pull to ground
	pullUpDnControl(button2_pin, PUD_DOWN); //pull to ground

	wiringPiISR(button1_pin, INT_EDGE_RISING, &button1_pressed); //interrupt
	wiringPiISR(button2_pin, INT_EDGE_RISING, &button2_pressed); //interrupt
}

void button1_pressed()
{
	game.set_button1_flag(true);
	states = States::result;
}

void button2_pressed()
{
	game.set_button2_flag(true);
	states = States::result;
}

void both_leds_blink(int pin1, int pin2) //both player_leds blink for 5 seconds
{
	for (int i = 0; i < 5; i++)
	{
		digitalWrite(pin1, HIGH);
		digitalWrite(pin2, HIGH);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, LOW);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}