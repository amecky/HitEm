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
		if (gui::begin("Ball", &states[0])) {
			gui::InputFloat(21, "Velocity", &settings->ballVelocity);
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