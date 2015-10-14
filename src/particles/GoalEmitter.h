#pragma once
#include <particles\ParticleSystem.h>

class GoalEmitter : public ds::ParticleEmitter {

public:
	GoalEmitter() : ds::ParticleEmitter(5,ds::Rect(75,0,12,12),2.0f,1.0f) , m_StartAngle(0.0f) , m_Range(90.0) , m_Orientation(0) {}
	void createParticles(const ds::Vec3& startPosition,ds::Particles& particles);
	void setStartAngle(float angle) {
		m_StartAngle = angle;
	}
	void setRange(float range) {
		m_Range = range;
	}
	void setOrientation(int orientation) {
		m_Orientation = orientation;
	}
	void setColorIndex(int colIdx) {
		m_ColorIndex = colIdx;
	}
private:
	int m_Orientation;
	int m_ColorIndex;
	float m_StartAngle;
	float m_Range;
};



