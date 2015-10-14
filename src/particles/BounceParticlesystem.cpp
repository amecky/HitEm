#include "BounceParticlesystem.h"
#include "ImpactEmitter.h"


BounceParticlesystem::BounceParticlesystem(ds::Renderer* renderer,int mtrl) {
	m_FireNode = new ds::ParticleEmitterNode(renderer,mtrl,300);
	m_ParticleData = new ds::ParticleData();
	m_ParticleData->minSize = 1.0f;
	m_ParticleData->maxSize = 1.0f;
	m_ParticleData->textureRect = ds::Rect(0,175,32,32);
	m_ParticleData->initialSize = 10.0f;
	m_ParticleData->ttl = 1.0f;
	m_ParticleData->startColor = ds::Color(255,255,25,255);
	m_ParticleData->endColor = ds::Color(255,255,255,0);
	m_FireNode->addParticleAffector(new ds::ColorAffector());

	m_EmitterData = new ds::ParticleEmitterData();
	m_EmitterData->velocity = 10.0f;
	m_EmitterData->velocityVariance = 5.0f;
	m_EmitterData->ejectionPeriod = 0;

	m_Emitter = new ImpactEmitter(m_EmitterData);
	m_Emitter->addParticleData(m_ParticleData);
	m_Emitter->setOrientation(0);
	uint32 id = m_FireNode->addEmitter(m_Emitter);	
}

void BounceParticlesystem::update(float elapsed) {
	m_FireNode->update(elapsed);
}

uint32 BounceParticlesystem::start(const ds::Vec2& pos,float angle) {
	m_Emitter->setStartAngle(angle);
	m_Emitter->setPosition(pos);	
	m_FireNode->emitParticles();
	return 0;
}

void BounceParticlesystem::remove(uint32 id) {
	m_FireNode->removeEmitter(id);
}

