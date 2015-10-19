#include "Goal.h"


Goal::Goal(void) {
}


Goal::~Goal(void) {
}

void Goal::init(const v2& pos,GoalOrientation orientation) {	
	_orientation = orientation;
	_position = pos;
	if (orientation == GO_VERTICAL) {
		_dimension = v2(180.0f, 20.0f);
	}
	else {
		_dimension = v2(20.0f, 180.0f);
	}


	float angle = 0.0f;
	for ( int j = 0; j < MAX_ITEMS; ++j ) {
		Item* item = &m_Items[j];
		item->dir = 0;
		item->angle = 0.0f;
		item->scale = v2(1, 1);
		item->texture = ds::math::buildTexture(0, 320, 40, 10);
		item->position = v2(170, 290 + 10.0*j);
		item->angle = angle;
		angle += 40.0f;
	}
	/*
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
	*/
}

void Goal::update(float elapsed) {
	/*
	for ( int j = 0; j < MAX_ITEMS; ++j ) {
		Item* item = &m_Items[j];
		float sx = 0.8f + sin(DEGTORAD(item->angle)) * 0.15f;
		item->angle += 360.0f * elapsed * 2.5f;			
		if ( item->angle > 360.0f ) {
			item->angle -= 360.0f;
		}
		if ( item->dir == 0 ) {
			item->scale.x = sx;
		}
		else {
			item->scale.y = sx;
		}
	}
	*/
}

void Goal::render() {
	/*
	for (int j = 0; j < MAX_ITEMS; ++j) {
		Item* item = &m_Items[j];
		ds::sprites::draw(item->position, item->texture, 0.0f, item->scale.x, item->scale.y);
	}
	*/
	if (_orientation == GO_VERTICAL) {
		ds::sprites::draw(_position, ds::math::buildTexture(0.0f, 525.0f, _dimension.x, _dimension.y));
	}
	else {
		ds::sprites::draw(_position, ds::math::buildTexture(0.0f, 500.0f, _dimension.x, _dimension.y));
	}
}

bool Goal::checkIntersection(const v2& ballPos) {
	return ds::math::checkCircleBoxIntersection(ballPos, 14.0f, _position,_dimension);
}
