#pragma once
#include <sprites\SpriteArray.h>
#include "GameSettings.h"

// -------------------------------------
// Trail array
// -------------------------------------
struct TrailArray {

	v2* position;
	v2* scale;
	float* rotation;
	v2* timer;
	ds::Color* color;
	char* buffer;

	uint32 count;
	uint32 countAlive;

	TrailArray() : count(0), countAlive(0), buffer(0) {}

	~TrailArray() {
		if (buffer != 0) {
			delete[] buffer;
		}
	}

	void initialize(unsigned int maxTrails) {
		int size = maxTrails * (sizeof(v2) * 2 + sizeof(float) + sizeof(v2) + sizeof(ds::Color));
		buffer = new char[size];
		position = (v2*)(buffer);
		scale = (v2*)(position + maxTrails);
		rotation = (float*)(scale + maxTrails);
		timer = (v2*)(rotation + maxTrails);		
		color = (ds::Color*)(timer + maxTrails);
		count = maxTrails;
		countAlive = 0;
	}

	void swapData(uint32 a, uint32 b) {
		if (a != b) {
			position[a] = position[b];
			scale[a] = scale[b];
			rotation[a] = rotation[b];
			timer[a] = timer[b];
			color[a] = color[b];
		}
	}

	void kill(uint32 id) {
		if (countAlive > 0) {
			swapData(id, countAlive - 1);
			--countAlive;
		}
	}

	void wake(uint32 id) {
		if (countAlive < count)	{
			swapData(id, countAlive);
			++countAlive;
		}
	}

};

// -------------------------------------
// Trail settings
// -------------------------------------
struct TrailSettings {

	v2 position;
	float angle;
	ds::Color color;
	int count;

};
// -------------------------------------
// Trails
// -------------------------------------
class Trails {

public:
	Trails(GameSettings* settings);
	~Trails();
	void update(float dt);
	void emit(const TrailSettings& trailSettings);
	void render();
private:
	TrailArray _array;
	GameSettings* _settings;
	ds::Texture _texture;
};

