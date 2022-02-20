//Copyright Eshwary Mishra 2022

#include "MainGameMode.h"

#include "player.h"
#include "Enemies/SIEnemyBasic.h"
#include "Enemies/SIEnemyIntermediate.h"
#include "Enemies/SIEnemyAdvanced.h"
#include "Enemies/SIEnemyBomber.h"
#include "main.h"

UGameModeBase::UGameModeBase()
{
	player_score = 0;
	player_money = 0;
	enemies_killed = 0;

	level = 1;
	difficulty = 1;
}

void UGameModeBase::Tick()
{
	
}

void UGameModeBase::BeginPlay()
{
	
}

void UGameModeBase::HandleInput(SDL_Event& input_event)
{
	
}


void UGameModeBase::RenderWorld()
{
	
}


void UGameModeBase::InternalMoveEnemies()
{

}

void UGameModeBase::EnemyAttack()
{

}


void UGameModeBase::StartGame()
{

}

void UGameModeBase::EndGame()
{

}


void UGameModeBase::AddScore(int score_delta)
{
	player_score += score_delta;
	player_money += score_delta / 10;
}

void UGameModeBase::AddDeath(int amount_killed, ASIEnemyBase* dead_enemy)
{
	enemies_killed = amount_killed;
}