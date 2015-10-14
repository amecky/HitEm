#pragma once
#include <world\World.h>

const int MAX_ITEMS = 20;

class Goal  {

struct Item {
	float timer;
	float angle;
	int dir;
};

public:
	Goal(void);
	~Goal(void);
	void update(float elapsed);
	void init();
private:
	Item m_Items[MAX_ITEMS*4];
};

