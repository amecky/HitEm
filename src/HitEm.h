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
#include "GameSettings.h"
#include "GameContext.h"

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
	GameSettings* _gameSettings;
	GameContext* _context;
};