#pragma once
#include <Vector.h>
#include <utils\Color.h>

struct EnergyRing {

	int value;
	int colorIndex;
	float timer;

	EnergyRing() {}
	~EnergyRing() {}
	
	void draw(const v2& center);

	bool tick(float dt);

};

