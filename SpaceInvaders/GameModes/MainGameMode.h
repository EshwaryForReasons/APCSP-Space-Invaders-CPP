//Copyright Eshwary Mishra 2022

#pragma once

#include "GameModeBase.h"
#include "Pawn.h"

enum class EEnemyType
{
	ET_BASIC,
	ET_INTERMEDIATE,
	ET_ADVANCED,
	ET_BOMBER
};

class UMainGameMode : public UGameModeBase
{
public:

	UMainGameMode();

	virtual void Tick() override;

	virtual void BeginPlay() override;

	virtual void EndGame() override;

	virtual void HandleInput(SDL_Event& input_event) override;

	virtual void RenderWorld() override;

	void InitializeEnemies();

	virtual void InternalMoveEnemies() override;
	virtual void EnemyAttack() override;

	virtual void AddDeath(int amount_killed, ASIEnemyBase* dead_enemy) override;

protected:

	/**List of enemies to spawn*/
	std::map<int, EEnemyType> enemy_data;

	/**Current enemies*/
	std::vector<class ASIEnemyBase*> current_enemies;

	SDL_TimerID enemy_move_timer;
	SDL_TimerID enemy_attack_timer;

	bool bMoveEnemiesLeft;
};