#include "HitEm.h"
#include "utils\Log.h"
#include "Constants.h"
#include <sprites\SpriteBatch.h>
#include <base\GameStateMachine.h>
#include "gamestates\MainGameState.h"
#include "gamestates\GameOverState.h"

ds::BaseApp *app = new HitEm(); 

HitEm::HitEm() : ds::BaseApp() {
	_settings.screenWidth = 1024;
	_settings.screenHeight = 768;
	_settings.clearColor = ds::Color(10,10,10,255);	
	_gameSettings = new GameSettings;
	_context = new GameContext;
}

HitEm::~HitEm() {
	delete _context;
	delete _gameSettings;
}

// -------------------------------------------------------
// Load content and prepare game
// -------------------------------------------------------
bool HitEm::loadContent() {	
	int texture = ds::renderer::loadTexture("textures");
	assert(texture != -1);
	ds::sprites::initializeTextSystem(texture, "xscale");
	gui::initialize();
	settings::load(_gameSettings);
	initializeGUI();
	stateMachine->add(new MainGameState(_gameSettings));
	stateMachine->add(new GameOverState(&gui,_context));
	stateMachine->connect("GameOver", 1, "MainGame");
	return true;
}

void HitEm::init() {
	stateMachine->activate("GameOver");
}


// -------------------------------------------------------
// Update
// -------------------------------------------------------
void HitEm::update(float dt) {
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
// Draw
// -------------------------------------------------------
void HitEm::draw() {
	
}
