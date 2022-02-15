//Copyright Eshwary Mishra 2022

#pragma once

#include <vector>
#include <map>
#include <memory>

#include "Pawn.h"

enum class EEnemyType
{
	ET_BASIC,
	ET_INTERMEDIATE,
	ET_ADVANCED,
	ET_BOMBER
};

class UMainGameMode
{
public:

	UMainGameMode();

	void InitializeEnemies();

	void StartGame();
	void EndGame();

	int player_score;
	int enemies_killed;

	int level;
	int difficulty;

	std::map<int, EEnemyType> enemy_data;

	std::vector<std::shared_ptr<APawn>> current_enemies;
};