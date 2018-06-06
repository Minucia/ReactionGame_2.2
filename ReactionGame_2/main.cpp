/*
******************************************
Reaction Game v 3.1
by Michaela Neuhold & Jakob Soukup

OSD, 06.06.2018
******************************************
 */


// ____________________________ Includes ____________________________

#include "Game_data.h"
#include "Game_logic.h"
#include "piproxy.h"


// ____________________________ Function Prototypes ____________________________

void button1_pressed();
void button2_pressed();
void interrupt_setup();


// ____________________________ Global Namespace ____________________________

using namespace std;


// ____________________________ Global Object ____________________________

Game_data game_data{ true, false, false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //setting loop, button1_flag, button2_flag and played_rounds is important


// ____________________________ Main Function ____________________________

int main()
{
	game_data.read_json();
	Game_logic logic{ game_data };
	interrupt_setup();
	logic.play();
}

// ____________________________ Functions ____________________________

void interrupt_setup()
{
	wiringPiISR(game_data.button1_pin_, INT_EDGE_RISING, &button1_pressed); //interrupt
	wiringPiISR(game_data.button2_pin_, INT_EDGE_RISING, &button2_pressed); //interrupt
}

void button1_pressed()
{
	game_data.set_button1_flag(true);
}

void button2_pressed()
{
	game_data.set_button2_flag(true);
}