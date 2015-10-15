#include "EnergyRing.h"
#include <math\GameMath.h>
#include <sprites\SpriteBatch.h>
#include <utils\font.h>

namespace EnergyRing {

	void draw(const v2& center, int percentage, const ds::Color& color) {
		float angle = 0.0f;
		uint32 steps = percentage / 5;
		float r1 = 60.0f;
		float step = DEGTORAD(360.0f / 20.0f);
		char buffer[10];
		sprintf_s(buffer, 10, "%d", percentage);
		v2 size = ds::sprites::getTextSize(buffer);
		int cx = center.x - size.x * 0.5f;
		int cy = center.y - size.y * 0.5f;
		ds::sprites::drawText(cx, cy, buffer);
		
		for (uint32 i = 0; i < steps; ++i) {
			float x = center.x + cos(angle) * r1;
			float y = center.y + sin(angle) * r1;
			ds::sprites::draw(v2(x, y), ds::math::buildTexture(ds::Rect(75, 0, 12, 12)), angle, 1.0f, 1.0f, color);
			angle += step;
		}
		for (uint32 i = steps; i < 20; ++i) {
			float x = center.x + cos(angle) * r1;
			float y = center.y + sin(angle) * r1;
			ds::sprites::draw(v2(x, y), ds::math::buildTexture(ds::Rect(75, 0, 12, 12)), angle, 1.0f, 1.0f, ds::Color(32,32,32,255));
			angle += step;
		}
	}

}