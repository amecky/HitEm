#include "MainGameState.h"
#include <sprites\SpriteBatch.h>
#include "..\Constants.h"

const v2 RING_POSITIONS[] = {
	v2( 80, 680), // red
	v2( 80,  80), // green
	v2(940, 680), // blue
	v2(940,  80) // yellow
};

MainGameState::MainGameState(GameSettings* settings,GameContext* context) : ds::GameState("MainGame"), _settings(settings) , _context(context) {
	_bat.position = v2(512, 384);
	_bat.texture = ds::math::buildTexture(340, 0, 50, 50);
	_trails = new Trails(_settings);
	_state = 1;
	_startPos = v2(20, 580);
	_settingsPos = v2(720, 740);
	_settingsState = 1;
	_showSettings = false;
	_showGoals = true;
	_tickEnergy = true;
	_showBalls = true;
	_autoRespawn = true;
	_goals[0].init(v2(160, 384), GO_HORIZONTAL);
	_goals[1].init(v2(512, 740), GO_VERTICAL);
	_goals[2].init(v2(870, 384), GO_HORIZONTAL);
	_goals[3].init(v2(512,  30), GO_VERTICAL);	
}


MainGameState::~MainGameState() {
	delete _trails;
}

// -------------------------------------------------------
// init
// -------------------------------------------------------
void MainGameState::init() {

}

// -------------------------------------------------------
// activate
// -------------------------------------------------------
void MainGameState::activate() {
	for (int i = 0; i < 4; ++i) {
		_energies[i].colorIndex = i;
		_energies[i].value = 100;
		_energies[i].timer = 0.0f;
	}
	createBall(0);
	createBall(1);
	createBall(2);
	createBall(3);
	_context->resetScore();
	_mode = GM_PREPARING;
	_timer = 0.0f;
	_context->timer.reset();
	_context->timer.start();
}

// -------------------------------------------------------
// Check if position is inside goal
// -------------------------------------------------------
//           green(1)
//          --------
//  red(0) |       | blue (2)
//          --------
//          yellow(3)
//
int MainGameState::checkGoal(const v2& ballPos) {
	for (int i = 0; i < 4; ++i) {
		if (_goals[i].checkIntersection(ballPos)) {
			return i;
		}
	}
	return -1;
}

// -------------------------------------------------------
// Update
// -------------------------------------------------------
int MainGameState::update(float dt) {
	v2 mp = ds::renderer::getMousePosition();
	float angle = 0.0f;
	v2 bp = _bat.position;
	ds::math::follow(mp, bp, &angle, 2.0f, 5.0f*dt);
	if (bp.x > 200.0f && bp.x < 820.0f && bp.y > 80.0f && bp.y < 700.0f) {
		_bat.position = bp;
	}
	if (_mode == GM_PREPARING) {
		_timer += dt;
		if (_timer > _settings->prepareMatchTime) {
			_mode = GM_RUNNING;
		}
	}
	else {

		_context->timer.tick(dt);

		moveBalls(dt);

		for (int i = 0; i < 4; ++i) {
			if (_balls[i].mode == BM_FLYING) {
				int ret = checkGoal(_balls[i].position);
				if (ret != -1) {
					if (ret == i) {
						LOG << "--> correct one!";
						++_context->score.goals;
						_energies[i].inc(5);
						_energies[i].flash(1.5f);
					}
					else {
						++_context->score.wrongGoals;
					}
					if (_autoRespawn) {
						respawn(i);
					}
					else {
						_balls[i].mode = BM_STICKY;
					}
				}
			}
		}

		if (_tickEnergy) {
			for (int i = 0; i < 4; ++i) {
				_energies[i].tick(dt);
			}
		}
		// check if ALL energies are <= 0
		int cnt = 0;
		for (int i = 0; i < 4; ++i) {
			if (_energies[i].value <= 0) {
				++cnt;
			}
		}
		if (cnt == 4) {
			_context->timer.stop();
			return 1;
		}

		_trails->update(dt);
		
	}
	return 0;
}

