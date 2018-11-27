#include "cutscene.hpp"

#include <iostream>
#include <ctime>

Cutscene::Cutscene(State * state, int scene_time, bool timed_scene) {

	// For testing purposes populate sprites with temp images
	m_sprites.push_back(new Sprite("res/test.png"));
	m_sprites.push_back(new Sprite("res/test2.png"));
	m_sprites.push_back(new Sprite("res/test3.png"));
	m_sprites.push_back(new Sprite("res/test4.png"));
	m_sprites.push_back(new Sprite("res/test5.png"));

	m_scene_time = scene_time;
	m_position = 0;
	m_curr_img = m_sprites[m_position];
	m_state = state;
	m_start = std::clock();
	m_timed_scene = timed_scene;
}

Cutscene::~Cutscene() {
	
}

void Cutscene::handleEvent(const SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_a && m_position < m_sprites.size() - 1) {
			m_curr_img = m_sprites[++m_position];
		}
		else if (e.key.keysym.sym == SDLK_a && m_position == m_sprites.size() - 1) {
			changeState(m_state);
		}
	}
}

void Cutscene::update(int delta) {
	if (((std::clock() - m_start) / (double)CLOCKS_PER_SEC) > m_scene_time && m_timed_scene) {
		if (m_position >= m_sprites.size() - 1) {
			changeState(m_state);
		}
		else {
			m_curr_img = m_sprites[++m_position];
			m_start = std::clock();
		}
	}
}

void Cutscene::render() {
	m_curr_img->render();
}
