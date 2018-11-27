#include "attackloader.hpp"

#ifdef _DEBUG
#include <iostream>
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

#include <fstream>

Attack AttackLoader::get(const std::string& name, Unit * unit) {
	if (attacks.find(name) == attacks.end()) return Attack("INVALID", unit, AttackType::INVALID);
	return Attack(attacks.at(name), unit);
}

AttackLoader::AttackLoader() {
	loadAttacks();
}

AttackLoader::~AttackLoader() {
	// Since nothing is allocated on the heap, there is no need to handle any resources here
}

// The helper function to load all attack data from a file
void AttackLoader::loadAttacks() {
	std::ifstream inp(ATTACK_FILE_LOCATION);
	// Use the provided overloaded operators to load the json data
	json data;
	inp >> data;

	// Load all the attacks individually
	for (const json& attack : data["attacks"]) {
		loadAttack(attack);
	}
}

// The helper function to load an attack to the map based on its json data
// TODO: return false if an attack failed to load
bool AttackLoader::loadAttack(const json & data) {

	std::string name = data["name"];
	AttackType type = getTypeFromString(data["type"]);
	int range = data["range"];
	int aoe = data["aoe"];
	bool affect_self = data["affect_self"];
	// Parse the effects here
	std::vector<AttackEffect*> effects;
	for (const json& effect : data["effects"]) {
		effects.push_back(parseEffect(effect));
	}
	if (effects.size() == 0) return false;
	attacks[name] = Attack(
		name, 
		nullptr, 
		type, 
		range, 
		effects[0], 
		aoe, 
		affect_self);
	// Parse the modifiers here
	for (const json& modifier : data["modifiers"]) {
		attacks[name].addEffectModifier(parseModifier(modifier));
	}
	return true;
}

AttackType AttackLoader::getTypeFromString(const std::string & str) const {
	if (str == "melee") {
		return AttackType::MELEE;
	}
	if (str == "ranged") {
		return AttackType::RANGED;
	}
	if (str == "self") {
		return AttackType::SELF;
	}
	if (str == "pierce") {
		return AttackType::PIERCE;
	}
	return AttackType::INVALID;
}

AttackEffect * AttackLoader::parseEffect(const json & data) const {
	if (data["type"] == "damage") {
		int damage = data["damage"];
		return new DamageEffect(damage);
	}
	return nullptr;
}

EffectModifier AttackLoader::parseModifier(const json & data) const {
	float mod = data["mod"];
	if (data["type"] == "STR") {
		return EffectModifier{ Stat::STR, mod };
	}
	if (data["type"] == "DEX") {
		return EffectModifier{ Stat::DEX, mod };
	}
	if (data["type"] == "INT") {
		return EffectModifier{ Stat::INT, mod };
	}
	if (data["type"] == "CON") {
		return EffectModifier{ Stat::CON, mod };
	}
	return EffectModifier();
}
