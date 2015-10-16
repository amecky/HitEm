#include "GameSettings.h"
#include <utils\StringUtils.h>
#include <utils\FileUtils.h>
#include <ui\IMGUI.h>
#include <utils\Log.h>

namespace settings {

	void save(GameSettings* settings) {
		if (!ds::file::saveBinary<GameSettings>("Settings", settings)) {
			LOG << "Error saving file";
		}
	}

	void load(GameSettings* settings) {
		if (!ds::file::loadBinary<GameSettings>("Settings", settings)) {
			LOG << "Error loading file";
		}
	}

	void showDialog(GameSettings* settings, v2* pos, int* states) {
		gui::start(20, pos);
		if (gui::begin("Settings", &states[0])) {
			gui::InputFloat(21, "Velocity", &settings->ballVelocity);
			gui::InputFloat(28, "Grow TTL", &settings->ballGrowTTL);			
			gui::InputFloat(24, "Trail TTL", &settings->trailTTL);
			gui::InputVec2(25, "Trail MIN", &settings->trailMinSize);
			gui::InputVec2(26, "Trail MAX", &settings->trailMaxSize);
			gui::InputFloat(27, "Trail Dist", &settings->trailDistance);
			gui::InputVec2(29, "Trail Radius", &settings->trailRadius);
			gui::InputFloat(30, "Prepare timer", &settings->prepareMatchTime);
			gui::beginGroup();
			if (gui::Button(22, "Save")) {
				LOG << "Save pressed";
				save(settings);
			}
			if (gui::Button(23, "Load")) {
				LOG << "Load clicked";
				load(settings);
			}
			gui::endGroup();
		}
		gui::end();
	}
}