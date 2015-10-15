#include "HitEm.h"
#include "utils\Log.h"
#include "Constants.h"
#include <sprites\SpriteBatch.h>

ds::BaseApp *app = new HitEm(); 

HitEm::HitEm() : ds::BaseApp() {
	_settings.screenWidth = 1024;
	_settings.screenHeight = 768;
	_settings.clearColor = ds::Color(10,10,10,255);	
	_gameSettings = new GameSettings;
	_settingsPos = v2(720, 740);
	_settingsState = 1;
	_state = 1;
	_startPos = v2(20, 580);
	_trails = new Trails(_gameSettings);
	_showSettings = false;
	_tickEnergy = false;
}

HitEm::~HitEm() {
	delete _trails;
	delete _gameSettings;
}

// -------------------------------------------------------
// Load content and prepare game
// -------------------------------------------------------
bool HitEm::loadContent() {	
	int texture = ds::renderer::loadTexture("textures");
	assert(texture != -1);
	// balls
	ds::sprites::initializeTextSystem(texture, "xscale");
	gui::initialize();
	settings::load(_gameSettings);
	_showBalls = false;
	createBall(0);
	createBall(1);
	createBall(2);
	createBall(3);
	for (int i = 0; i < 4; ++i) {
		_energies[i].index = i;
		_energies[i].value = 100;
		_energies[i].timer = 0.0f;
	}
	_bat.position = v2(512, 384);
	_bat.texture = ds::math::buildTexture(375, 63, 52, 52);
	_redGoal.init(GO_VERTICAL);
	return true;
}

