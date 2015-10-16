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


public:	
	HitEm();
	virtual ~HitEm();
	bool loadContent();
	const char* getTitle() {
		return "HitEm";
	}
	void init();
	void update(float dt);
	void draw();
private:
	Goal _redGoal;
	GameSettings* _gameSettings;
};