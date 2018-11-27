#define SDL_MAIN_HANDLED

#include <iostream>

#include "engine/core.hpp"
#include "game/menu.hpp"
#include "game/combat.hpp"

#include "engine/mixer.hpp"
#include "game/combat.hpp"
#include "game/customization.hpp"
#include "game/skillTree.hpp"


int main(int argc, char* argv[]) {

	// Initialize the engine
	if (!Core::init("Wyverns Nest", 1280, 720)) {
		std::cerr << "Initialization failed\n";
		return 1;
	}

	/*
	// Example mixer usage
	Core::Mixer::loadAudio("res/music/track1.wav", AudioType::Music);
	Core::Mixer::playAudio("res/music/track1.wav", 1, 0.8f);
	*/

	Core::setDebugMode(true);

	// Combat * state = new Combat("res/data/levels/level1.json");
	// Combat * state = new Combat();
	Customization * state = new Customization();
	// SkillTree * state = new SkillTree();
	// Menu * state = new Menu();
	Core::setState(state);

	// Main engine loop
	while (Core::running()) {
		Core::update();
	}

	return 0;

}