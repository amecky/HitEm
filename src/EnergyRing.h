#pragma once
#include <Vector.h>
#include <utils\Color.h>

struct EnergyRing {

	int value;
	int colorIndex;
	float timer;
	float flashTimer;
	ds::Color textColor;

	EnergyRing() : value(0) , timer(0.0f) , colorIndex(-1) , flashTimer(0.0f) , textColor(ds::Color::WHITE) {}
	~EnergyRing() {}
	
	void draw(const v2& center);

	bool tick(float dt);

	void inc(int v);

	void flash(float ttl);

};

