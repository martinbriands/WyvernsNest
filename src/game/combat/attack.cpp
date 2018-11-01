#include "attack.hpp"

#include "unit.hpp"
#include "../combat.hpp"

Attack::Attack(std::string name,
	Unit * source,
	AttackType type,
	AttackEffect * effect,
	AttackAoE aoe,
	int range)
	:
	name(name),
	source(source),
	type(type),
	effect(effect),
	aoe(aoe),
	validSprite("res/test8.png"),
	targetValidSprite("res/test6.png"),
	targetInvalidSprite("res/test7.png"),
	range(range)
{
	/*
	validSprite.setSize(213, 180);
	targetValidSprite.setSize(213, 180);
	targetInvalidSprite.setSize(213, 180);
	*/
}

void Attack::attack(ScreenCoord pos, Combat& combat) {
	if (isValid(pos)) {
		effect->attack(pos, combat);
	}
	// TODO: figure out how to apply the attack effect to the surrounding aoe
}

// Display the valid attack tiles on the grid
void Attack::renderValidGrid() {
	switch (type) {
	case AttackType::MELEE: {
		validSprite.setPos((source->position.x() - 1) * tile_width, source->position.y() * tile_height);
		validSprite.render();
		validSprite.setPos(source->position.x() * tile_width, (source->position.y() - 1) * tile_height);
		validSprite.render();
		validSprite.setPos((source->position.x() + 1) * tile_width, source->position.y() * tile_height);
		validSprite.render();
		validSprite.setPos(source->position.x() * tile_width, (source->position.y() + 1) * tile_height);
		validSprite.render();
	} break;
	case AttackType::PLUS: {
		// TODO: More descriptive name than plus
		// TODO: Display the sprites correctly
		// TODO: Add a range property and figure out valid grid based off of range
	} break;
	case AttackType::RANGED: {
		for (int y = -range; y < range + 1 ; y++) {
			for (int x = -range; x < range + 1 ; x++) {
				if (!(y == x && y == 0)) {
					if (abs(x) + abs(y) <= range) {
						validSprite.setPos((source->position.x() + x) * tile_width, (source->position.y() + y) * tile_height);
						validSprite.render();
					}
				}
			}
		}
	} break;
	}

	int mouseX; int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int x = static_cast<int>(floor(mouseX / tile_width));
	int y = static_cast<int>(floor(mouseY / tile_height));

	if (isValid(ScreenCoord(x, y))) {
		targetValidSprite.setPos(x * tile_width, y * tile_height);
		targetValidSprite.render();
	}
	else {
		targetInvalidSprite.setPos(x * tile_width, y * tile_height);
		targetInvalidSprite.render();
	}
	// TODO: get the mouse position somehow to render whether the target position is valid
	/*
	if (isValid(pos)) {
		//TODO values here are temporary
		targetValidprite.setPos(pos.x() * 213, pos.y() * 180);
		targetValidprite.setSize(213, 180);
		targetValidprite.render();
	}
	else {
		//TODO values here are temporary
		targetInvalidSprite.setPos(pos.x() * 213, pos.y() * 180);
		targetInvalidSprite.setSize(213, 180);
		targetInvalidSprite.render();
	}
	*/
}

bool Attack::isValid(ScreenCoord pos) {
	switch (type) {
	case AttackType::MELEE: {
		int x_diff = std::abs(pos.x() - source->position.x());
		int y_diff = std::abs(pos.y() - source->position.y());
		if (x_diff + y_diff == 1) return true;
		return false;
		/*
		if ((pos.x() == source->position.x() + 1 || pos.x() == source->position.x() - 1) && pos.y() == source->position.y()) {
			return true;
		}
		else if ((pos.y() == source->position.y() + 1 || pos.y() == source->position.y() - 1) && pos.x() == source->position.x()) {
			return true;
		}
		*/
	} break;
	case AttackType::PLUS: {
		// TODO: More descriptive name than plus
		// TODO: Calculate whether the pos is valid based off a range property
	} break;
	case AttackType::RANGED: {
		int x_diff = std::abs(pos.x() - source->position.x());
		int y_diff = std::abs(pos.y() - source->position.y());
		if (x_diff + y_diff <= range) return true;
		return false;
	} break;
	}
	return false;
}

void Attack::setTileSize(int width, int height) {
	tile_width = width;
	tile_height = height;
	validSprite.setSize(tile_width, tile_height);
	targetValidSprite.setSize(tile_width, tile_height);
	targetInvalidSprite.setSize(tile_width, tile_height);
}

void DamageEffect::attack(ScreenCoord pos, Combat & combat) {
	Unit * unit = combat.getUnitAt(pos);
	if (unit) {
		unit->takeDamage(damage);
		// Do something if the unit dies
	}
}
