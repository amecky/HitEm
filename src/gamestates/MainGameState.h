#pragma once
#include <base\GameState.h>
#include <renderer\render_types.h>
#include <ui\IMGUI.h>
#include "..\EnergyRing.h"
#include "..\GameSettings.h"
#include "..\Trails.h"

class MainGameState : public ds::GameState {

enum GameMode {
	GM_PREPARING,
	GM_RUNNING
};

struct Bat {
	v2 position;
	ds::Texture texture;
};

enum BallMode {
	BM_FLYING,
	BM_GROWING
};

struct Score {
	int correct;
	int wrong;
};

struct Ball {
	v2 velocity;
	v2 position;
	v2 prev;
	int colorIndex;
	BallMode mode;
	float timer;
	float angle;
	ds::Texture texture;
	float scale;
};

public:
	MainGameState(GameSettings* settings);
	virtual ~MainGameState();
	void init();
	int update(float dt);
	void render();
	void activate();
	int onChar(int ascii);
private:
	void moveBalls(float dt);
	void createBall(int colorIndex);
	void respawn(int index);
	float getRandomAngle(int sector);
	int checkGoal(const v2& ballPos);

	GameSettings* _settings;
	EnergyRing _energies[4];
	bool _tickEnergy;
	Bat _bat;
	Ball _balls[4];
	bool _showBalls;
	Trails* _trails;
	TrailSettings _trailSettings;
	v2 _startPos;
	int _state;
	v2 _settingsPos;
	int _settingsState;
	bool _showSettings;
	Score _score;
	GameMode _mode;
	float _timer;
};

