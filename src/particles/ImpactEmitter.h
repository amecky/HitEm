#pragma once
#include <particles/ParticleEmitter.h>

class ImpactEmitter : public ds::ParticleEmitter {

public:
	ImpactEmitter(ds::ParticleEmitterData* emitterData) : ds::ParticleEmitter(emitterData) , m_StartAngle(0.0f) , m_Range(45.0) , m_Orientation(0) {}
	void createParticles(ds::ParticleBuffer* buffer,ds::ParticleData* particleData);
	void setStartAngle(float angle) {
		m_StartAngle = angle;
	}
	void setRange(float range) {
		m_Range = range;
	}
	void setOrientation(int orientation) {
		m_Orientation = orientation;
	}
private:
	int m_Orientation;
	float m_StartAngle;
	float m_Range;
};

