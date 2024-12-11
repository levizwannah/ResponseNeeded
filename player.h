#pragma once
#include <string>
#include "playerLife.h"
#include "score.h"

class Player
{
public:
	int life;
	int score;
	PlayerLife playerLife;
	Score playerScore;
	static int maxConsecutiveMiss;
	static int consecutiveMiss;

	Player();
};

