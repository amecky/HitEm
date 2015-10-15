#pragma once
#include <Vector.h>

struct GameSettings {

	float ballVelocity;
	float ballGrowTTL;

	float trailTTL;
	v2 trailMinSize;
	v2 trailMaxSize;
	float trailDistance;
	v2 trailRadius;

	GameSettings() {
		ballVelocity = 400.0f;
		ballGrowTTL = 0.4f;
		trailTTL = 0.6f;
		trailMinSize = v2(0.6f, 0.6f);
		trailMaxSize = v2(0.2f, 0.2f);
		trailDistance = 15.0f;
		trailRadius = v2(4, 8);
	}

};

namespace settings {

	void save(GameSettings* settings);

	void load(GameSettings* settings);

	void showDialog(GameSettings* settings,v2* pos, int* states);
}

