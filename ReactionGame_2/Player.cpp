
#include "Player.h"

using namespace std;


Player::Player() : name_{ "MusterMaxi" }, score_{ 0 }
{
}

Player::Player(string name, int score = 0) : name_{ name }, score_{ score }
{
}

void Player::set_name(std::string name)
{
	name_ = name;
}


string Player::get_name() const
{
	return name_;
}

void Player::increase_score()
{
	score_++;
}

void Player::reset_score()
{
	score_ = 0;
}

int Player::get_score() const
{
	return score_;
}

