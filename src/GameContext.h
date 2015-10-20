#pragma once
#include <utils\GameTimer.h>

struct Score {

	int points;
	int seconds;
	int minutes;
	int goals;
	int wrongGoals;

};

struct GameContext {

	Score score;
	ds::GameTimer timer;

	void resetScore() {
		score.points = 0;
		score.goals = 0;
		score.wrongGoals = 0;
		score.seconds = 0;
		score.minutes = 0;
	}
};

