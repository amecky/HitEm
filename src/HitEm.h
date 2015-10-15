#pragma comment(lib, "Diesel2D.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxerr.lib")
#pragma warning(disable : 4995)

#pragma once
#include "base\BaseApp.h"
#include "dxstdafx.h"
#include <renderer\render_types.h>
#include "EnergyRing.h"
#include "Goal.h"
#include "GameSettings.h"
#include "Trails.h"

class HitEm : public ds::BaseApp {

enum BallMode {
	BM_FLYING,
	BM_GROWING
};

struct Bat {
	v2 position;
	ds::Texture texture;
};

struct Energy {

	int index;
	int value;
	float timer;

};

struct Ball {
	v2 velocity;
	v2 position;
	v2 prev;
	int colorIndex;
	BallMode mode;
	float timer;
	bool sticky;
	float angle;
	ds::Texture texture;
	float scale;
};

public:	
	HitEm();
	virtual ~HitEm();
	bool loadContent();
	const char* getTitle() {
		return "HitEm";
	}
	void update(float dt);
	void draw();
	void OnButtonDown( int button,int x,int y );
	void OnButtonUp( int button,int x,int y );
	void OnChar( char ascii,unsigned int keyState );
private:
	void createBall(int colorIndex);
	float getRandomAngle(int sector);
	bool isOutside(const v2& pos);
	int checkGoal(int mx,int my);
	bool check2D(v2 ballPos,int x2,int y2,int w2,int h2);
	void respawn(int index);
	v2 reflect(const v2& vel,const v2& norm);
	void moveBalls(float dt);
	void handleEnergy(float dt);

	Ball _balls[4];
	bool _showBalls;
	bool _tickEnergy;
	Energy _energies[4];
	Goal _redGoal;
	v2 _startPos;
	int _state;
	GameSettings* _gameSettings;
	v2 _settingsPos;
	int _settingsState;
	bool _showSettings;
	Trails* _trails;
	Bat _bat;

};