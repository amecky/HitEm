#pragma once
#include <Vector.h>

class EnergyRing {

public:
	EnergyRing(const v2& center);
	~EnergyRing(void);
	void draw(int percentage);
private:
	v2 m_Center;	
};

