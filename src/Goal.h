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
	void init(const v2& pos,GoalOrientation orientation);
	void render();
	bool checkIntersection(const v2& ballPos);
private:
	Item m_Items[MAX_ITEMS];
	GoalOrientation _orientation;
	v2 _position;
	v2 _dimension;
};

