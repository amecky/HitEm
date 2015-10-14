#include "HitEm.h"
#include "utils\Log.h"
#include "Constants.h"
#include <sprites\SpriteBatch.h>

ds::BaseApp *app = new HitEm(); 

HitEm::HitEm() : ds::BaseApp() {
	_settings.screenWidth = 1024;
	_settings.screenHeight = 768;
	_settings.clearColor = ds::Color(10,10,10,255);	
	m_StickyBall = 0;
	_gameSettings = new GameSettings;
	_settingsPos = v2(820, 740);
	_settingsState = 1;
	_state = 1;
	_startPos = v2(20, 740);

}

HitEm::~HitEm() {
	delete _gameSettings;
}

// -------------------------------------------------------
// Load content and prepare game
// -------------------------------------------------------
bool HitEm::loadContent() {	
	int texture = ds::renderer::loadTexture("textures");
	assert(texture != -1);
	// balls
	gui::initialize();
	settings::load(_gameSettings);

	createBall(0);
	createBall(1);
	createBall(2);
	createBall(3);

	
	return true;
}

// -------------------------------------------------------
// Update
// -------------------------------------------------------
void HitEm::update(float dt) {
	/*
	v2 mp = getMousePos();
	//m_Bat.position = mp;
	float angle = 0.0f;
	mp.y = 768.0f - mp.y;
	ds::Vec2 bp = m_Bat.getPosition();
	ds::math::follow(mp,bp,&angle,2.0f,5.0f*gameTime.elapsed);
	m_Bat.setPosition(bp);
	m_Catcher.setPosition(bp);
	*/
	for ( int i = 0; i < 4; ++i ) {
		Ball& b = _balls[i];
		if ( !b.sticky ) {
			if ( b.mode == BM_GROWING ) {
				b.timer += dt;
				float norm = b.timer / BALL_GROW_TTL;
				b.scale = 0.1f + norm * 0.9f;
				if ( b.timer >= BALL_GROW_TTL ) {
					b.mode = BM_FLYING;
					b.scale = 1.0f;				
				}
			}
			else {
				b.position += b.velocity * dt;
				float mx = b.position.x - CENTER_X;
				float my = b.position.y - CENTER_Y;
				float r = sqrt(mx * mx + my*my);
				if ( r > ( RING_RADIUS - HALF_SIZE ) ) {
					float da = ds::math::getAngle(normalize(b.velocity),v2(1,0));
					LOG << "da " << RADTODEG(da);
					int goal = checkGoal(b.position.x, b.position.y);
					if ( goal != -1 ) {
						LOG << "Goal " << goal << " ball " << b.colorIndex;						
						respawn(i);
					}
					else {
						//LOG(logINFO) << "ball " << b.index << " bouncing at " << b.position.x << " " << b.position.y;
						//m_BounceParticles->start(b.position,b.angle);
						b.angle += 180.0f;
						if ( b.angle > 360.0f ) {
							b.angle -= 360.0f;
						}
						b.velocity.x *= -1.0f;
						b.velocity.y *= -1.0f;
						b.position += b.velocity * dt;
						float cvs = ds::math::getAngle(b.velocity,v2(1,0));
						v2 expPos = b.position;
						ds::vector::addRadial(expPos,-30.0f,cvs);
						float va = RADTODEG(ds::math::reflect(cvs));
						if ( va > 360.0f ) {
							va -= 360.0f;
						}
						LOG << "VA " << va;
						//m_BorderEmitter->setAngle(va - 45.0f,va + 45.0f);
						//m_BorderExp.start(expPos);
					}
				}
				//m_Trail.setEmitterPosition(bp);
			}
			//v2 diff = b.position - m_Bat.getPosition();
			//if ( ds::vector::sqrLength(diff) <= (( BALL_RADIUS+PLAYER_RADIUS) * (BALL_RADIUS+PLAYER_RADIUS)) ) {
				//ds::Vec2 norm = ds::vector::normalize(diff);
				//ds::Vec2 pushBack = ds::math::getShiftVector(b.entity.getPosition(),BALL_RADIUS,m_Bat.getPosition(),PLAYER_RADIUS+2.0f);
				//pushBack *= 1.1f;
				//b.entity.setPosition(b.entity.getPosition() + pushBack);
				//b.velocity = reflect(b.velocity,norm);
			//}
		}
		// sticky ball
		else {
			//b.entity.setPosition(m_Bat.getPosition());
			//ds::Vec2 bp = b.entity.getPosition();
			//b.angle += DEGTORAD(270.0f) * gameTime.elapsed;
			//ds::vector::addRadial(bp,40.0f,b.angle);
			//b.entity.setPosition(bp);
		}
	}
	/*
	for ( int i = 0; i < 4; ++i ) {
		m_Goals[i]->update(gameTime.elapsed);
	}
	*/
}

