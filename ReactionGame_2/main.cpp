/*
******************************************
Reaction Game v 2.0 (incl. IO-Manager)
by Michaela Neuhold & Jakob Soukup

OSD, 14.05.2018
******************************************
 */


// ____________________________ Includes ____________________________

#include "Game_data.h"
#include "Game_logic.h"
#include "piproxy.h"
//#include "json.hpp"


// ____________________________ Function Prototypes ____________________________

//void button_setup();
void button1_pressed();
void button2_pressed();
void interrupt_setup();


// ____________________________ Global Namespace ____________________________

using namespace std;


// ____________________________ Global Object ____________________________

Game_data game_data{ true, false, false, 0, 0, 0, 0, 0 }; //setting loop, button1_flag, button2_flag and played_rounds is important


// ____________________________ Main Function ____________________________

int main()
{
	//button_setup();

	Game_logic logic{ game_data };
	interrupt_setup();
	logic.play();
}

// --------------------- Functions ---------------------

void interrupt_setup()
{
	static constexpr auto button1_pin = 0;
	static constexpr auto button2_pin = 2;

	wiringPiISR(button1_pin, INT_EDGE_RISING, &button1_pressed); //interrupt
	wiringPiISR(button2_pin, INT_EDGE_RISING, &button2_pressed); //interrupt
}
/*void button_setup()
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
}*/

void button1_pressed()
{
	game_data.set_button1_flag(true);
}

void button2_pressed()
{
	game_data.set_button2_flag(true);
}