// -------------------------------------------------------
// render
// -------------------------------------------------------
void MainGameState::render() {
	ds::sprites::draw(v2(CENTER_X, CENTER_Y), ds::math::buildTexture(ds::Rect(300, 400, 400, 400)), 0.0f, 2.0f, 2.0f);
	for (int i = 0; i < 4; ++i) {
		_energies[i].draw(RING_POSITIONS[i]);
	}

	if (_mode == GM_RUNNING) {
		_trails->render();

		if (_showBalls) {
			for (int i = 0; i < 4; ++i) {
				Ball& ball = _balls[i];
				ds::sprites::draw(ball.position, ball.texture, 0.0f, ball.scale, ball.scale);
			}
		}
	}
	else {
		ds::Color clr = ds::Color::WHITE;
		clr.a = 1.0f - _timer / _settings->prepareMatchTime;
		ds::sprites::draw(v2(512,384),ds::math::buildTexture(590.0f,0.0f,400.0f,60.0f),0.0f,1.0f,1.0f,clr);
	}

	ds::sprites::draw(_bat.position, _bat.texture);

	for (int i = 0; i < 4; ++i) {
		_goals[i].render();
	}

	

	gui::start(1, &_startPos);
	if (gui::begin("Test", &_state)) {
		gui::CheckBox(5, "Show Balls", &_showBalls);
		//gui::CheckBox(7, "Tick energy", &_tickEnergy);
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
		settings::showDialog(_settings, &_settingsPos, &_settingsState);
	}
}

// -------------------------------------------------------
// move balls
// -------------------------------------------------------
void MainGameState::moveBalls(float dt) {
	if (_showBalls) {
		for (int i = 0; i < 4; ++i) {
			Ball& b = _balls[i];
			if (b.mode == BM_GROWING) {
				b.timer += dt;
				float norm = b.timer / _settings->ballGrowTTL;
				b.scale = 0.1f + norm * 0.9f;
				if (b.timer >= _settings->ballGrowTTL) {
					b.mode = BM_FLYING;
					b.scale = 1.0f;
				}
			}
			else if ( b.mode == BM_FLYING) {

				if (sqr_length(b.prev - b.position) > (_settings->trailDistance * _settings->trailDistance)) {
						
					_trailSettings.position = b.prev;
					_trailSettings.color = COLORS[b.colorIndex];
					_trailSettings.count = 6;
					_trailSettings.angle = 0.0f;
					_trails->emit(_trailSettings);
					b.prev = b.position;
				}
				b.position += b.velocity * dt;
				bool push = false;
				if (b.position.x < 160.0f || b.position.x > 870.0f) {
					b.velocity.x *= -1.0f;
					push = true;
				}
				if (b.position.y < 30.0f || b.position.y > 730.0f) {
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
	}
}

// -------------------------------------------------------
// Respawn ball
// -------------------------------------------------------
void MainGameState::respawn(int index) {
	Ball& ball = _balls[index];
	float angle = getRandomAngle(ball.colorIndex);
	float xp = CENTER_X + (RING_RADIUS - BALL_SIZE) * cos(DEGTORAD(angle));
	float yp = CENTER_Y + (RING_RADIUS - BALL_SIZE) * sin(DEGTORAD(angle));
	ball.position = v2(xp, yp);
	ball.prev = v2(xp, yp);
	angle += 180.0f;
	float vx = _settings->ballVelocity * cos(DEGTORAD(angle));
	float vy = _settings->ballVelocity * sin(DEGTORAD(angle));
	ball.velocity = v2(vx, vy);
	ball.angle = angle;
	ball.mode = BM_GROWING;
	ball.scale = 0.1f;
	ball.timer = 0.0f;
}

// -------------------------------------------------------
// Get random angle based on sector
// -------------------------------------------------------
float MainGameState::getRandomAngle(int sector) {
	float start = 15.0f;
	float max = 75.0f;
	if (sector == 1) {
		start = 105.0f;
	}
	else if (sector == 2) {
		start = 195.0f;
	}
	else if (sector == 3) {
		start = 285.0f;
	}
	return ds::math::random(start, start + max);//start + rand()*max;
}

// -------------------------------------------------------
// Create ball
// -------------------------------------------------------
void MainGameState::createBall(int colorIndex) {
	Ball& b = _balls[colorIndex];
	b.colorIndex = colorIndex;
	b.texture = ds::math::buildTexture(BALL_TEXTURES[colorIndex]);
	respawn(colorIndex);
}

// -------------------------------------------------------
// on char
// -------------------------------------------------------
int MainGameState::onChar(int ascii) {
	if (ascii == 's') {
		_showSettings = !_showSettings;
	}
	if (ascii == 'e') {
		return 1;
	}
	return 0;
}