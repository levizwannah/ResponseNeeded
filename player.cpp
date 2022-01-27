#include "player.h"

int Player::consecutiveMiss;
int Player::maxConsecutiveMiss;

Player::Player() {
	this->life = 0;
}