#include "Goal.h"


Goal::Goal(void) {
}


Goal::~Goal(void) {
}

void Goal::init() {
	float angle = 0.0f;
	for ( int j = 0; j < MAX_ITEMS; ++j ) {
		Item* item = &m_Items[j];
		item->dir = 0;
		item->angle = 0.0f;
		//m_World->addSpriteEntity(0,0,&item->entity,170,290+10.0*j,ds::Rect(30,320,40,10));		
		item->angle = angle;
		angle += 40.0f;
	}
	for ( int j = 0; j < MAX_ITEMS; ++j ) {
		Item* item = &m_Items[j+MAX_ITEMS];
		item->dir = 0;
		item->angle = 0.0f;
		//m_World->addSpriteEntity(0,0,&item->entity,848,290+10.0*j,ds::Rect(42,320,40,10));		
		item->angle = angle;
		angle += 40.0f;
	}
	for ( int j = 0; j < MAX_ITEMS; ++j ) {
		Item* item = &m_Items[j+MAX_ITEMS*2];
		item->dir = 1;
		item->angle = 0.0f;
		//m_World->addSpriteEntity(0,0,&item->entity,418 + j * 10 ,725,ds::Rect(60,320,10,40));		
		item->angle = angle;
		angle += 40.0f;
	}
	for ( int j = 0; j < MAX_ITEMS; ++j ) {
		Item* item = &m_Items[j+MAX_ITEMS*3];
		item->dir = 1;
		item->angle = 0.0f;
		//m_World->addSpriteEntity(0,0,&item->entity,418 + j * 10 ,50,ds::Rect(60,332,10,40));		
		item->angle = angle;
		angle += 40.0f;
	}
}

void Goal::update(float elapsed) {
	for ( int j = 0; j < MAX_ITEMS*4; ++j ) {
		Item* item = &m_Items[j];
		float sx = 0.8f + sin(DEGTORAD(item->angle)) * 0.15f;
		item->angle += 360.0f * elapsed * 2.5f;			
		if ( item->angle > 360.0f ) {
			item->angle -= 360.0f;
		}
		if ( item->dir == 0 ) {
			//item->entity.setScale(sx,1.0f);
		}
		else {
			//item->entity.setScale(1.0f,sx);
		}
	}
}
