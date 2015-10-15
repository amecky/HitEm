#pragma once
#include <world\World.h>

const int MAX_ITEMS = 20;

enum GoalOrientation {
	GO_VERTICAL,
	GO_HORIZONTAL
};

class Goal  {

struct Item {
	float timer;
	float angle;
	int dir;
	GoalOrientation orientation;
	ds::Texture texture;
	v2 scale;
	v2 position;
};

public:
	Goal(void);
	~Goal(void);
	void update(float elapsed);
	void init(GoalOrientation orientation);
	void render();
private:
	Item m_Items[MAX_ITEMS];
};

