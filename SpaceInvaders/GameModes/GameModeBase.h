//Copyright Eshwary Mishra 2022

#pragma once

#include <vector>
#include <map>
#include <memory>

#include "Pawn.h"

class UGameModeBase
{
public:

	UGameModeBase();

	virtual void Tick();

	virtual void BeginPlay();
	virtual void HandleInput(SDL_Event& input_event);

	virtual void StartGame();
	virtual void EndGame();

	virtual void AddScore(int score_delta);
	virtual void AddDeath(int amount_killed, class ASIEnemyBase* dead_enemy);

	virtual void RenderWorld();

	virtual void InternalMoveEnemies();
	virtual void EnemyAttack();

	int player_score;
	int player_money;
	int enemies_killed;

	int level;
	int difficulty;

	/**The player*/
	class APlayer* player;
};