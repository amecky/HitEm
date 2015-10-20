#include "GameOverState.h"
#include <utils\Log.h>
#include <sprites\SpriteBatch.h>
#include <renderer\graphics.h>
#include <base\GameStateMachine.h>

GameOverState::GameOverState(ds::DialogManager* gui, GameContext* context) : ds::GameState("GameOver"), _context(context), _gui(gui) {
}


GameOverState::~GameOverState() {
}

// --------------------------------------------
// activate
// --------------------------------------------
void GameOverState::activate() {
	_gui->activate("GameOver");	
	
	ds::GUIDialog* dlg = _gui->get("GameOver");
	std::string str;
	ds::string::formatInt(_context->score.goals, str);
	dlg->updateText(12, str);
	ds::string::formatInt(_context->score.wrongGoals, str);
	dlg->updateText(8, str);
	ds::string::formatTime(_context->timer.getMinutes(), _context->timer.getSeconds(), str);
	int seconds = _context->timer.getSeconds() + _context->timer.getMinutes() * 60;
	int diff = seconds - 100;
	dlg->updateText(14, str);
	_context->score.points = _context->score.goals * 1000 + diff * 500;
	ds::string::formatInt(_context->score.points, str);
	dlg->updateText(16, str);
	
}

// --------------------------------------------
// activate
// --------------------------------------------
void GameOverState::deactivate() {
	_gui->deactivate("GameOver");
}

// --------------------------------------------
// update
// --------------------------------------------
int GameOverState::update(float dt) {
	// nothing to do
	return 0;
}

// --------------------------------------------
// click
// --------------------------------------------
int GameOverState::onGUIButton(ds::DialogID dlgID, int button) {	
	return button;
}

// --------------------------------------------
// render
// --------------------------------------------
void GameOverState::render() {
}


