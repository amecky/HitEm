#include "ImpactEmitter.h"

// -----------------------------------------------
//  ImpactEmitter
// -----------------------------------------------
void ImpactEmitter::createParticles(ds::ParticleBuffer* buffer,ds::ParticleData* particleData) {
	int gx = m_Position.x + 16;
	int gy = m_Position.y;
	ds::Vec2 pos = ds::Vec2(gx,gy);
	float angle = m_StartAngle + 180.0f;
	float steps = (m_Range + m_StartAngle) / 4.0f;
	//LOG(logINFO) << "creating particles at " << pos.x << " " << pos.y << " start angle " << m_StartAngle;
	for ( int x = 0; x < 4; ++x ) {
		ds::Particle* p = buffer->createParticle(particleData);
		ds::Vec2 pp = pos;
		/*
		if ( m_Orientation == 0 ) {
			pp.x = pos.x - x * 4;
			pp.y = gy;
		}
		else if ( m_Orientation == 1 ) {
			pp.x = gx;
			pp.y = pos.y - x * 4;
		}
		else if ( m_Orientation == 2 ) {
			pp.x = pos.x + x * 4;
			pp.y = gy;
		}
		else if ( m_Orientation == 0 ) {
			pp.x = gx;
			pp.y = pos.y + x * 4;
		}
		*/
		p->startPos = ds::Vec2(pp.x,pp.y);
		float vr = random(15.0f,45.0f);
		ds::Vec2 vel = ds::math::getRadialVelocity(angle,vr);
		p->acceleration = ds::Vec2(0,0);	
		p->velocity = ds::Vec2(vel.x,-vel.y);
		p->color = particleData->startColor;
		p->rotation = 0.0f;		
		angle += steps;
		if ( angle > 360.0f ) {
			angle -= 360.0f;
		}
	}
}
