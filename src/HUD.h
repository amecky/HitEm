#pragma once
#include <addons\HudNode.h>
#include <renderer\Renderer.h>
#include <renderer\render_types.h>
#include <nodes\QuadMeshNode.h>
#include "EnergyRing.h"
#include <vector>

class HUD : public ds::HudNode {

struct ColorCounter {
	uint32 textIndex;
	float timer;
	int value;
};

typedef std::vector<EnergyRing*> Rings;
public:
	HUD(ds::Renderer* renderer,int material,int bitmapFont,ds::QuadMeshNode* energyNode);
	virtual ~HUD() {}
	void setPercentage(int index,int percentage);
	void addPercentage(int index,int percentage);
	const int getPercentage(int index) const {
		return m_Counter[index].value;
	}
	void update(float elapsed);
	void reset();
	void start();
	void stop();
	const bool isActive() const {
		return m_Active;
	}	
	const bool isRunning() const;
private:
	ColorCounter m_Counter[4];
	bool m_Active;
	ds::QuadMeshNode* m_EnergyNode;
	Rings m_Rings;
};

