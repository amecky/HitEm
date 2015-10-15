#include "Trails.h"
#include <math\GameMath.h>
#include <sprites\SpriteBatch.h>

const int MAX_TRAILS = 2048;

// -------------------------------------
// constructor
// -------------------------------------
Trails::Trails(GameSettings* settings) : _settings(settings) {
	_array.initialize(MAX_TRAILS);
	_texture = ds::math::buildTexture(75, 0, 8, 8);
}

// -------------------------------------
// destructor
// -------------------------------------
Trails::~Trails() {
}

// -------------------------------------
// update
// -------------------------------------
void Trails::update(float dt) {
	for (int i = 0; i < _array.countAlive; ++i) {
		_array.timer[i].x += dt;
		_array.timer[i].y = _array.timer[i].x / _settings->trailTTL;
		_array.scale[i] = lerp(_settings->trailMinSize, _settings->trailMaxSize, _array.timer[i].y);
		_array.color[i].a = 1.0f - _array.timer[i].y * 0.6f;
	}
	uint32 cnt = 0;
	while (cnt < _array.countAlive) {
		if (_array.timer[cnt].y >= 1.0f ) {
			_array.kill(cnt);
		}
		++cnt;
	}
}

// -------------------------------------
// emit
// -------------------------------------
void Trails::emit(const TrailSettings& trailSettings){
	uint32 start = _array.countAlive;
	uint32 end = start + trailSettings.count;
	if (end > _array.count) {
		end = _array.count;
	}

	for (int i = start; i < end; ++i) {
		float r = ds::math::random(_settings->trailRadius.x, _settings->trailRadius.y);
		float angle = ds::math::random(0.0f, TWO_PI);
		_array.position[i].x = trailSettings.position.x + r * cos(angle);
		_array.position[i].y = trailSettings.position.y + r * sin(angle);
		_array.color[i] = trailSettings.color;
		_array.scale[i] = v2(1, 1);
		_array.timer[i] = v2(0, 0);
	}

	for (uint32 i = start; i < end; ++i) {
		_array.wake(i);
	}
}

// -------------------------------------
// render
// -------------------------------------
void Trails::render() {
	for (int i = 0; i < _array.countAlive; ++i) {
		ds::sprites::draw(_array.position[i], _texture, 0.0f, _array.scale[i].x, _array.scale[i].y, _array.color[i]);
	}
}