void HitEm::moveBalls(float dt) {
	if (_showBalls) {
		for (int i = 0; i < 4; ++i) {
			Ball& b = _balls[i];
			if (!b.sticky) {
				if (b.mode == BM_GROWING) {
					b.timer += dt;
					float norm = b.timer / _gameSettings->ballGrowTTL;
					b.scale = 0.1f + norm * 0.9f;
					if (b.timer >= _gameSettings->ballGrowTTL) {
						b.mode = BM_FLYING;
						b.scale = 1.0f;
					}
				}
				else {

					if (sqr_length(b.prev - b.position) > (_gameSettings->trailDistance * _gameSettings->trailDistance)) {
						TrailSettings s;
						s.position = b.prev;
						s.color = COLORS[b.colorIndex];
						s.count = 6;
						s.angle = 0.0f;
						_trails->emit(s);
						b.prev = b.position;
					}
					b.position += b.velocity * dt;
					bool push = false;
					if (b.position.x < 180.0f || b.position.x > 840.0f) {
						b.velocity.x *= -1.0f;
						push = true;
					}
					if (b.position.y < 60.0f || b.position.y > 720.0f) {
						b.velocity.y *= -1.0f;
						push = true;
					}
					if (push) {
						b.position += b.velocity * dt;
					}
					v2 diff = b.position - _bat.position;
					if ( sqr_length(diff) <= (( BALL_RADIUS+PLAYER_RADIUS) * (BALL_RADIUS+PLAYER_RADIUS)) ) {
						v2 norm = normalize(diff);
						v2 pushBack = ds::math::getShiftVector(b.position,BALL_RADIUS,_bat.position,PLAYER_RADIUS+2.0f);
						pushBack *= 1.1f;
						b.position = b.position + pushBack;
						b.velocity = reflect(b.velocity,norm);
					}
				}
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
	}
}
// -------------------------------------------------------
// Update
// -------------------------------------------------------
void HitEm::update(float dt) {
	
	v2 mp = getMousePos();
	//m_Bat.position = mp;
	float angle = 0.0f;
	mp.y = 768.0f - mp.y;
	v2 bp = _bat.position;
	ds::math::follow(mp,bp,&angle,2.0f,5.0f*dt);
	if (bp.x > 200.0f && bp.x < 820.0f && bp.y > 80.0f && bp.y < 700.0f) {
		_bat.position = bp;
	}
	

	_redGoal.update(dt);

	_trails->update(dt);

	moveBalls(dt);

	if (_tickEnergy) {
		for (int i = 0; i < 4; ++i) {
			_energies[i].timer += dt;
			if (_energies[i].timer >= 1.0f) {
				_energies[i].timer -= 1.0f;
				--_energies[i].value;
			}
		}
	}
	/*
	if (_showBalls) {
		for (int i = 0; i < 4; ++i) {
			Ball& b = _balls[i];
			if (!b.sticky) {
				if (b.mode == BM_GROWING) {
					b.timer += dt;
					float norm = b.timer / _gameSettings->ballGrowTTL;
					b.scale = 0.1f + norm * 0.9f;
					if (b.timer >= _gameSettings->ballGrowTTL) {
						b.mode = BM_FLYING;
						b.scale = 1.0f;
					}
				}
				else {

					if (sqr_length(b.prev - b.position) > (_gameSettings->trailDistance * _gameSettings->trailDistance)) {
						TrailSettings s;
						s.position = b.prev;
						s.color = COLORS[b.colorIndex];
						s.count = 6;
						s.angle = 0.0f;
						_trails->emit(s);
						b.prev = b.position;
					}

					b.position += b.velocity * dt;
					float mx = b.position.x - CENTER_X;
					float my = b.position.y - CENTER_Y;
					float r = sqrt(mx * mx + my*my);
					if (r > (RING_RADIUS - HALF_SIZE)) {
						float da = ds::math::getAngle(normalize(b.velocity), v2(1, 0));
						LOG << "da " << RADTODEG(da);
						int goal = checkGoal(b.position.x, b.position.y);
						if (goal != -1) {
							LOG << "Goal " << goal << " ball " << b.colorIndex;
							respawn(i);
						}
						else {
							//LOG(logINFO) << "ball " << b.index << " bouncing at " << b.position.x << " " << b.position.y;
							//m_BounceParticles->start(b.position,b.angle);
							b.angle += 180.0f;
							if (b.angle > 360.0f) {
								b.angle -= 360.0f;
							}
							b.velocity.x *= -1.0f;
							b.velocity.y *= -1.0f;
							b.position += b.velocity * dt;
							float cvs = ds::math::getAngle(b.velocity, v2(1, 0));
							v2 expPos = b.position;
							ds::vector::addRadial(expPos, -30.0f, cvs);
							float va = RADTODEG(ds::math::reflect(cvs));
							if (va > 360.0f) {
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
	}
	*/
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
	_trails->render();
	if (_showBalls) {
		for (int i = 0; i < 4; ++i) {
			Ball& ball = _balls[i];
			ds::sprites::draw(ball.position, ball.texture, 0.0f, ball.scale, ball.scale);
		}
	}
	ds::sprites::draw(_bat.position, _bat.texture);

	EnergyRing::draw(v2(80, 680), _energies[0].value, ds::Color(192, 0, 0, 255)); // red
	EnergyRing::draw(v2(80, 80), _energies[1].value, ds::Color(0, 192, 0, 255)); // green
	EnergyRing::draw(v2(940, 680), _energies[2].value, ds::Color(0, 0, 192, 255)); // blue
	EnergyRing::draw(v2(940, 80), _energies[3].value, ds::Color(192, 192, 0, 255)); // yellow

	_redGoal.render();
	
	
	gui::start(1, &_startPos);
	if (gui::begin("Test", &_state)) {
		gui::CheckBox(5, "Show Balls", &_showBalls);
		gui::CheckBox(7, "Tick energy", &_tickEnergy);
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
		if (gui::Button(6, "Emitt trail")) {
			TrailSettings s;
			s.position = v2(512, 384);
			s.color = ds::Color(255, 0, 0, 255);
			s.count = 6;
			s.angle = 0.0f;
			_trails->emit(s);
		}
	}
	gui::end();
	if (_showSettings) {
		settings::showDialog(_gameSettings, &_settingsPos, &_settingsState);
	}
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
	ball.prev = v2(xp, yp);
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
}

// -------------------------------------------------------
// On button up
// -------------------------------------------------------
void HitEm::OnButtonUp( int button,int x,int y ) {
}

void HitEm::OnChar( char ascii,unsigned int keyState ) {
	if ( ascii == 's' ) {
		_showSettings = !_showSettings;
	}
}