// -------------------------------------------------------
// Reflect
// -------------------------------------------------------
v2 HitEm::reflect(const v2& vel,const v2& norm) {
	float dp = dot(vel,norm);
	return v2(vel.x - 2.0f * dp * norm.x,vel.y -2.0f * dp * norm.y);	
}

// -------------------------------------------------------
// isOutside - checks if position is outside of ring
// -------------------------------------------------------
bool HitEm::isOutside(const v2& pos) {
	float mx = pos.x - CENTER_X;
	float my = pos.y - CENTER_Y;
	float r = sqrt(mx * mx + my*my);
	if ( r > ( RING_RADIUS - BALL_SIZE ) ) {
		return true;
	}
	return false;
}

// -------------------------------------------------------
// Draw
// -------------------------------------------------------
void HitEm::draw() {
	ds::sprites::draw(v2(CENTER_X,CENTER_Y),ds::math::buildTexture(ds::Rect(300,400,400,400)),0.0f,2.0f,2.0f);
	for (int i = 0; i < 4; ++i) {
		Ball& ball = _balls[i];
		ds::sprites::draw(ball.position, ball.texture, 0.0f, ball.scale, ball.scale);
	}
	/*
	m_SpriteBatch->draw(m_Bat.position.x,m_Bat.position.y,ds::Rect(32,0,45,41));
	for ( int i = 0;i < 4; ++i ) {
		Ball* ball = &m_Balls[i];
		m_SpriteBatch->draw(ball->position.x,ball->position.y,BALL_TEXTURES[ball->colorIndex]);
	}
	m_RedRing->draw(75.0f);
	m_GreenRing->draw(45.0f);
	m_SpriteBatch->end();	
	renderer->set2DCameraOff();
	*/
	gui::start(1, &_startPos);
	if (gui::begin("Test", &_state)) {
		if (gui::Button(1, "Respawn 1")) {
			respawn(0);
		}
		if (gui::Button(2, "Respawn 2")) {
			respawn(1);
		}
		if (gui::Button(3, "Respawn 3")) {
			respawn(2);
		}
		if (gui::Button(4, "Respawn 4")) {
			respawn(3);
		}
	}
	gui::end();

	settings::showDialog(_gameSettings, &_settingsPos, &_settingsState);
}

// -------------------------------------------------------
// Respawn ball
// -------------------------------------------------------
void HitEm::respawn(int index) {
	Ball& ball = _balls[index];
	float angle = getRandomAngle(ball.colorIndex);
	float xp = CENTER_X + (RING_RADIUS - BALL_SIZE) * cos(DEGTORAD(angle));
	float yp = CENTER_Y + (RING_RADIUS - BALL_SIZE) * sin(DEGTORAD(angle));
	ball.position = v2(xp,yp);
	angle += 180.0f;
	float vx = _gameSettings->ballVelocity * cos(DEGTORAD(angle));
	float vy = _gameSettings->ballVelocity * sin(DEGTORAD(angle));
	ball.velocity = v2(vx,vy);
	ball.angle = angle;
	ball.mode = BM_GROWING;
	ball.scale = 0.1f;
	ball.timer = 0.0f;
}

// -------------------------------------------------------
// Create ball
// -------------------------------------------------------
void HitEm::createBall(int colorIndex) {
	Ball& b = _balls[colorIndex];	
	b.colorIndex = colorIndex;
	b.sticky = false;
	b.texture = ds::math::buildTexture(BALL_TEXTURES[colorIndex]);
	respawn(colorIndex);
	/*
	float angle = getRandomAngle(colorIndex);
	float xp = 512 + (RING_RADIUS - BALL_SIZE) * cos(DEGTORAD(angle));
	float yp = 384 + (RING_RADIUS - BALL_SIZE) * sin(DEGTORAD(angle));
	
	angle += 180.0f;
	float vx = BALL_VELOCITY * cos(DEGTORAD(angle));
	float vy = BALL_VELOCITY * sin(DEGTORAD(angle));
	b.velocity = ds::Vec2(vx,vy);
	b.entity.setPosition(ds::Vec2(xp,yp));
	b.mode = BM_GROWING;
	b.timer = 0.0f;
	b.colorIndex = colorIndex;
	b.sticky = false;
	b.angle = angle;
	//b.scale = 1.0f;
	*/
}

