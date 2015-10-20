#include "EnergyRing.h"
#include <math\GameMath.h>
#include <sprites\SpriteBatch.h>
#include <utils\font.h>
#include "Constants.h"

void EnergyRing::draw(const v2& center) {
	float angle = 0.0f;
	uint32 steps = value / 5;
	float r1 = 40.0f;
	float step = DEGTORAD(360.0f / 20.0f);
	char buffer[10];
	sprintf_s(buffer, 10, "%d", value);
	v2 size = ds::sprites::getTextSize(buffer);
	int cx = center.x - size.x * 0.5f;
	int cy = center.y - size.y * 0.5f;
	ds::sprites::drawText(cx, cy, buffer,1.0f,1.0f,textColor);
		
	for (uint32 i = 0; i < steps; ++i) {
		float x = center.x + cos(angle) * r1;
		float y = center.y + sin(angle) * r1;
		ds::sprites::draw(v2(x, y), ds::math::buildTexture(ds::Rect(75, 0, 6, 8)), angle, 1.0f, 1.0f, COLORS[colorIndex]);
		angle += step;
	}
	for (uint32 i = steps; i < 20; ++i) {
		float x = center.x + cos(angle) * r1;
		float y = center.y + sin(angle) * r1;
		ds::sprites::draw(v2(x, y), ds::math::buildTexture(ds::Rect(75, 0, 6, 8)), angle, 1.0f, 1.0f, ds::Color(32,32,32,255));
		angle += step;
	}
}

bool EnergyRing::tick(float dt) {
	if (flashTimer > 0.0f) {
		flashTimer -= dt;
	}
	textColor.r = 1.0f - flashTimer;
	textColor.g = 1.0f - flashTimer;
	textColor.b = 1.0f - flashTimer;

	timer += dt;
	if (timer >= 1.0f) {
		timer -= 1.0f;
		--value;
	}
	if (value < 0) {
		value = 0;
	}
	return value > 0;
}

void EnergyRing::inc(int v) {
	value += v;
	if (value > 100) {
		value = 100;
	}
}

void EnergyRing::flash(float ttl) {
	flashTimer = ttl;
}