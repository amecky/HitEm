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

class HitEm : public ds::BaseApp {

enum BallMode {
	BM_FLYING,
	BM_GROWING
};

struct Ball {
	v2 velocity;
	v2 position;
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
	

	
	Goal m_Goal;
	

	int m_Mtrl;
	int m_BackgroundHandle;
	int m_RingHandle;
	int m_ObjectsHandle;

	
	EnergyRing* m_RedRing;
	EnergyRing* m_GreenRing;
	//BounceParticlesystem* m_BounceParticles;

	Ball _balls[4];
	v2 _startPos;
	int _state;
	GameSettings* _gameSettings;
	v2 _settingsPos;
	int _settingsState;
	//Bat m_Bat;
	ds::BitmapFont* m_BitmapFont;
	//HUD* m_HUD;
	//ds::PostProcessor* m_PostProcessor;
	uint32 m_AddBlendState;
	uint32 m_DefaultBS;
	Ball* m_StickyBall;
	uint32 m_OuterRingIdx;
};