#pragma once

#include "Player.h"
#include "Digital_output.h"
#include "Game_data.h"

class Game_logic
{
public:
	Game_logic(Game_data& game_data);
	
	void play();

private:
	void read_player_names();
	void read_num_rounds() const;
	void toggle_reaction_led();
	void on_player_faster(Player& player, Digital_output& led_player);
	void on_player_too_fast(Player& winner, Player& loser, Digital_output& winner_led);
	static void both_leds_blink();
	void check_round_results();
	void finish_game();
	void prepare_round();
	void play_round();

	Player player1_;
	Player player2_;
	Digital_output led_reaction_;
	Digital_output led_player1;
	Digital_output led_player2;
	Game_data& game;

	enum class States { preperation, reaction_led, result, finish };

	States states_;
};

