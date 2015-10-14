#pragma once
#include <particles\ParticleAffector.h>
#include <particles\Particle.h>
#include <particles\ParticleEmitter.h>
#include <particles\ParticleEmitterNode.h>
#include "ImpactEmitter.h"

class BounceParticlesystem {

public:
	BounceParticlesystem(ds::Renderer* renderer,int mtrl);
	virtual ~BounceParticlesystem() {}
	void update(float elapsed);
	uint32 start(const ds::Vec2& pos,float angle);
	void render() {
		//m_FireNode->render();
	}
	void remove(uint32 id);
private:
	ds::ParticleData* m_ParticleData;
	ds::ParticleData* m_InnerParticleData;
	ds::ParticleEmitterNode* m_FireNode;
	ds::ParticleEmitterData* m_EmitterData;
	ds::ParticleEmitterData* m_InnerEmitterData;
	ImpactEmitter* m_Emitter;
};

