#pragma once
#include <utils\Color.h>
#include <renderer\render_types.h>

const ds::Color CL_BLUE = ds::Color(0.0f,0.5f,1.0f,1.0f);
const ds::Color CL_ORANGE = ds::Color(1.0f,0.5f,0.0f,1.0f);

const float CENTER_X = 512.0f;
const float CENTER_Y = 384.0f;
const float RING_RADIUS = 350.0f;
const float BALL_RADIUS = 14.0f;
const float PLAYER_RADIUS = 25.0f;
const float HALF_SIZE = 16.0f;
const float BALL_SIZE = 32.0f;

const ds::Color COLORS[] = {
	ds::Color(192, 0, 0, 255), // red
	ds::Color(0, 192, 0, 255), // green
	ds::Color(0, 0, 192, 255), // blue
	ds::Color(192, 192, 0, 255) // yellow
};

// red, yellow, green, blue
const ds::Rect GOAL_RECTS[] = {ds::Rect(32,160,30,20),ds::Rect(32,192,20,30),ds::Rect(64,160,30,20),ds::Rect(64,192,20,30)};

// red, green, blue, yellow
//const ds::Rect BALL_TEXTURES[] = {ds::Rect(0,0,32,32), ds::Rect(0,64,32,32),ds::Rect(0,96,32,32),ds::Rect(0,32,32,32)};
const ds::Rect BALL_TEXTURES[] = { ds::Rect(300, 0, 26, 26), ds::Rect(300, 52, 26, 26), ds::Rect(300, 78, 26, 26), ds::Rect(300, 26, 26, 26) };


