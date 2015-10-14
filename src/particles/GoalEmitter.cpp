#include "GoalEmitter.h"

const float START_ANGLES[] = {45.0f,135.0f,225.0f,315.0f};
const ds::Color COLORS[] = {ds::Color(1.0f,0.0f,0.0f,1.0f),ds::Color(1.0f,1.0f,0.0f,1.0f),ds::Color(0.0f,1.0f,0.0f,1.0f),ds::Color(0.0f,0.0f,1.0f,1.0f)};

void GoalEmitter::createParticles(const ds::Vec3& startPosition,ds::Particles& particles) {
	int gx = startPosition.x + 16;
	int gy = startPosition.y + 16;
	ds::Vec2 pos = ds::Vec2(gx,gy);
	float angle = START_ANGLES[m_Orientation];
	int steps = 20;
	float step = 90.0f / static_cast<float>(steps);	
	float dx = 16.0f / static_cast<float>(steps);
	for ( int x = 0; x < steps; ++x ) {
		ds::Vec2 pp = pos;		
		if ( m_Orientation == 0 ) {
			pp.x = pos.x - dx * x;
			pp.y = gy;
		}
		else if ( m_Orientation == 1 ) {
			pp.x = gx;
			pp.y = pos.y - dx * x;
		}
		else if ( m_Orientation == 2 ) {
			pp.x = pos.x + dx * x;
			pp.y = gy;
		}
		else if ( m_Orientation == 3 ) {
			pp.x = gx;
			pp.y = pos.y + dx * x;
		}		
		ds::Particle p;			
		p.textureRect = ds::Rect(75,0,8,8);
		p.position = ds::Vec3(pp.x,pp.y,0.0f);
		p.initialPosition = ds::Vec3(pp.x,pp.y,0.0f);
		p.size = ds::Vec3(8,8,0);			
		p.timer = 0.0f;
		p.alive = true;
		p.ttl = 1.0f;
		float vr = gEngine->random(70.0f,120.0f);
		ds::Vec2 vel = ds::math::getRadialVelocity(angle,vr);
		p.velocity = ds::Vec3(vel.x,vel.y,0.0f);
		p.color = COLORS[m_ColorIndex];
		particles.append(p);
		angle += step;
		if ( angle > 360.0f ) {
			angle -= 360.0f;
		}
	}
}

