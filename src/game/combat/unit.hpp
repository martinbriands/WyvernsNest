#pragma once

#include "../../engine/core.hpp"

#include "attack.hpp"
#include "../unitData.hpp"

#define DEFAULT_SPRITE_WIDTH 200
#define DEFAULT_SPRITE_HEIGHT 200

// Enumeration of unit types
enum class UnitType {
	PLAYER,
	ENEMY
};

// Enumeration of all possible unit states
enum class UnitState {
	IDLE,
	MOVE,
	ATTACK,
	DONE,
	DEAD
};

class Unit : public Entity {

public:

	Unit();
	Unit(UnitType type);
	Unit(UnitType type, Attack attack1, Attack attack2);

	// The position of the unit in terms of grid coordinates
	Vec2<int> position;
	// The position of the unit in terms of screen coordinates
	ScreenCoord screenPosition;

	// Render methods
	virtual void renderBottom();
	// virtual void renderUnit();	<-- USE THE ORIGINAL ENTITY RENDER FUNCTION FOR THIS
	virtual void renderTop();
	virtual void renderHealth();

	// Getter methods
	UnitState getState() const { return state; }
	UnitType getType() const { return type; }
	// Unit attribute getter methods
	int getStat(Stat stat) const;
	int getSTR() const { return data.strength; }
	int getDEX() const { return data.dexterity; }
	int getINT() const { return data.intelligence; }
	int getCON() const { return data.constitution; }
	int getMoveSpeed() const { return move_speed; }
	int getMaxHealth() const { return maxHealth; }

	// Setter methods
	void setTileSize(int width, int height);
	void setTopMargin(int margin);
	void setState(UnitState newState) { state = newState; }

	// The health variables of the unit
	int health;
	int maxHealth;

	// Utility functions common across all units
	void select();
	void deselect();
	void takeDamage(int damage);
	void heal(int health);
	bool move(Combat& combat, Vec2<int> pos);

	// Utility references to the combat state to access needed data
	Combat * combat;

protected:

	// Variables that contain various useful stats for the unit
	int move_speed;
	bool selected = false;
	void loadPropertiesFromUnitData();

	// State variable of the unit
	UnitState state;
	// The state counter can be used by setting it to 0 and incrementing every frame
	int state_counter;
	inline void startCounter() { state_counter = 0; }
	inline void incrementCounter() { state_counter++; }
	inline bool compareCounter(int num) const { return state_counter >= num; }

	// Variables to help keep track of unit movement
	std::vector<Vec2<int>> path;
	ScreenCoord moveTarget;
	ScreenCoord moveDiff;
	ScreenCoord moveNext;
	// Helper variables for unit movement
	std::vector<ScreenCoord> getPath(Combat & combat, ScreenCoord to);
	// Pathfinding helper methods
	std::vector<ScreenCoord> heuristic(std::vector<std::vector<ScreenCoord>> * open);
	std::vector<ScreenCoord> getValidNeighbours(ScreenCoord pos, Combat & combat);
	// Helper functions to calculate the screen position and movement of the player
	void calculateScreenPositionMovement();
	void incrementMovement();


	// Helper method to calculate the screen position based on grid position
	void calculateScreenPosition();

	// Helper methods/variables needed for proper sprite rendering
	int sprite_width;
	int sprite_height;
	int tile_width, tile_height;
	int top_margin;

	// Virtual functions that units can override to customize functionality
	virtual void takeDamageCallback(int damage);
	virtual void selectCallback();

	// Common sprites used by most units
	Sprite shadow;

private:

	// The type of the unit
	UnitType type;

	// The unit data of the unit
	UnitData data;
	void generateDefaultUnitData();

};