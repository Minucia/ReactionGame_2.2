#pragma once
#include <sstream>


class Player
{
public:
	Player();
	Player(std::string name, int score);
	std::string get_name() const;
	void increase_score();
	void reset_score();
	int get_score() const;

private:
	std::string name_;
	int score_;
};

