#pragma once
#include <Vector.h>

struct GameSettings {

	float ballVelocity;

	GameSettings() {
		ballVelocity = 400.0f;
	}

};

namespace settings {

	void save(GameSettings* settings);

	void load(GameSettings* settings);

	void showDialog(GameSettings* settings,v2* pos, int* states);
}

