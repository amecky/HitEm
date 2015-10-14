#include "HUD.h"
#include <utils\StringUtils.h>
#include "Constants.h"

const char* ENERGY_TEXTURES[] = {"Red_EnergyCell","Yellow_EnergyCell","Green_EnergyCell","Blue_EnergyCell"};

HUD::HUD(ds::Renderer* renderer,int material,int bitmapFont,ds::QuadMeshNode* energyNode)  
	: ds::HudNode(renderer,material,bitmapFont) , m_EnergyNode(energyNode) {
	for ( int i = 0; i < 4; ++i ) {
		addImage(ds::Vec2(800,i*240),"HUD_BG");
	}	
	for ( int i = 0; i < 4; ++i ) {
		m_Counter[i].textIndex = addText(ds::Vec2(880,175 + i * 125),"100");
	}
	m_Active = false;
	for ( int i = 0; i < 4; ++i ) {
		m_Rings.push_back(new EnergyRing(m_EnergyNode,ds::Vec2(900,180 + i * 125),ENERGY_TEXTURES[i]));
		setPercentage(i,100);
	}
}

void HUD::start() {
	reset();
	m_Active = true;
}

void HUD::stop() {
	m_Active = false;
}

void HUD::reset() {
	for ( int i = 0; i < 4; ++i ) {
		m_Counter[i].timer = 0.0f;
		m_Counter[i].value = 100;
	}
}

// -------------------------------------------------------
// Check if we are still running
// -------------------------------------------------------
const bool HUD::isRunning() const {
	for ( int i = 0; i < 4; ++i ) {
		if ( m_Counter[i].value == 0 ) {
			return false;
		}
	}
	return true;
}
// -------------------------------------------------------
// Update energy ring
// -------------------------------------------------------
void HUD::update(float elapsed) {
	for ( int i = 0; i < 4; ++i ) {
		ColorCounter* cc = &m_Counter[i];
		cc->timer += elapsed;
		if ( cc->timer >= 1.0f ) {
			cc->timer = 0.0f;
			// dec percentage
			cc->value = cc->value - 1;
			if ( cc->value < 0 ) {
				cc->value = 0;
			}
			setPercentage(i,cc->value);
		}
	}
}

// -------------------------------------------------------
// Add percentage
// -------------------------------------------------------
void HUD::addPercentage(int index,int percentage) {
	ColorCounter* cc = &m_Counter[index];
	cc->timer = 0.0f;
	cc->value = cc->value + percentage;
	if ( cc->value > 100 ) {
		cc->value = 100;
	}
	setPercentage(index,cc->value);
}

// -------------------------------------------------------
// 
// -------------------------------------------------------
void HUD::setPercentage(int index,int percentage) {	
	if (  percentage >= 0 ) {
		int x = 880;
		if ( percentage < 100 ) {
			x += 8;
		}
		if ( percentage < 10 ) {
			x += 8;
		}	
		m_Rings[index]->updateRing(percentage);
		//m_Rings[index].energyRing->updateRing(percentage);
		//m_TextNode->setText(m_Rings[index].textIndex,ds::Vec2(x,175 + index * 125),ds::Color(1.0f,1.0f,1.0f,1.0f),ds::string::to_string(percentage));	
		updateText(m_Counter[index].textIndex,ds::string::to_string(percentage));
	}
}