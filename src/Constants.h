#pragma once
#include <utils\Color.h>

const ds::Color CL_BLUE = ds::Color(0.0f,0.5f,1.0f,1.0f);
const ds::Color CL_ORANGE = ds::Color(1.0f,0.5f,0.0f,1.0f);

const float CENTER_X = 512.0f;
const float CENTER_Y = 384.0f;
const float RING_RADIUS = 350.0f;
const float BALL_RADIUS = 16.0f;
const float PLAYER_RADIUS = 20.0f;
const float HALF_SIZE = 16.0f;
const float BALL_SIZE = 32.0f;
const float BALL_GROW_TTL = 0.5f;
// red, yellow, green, blue
const ds::Rect GOAL_RECTS[] = {ds::Rect(32,160,30,20),ds::Rect(32,192,20,30),ds::Rect(64,160,30,20),ds::Rect(64,192,20,30)};

// red, green, blue, yellow
const ds::Rect BALL_TEXTURES[] = {ds::Rect(0,0,32,32), ds::Rect(0,64,32,32),ds::Rect(0,96,32,32),ds::Rect(0,32,32,32)};

struct Score {
	int points;
	int seconds;
	int minutes;
	int goals;
	int wrongGoals;
	int sticky;
};