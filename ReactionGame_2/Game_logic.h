#pragma once

#include "Game_data.h"
#include "Player.h"
#include "Digital_output.h"
#include "Digital_input.h"


class Game_logic
{
public:
	Game_logic(Game_data& game_data);
	void play();

private:
	void read_json();
	void read_player_names();
	void read_num_rounds() const;
	void play_round();
	void prepare_round();
	void toggle_reaction_led();
	void check_round_results();
	void on_player_faster(Player& player, Digital_output& led_player);
	void on_player_too_fast(Player& winner, Player& loser, Digital_output& winner_led);
	static void both_leds_blink();
	void finish_game();
	
	Player player1_;
	Player player2_;
	Digital_output led_reaction_;
	Digital_output led_player1_;
	Digital_output led_player2_;
	Digital_input button_player1_;
	Digital_input button_player2_;
	Game_data& game_;

	enum class States { preperation, reaction_led, result, finish };
	States states_;
};

