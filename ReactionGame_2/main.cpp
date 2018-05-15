/*
******************************************
Reaction Game v 2.0 (incl. IO-Manager)
by Michaela Neuhold & Jakob Soukup

OSD, 14.05.2018
******************************************
 */


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
#include "Game_logic.h"


// ____________________________ Enumeration Class ____________________________


// ____________________________ Function Prototypes ____________________________

void button_setup();
void button1_pressed();
void button2_pressed();


// ____________________________ Global Namespace ____________________________

using namespace std;


// ____________________________ Global Object ____________________________

Game_data game{ true, false, false, 0, 0, 0, 0, 0 }; //setting loop, button1_flag, button2_flag and played_rounds is important


// ____________________________ Main Function ____________________________

int main()
{
	button_setup();

	Game_logic logic{ game };
	logic.play();
}

// --------------------- Functions ---------------------

void button_setup()
{
	// MFA TODO you don't reserve or release your pins here!
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
}

void button2_pressed()
{
	game.set_button2_flag(true);
}