#pragma once
#include "opengl/glwrappers.hpp"
#include "../math/vec.hpp"
#include "sprite.hpp"


class AttackSprite : public Sprite {
public:
	AttackSprite(const std::string & path, int w, int h);
	~AttackSprite();

	void render();


	int w, h;
	int src_w, src_h;
	int original_w, original_h;

	std::vector<ScreenCoord> frames;
	void addAnimation(int start, int end);

	ScreenCoord getFramePos();

	std::vector<AttackAnimation> animations;

	//int counter;
	//int frame_index;
	int animation_index;

	int frames_w;
	int frames_h;
};

class AttackAnimation {
public:
	AttackAnimation(int animationIndex, ScreenCoord pos);
	~AttackAnimation();

	int animationIndex;
	int frame_index;
	int counter;
	ScreenCoord pos; //to setsourcepos
};