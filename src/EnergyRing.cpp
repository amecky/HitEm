#include "EnergyRing.h"
#include <math\GameMath.h>


EnergyRing::EnergyRing(const v2& center) : m_Center(center) {
}


EnergyRing::~EnergyRing(void) {
}

void EnergyRing::draw(int percentage) {
	float angle = 0.0f;
	uint32 steps = percentage / 4;
	float r1 = 60.0f;
	float r2 = r1 + 20.0f;
	float step = 360.0f / 25.0f;
	//m_SpriteBatch->draw(m_Center.x,m_Center.y,ds::Rect(700,0,155,155));
	for ( uint32 i = 0; i < steps; ++i ) {
		float alpha2 = angle + step;			
		float x = m_Center.x + cos(DEGTORAD(angle)) * r1;
		float y = m_Center.y + sin(DEGTORAD(angle)) * r1;
		float ra = ds::math::reflect(DEGTORAD(angle));
		//m_SpriteBatch->draw(x,y,ds::Rect(75,0,12,12),ra,1.0f,1.0f,ds::Color(192,0,0,255));

		angle += step;
	}	
}