// -------------------------------------------------------
// Check if position is inside goal
// -------------------------------------------------------
int HitEm::checkGoal(int mx,int my) {
	// upper goal
	if ( check2D(v2(mx,my),450,35,120,20) ) {
		return 2;
	}
	// lower goal
	if ( check2D(v2(mx,my),450,725,120,20) ) {
		return 0;
	}
	// left goal
	if ( check2D(v2(mx,my),160,320,20,120) ) {
		return 1;
	}
	// right goal
	if ( check2D(v2(mx,my),840,320,20,120) ) {
		return 3;
	}
	return -1;
}

// -------------------------------------------------------
// Check 2D
// -------------------------------------------------------
bool HitEm::check2D(v2 ballPos,int x2,int y2,int w2,int h2) {
	int x1 = ballPos.x;
	int y1 = ballPos.y;
	int w1 = 32;
	int h1 = 32;	
	int left1 = x1;
	int left2 = x2;
	int right1 = left1 + w1;
	int right2 = left2 + w2;
	int top1 = y1;
	int top2 = y2;
	int bottom1 = top1 + h1;
	int bottom2 = top2 + h2;

	if (bottom1 < top2) return false;
	if (top1 > bottom2) return false;

	if (right1 < left2) return false;
	if (left1 > right2) return false;
	return true;
}

// -------------------------------------------------------
// Get random angle based on sector
// -------------------------------------------------------
float HitEm::getRandomAngle(int sector) {
	float start = 15.0f;
	float max = 75.0f;
	if ( sector == 1 ) {
		start = 105.0f;
	}
	else if ( sector == 2 ) {
		start = 195.0f;
	}
	else if ( sector == 3 ) {
		start = 285.0f;
	}
	return ds::math::random(start, start + max);//start + rand()*max;
}

// -------------------------------------------------------
// On button down
// -------------------------------------------------------
void HitEm::OnButtonDown( int button,int x,int y ) {
	/*
	// if no ball is sticky
	if ( !m_Catcher.isActive()) {
		m_Catcher.setActive(true);
	}
	 if ( m_StickyBall == 0 ) {
		 for ( int i = 0; i < 4; ++i ) {
			 Ball* b = &m_Balls[i];
			 if ( b.mode != BM_GROWING ) {				 
				ds::Vec2 diff = b.entity.getPosition() - m_Bat.getPosition();
				if ( ds::vector::sqrLength(diff) <= (( BALL_RADIUS+PLAYER_RADIUS) * (BALL_RADIUS+PLAYER_RADIUS)) * 8.0f) {
					if ( m_StickyBall == 0 ) {
						b.angle = ds::math::getTargetAngle(m_Bat.getPosition(),b.entity.getPosition());
						b.sticky = true;
						m_StickyBall = b;
					}
				}
			 }
		 }
	 }
	 */
}

// -------------------------------------------------------
// On button up
// -------------------------------------------------------
void HitEm::OnButtonUp( int button,int x,int y ) {
	/*
	// if there actually is a sticky ball
	if ( m_StickyBall != 0 ) {
		m_StickyBall->sticky = false;
		m_StickyBall->velocity = ds::math::getRadialVelocity(RADTODEG(m_StickyBall->angle),300.0f);
		// release it and set new velocity
		m_StickyBall = 0;
		m_Catcher.setActive(false);
	}

	ds::Vec2 mp = getMousePos();
	mp.y = 768.0f - mp.y;
	ds::Vec2 v;
	v.x = mp.x - CENTER_X;
	v.y = mp.y - CENTER_Y;
	float da = ds::math::getAngle(ds::vector::normalize(v),ds::Vec2(1,0));
	LOG(logINFO) << "clicked da: " << RADTODEG(da);
	*/
}

void HitEm::OnChar( char ascii,unsigned int keyState ) {
	if ( ascii == 'a' ) {
		//m_BorderExp.start(ds::Vec2(400,400));
	}
}