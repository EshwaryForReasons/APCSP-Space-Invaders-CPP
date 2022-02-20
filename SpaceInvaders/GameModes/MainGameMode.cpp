//Copyright Eshwary Mishra 2022

#include "MainGameMode.h"

#include "Player.h"
#include "Enemies/SIEnemyBase.h"
#include "Enemies/SIEnemyBasic.h"
#include "Enemies/SIEnemyIntermediate.h"
#include "Enemies/SIEnemyAdvanced.h"
#include "Enemies/SIEnemyBomber.h"
#include "main.h"

UMainGameMode::UMainGameMode()
{
	player_score = 0;
	enemies_killed = 0;

	level = 1;
	difficulty = 1;

	bMoveEnemiesLeft = false;

	enemy_data.emplace(1, EEnemyType::ET_BOMBER);
	enemy_data.emplace(2, EEnemyType::ET_ADVANCED);
	enemy_data.emplace(3, EEnemyType::ET_INTERMEDIATE);
	enemy_data.emplace(4, EEnemyType::ET_BASIC);
}

void UMainGameMode::Tick()
{
	UGameModeBase::Tick();

	if (current_enemies.size() == 0)
	{
		InitializeEnemies();
	}
}

Uint32 MoveEnemies(Uint32 Interval, void* param)
{
	Main::GetInstance()->current_game_mode->InternalMoveEnemies();

	return 1000;
}

Uint32 Attack(Uint32 Interval, void* param)
{
	Main::GetInstance()->current_game_mode->EnemyAttack();

	return 2500;
}

void UMainGameMode::BeginPlay()
{
	UGameModeBase::BeginPlay();

	srand(time(NULL));

	player = new APlayer(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, &Main::GetInstance()->player_texture);
	Main::GetInstance()->AddEntity(player);

	InitializeEnemies();

	enemy_move_timer = SDL_AddTimer(1000, MoveEnemies, NULL);
	enemy_attack_timer = SDL_AddTimer(1500, Attack, NULL);
}

void UMainGameMode::EndGame()
{
	UGameModeBase::EndGame();

	current_enemies.empty();

	Main::GetInstance()->global_entities.empty();
}

void UMainGameMode::HandleInput(SDL_Event& input_event)
{
	UGameModeBase::HandleInput(input_event);

	if (player)
	{
		player->HandleInput(input_event);
	}
}


void UMainGameMode::RenderWorld()
{
	for (class SIObject* object : Main::GetInstance()->global_entities)
	{
		object->Tick();
		object->Render();
	}
}


void UMainGameMode::InitializeEnemies()
{
	for (std::pair<int, EEnemyType> data : enemy_data)
	{
		int i = 0;
		int max = data.second == EEnemyType::ET_BOMBER ? 4 : 10;
		int start = (SCREEN_WIDTH / 2) - (SCREEN_WIDTH * 0.4);
		int end = (SCREEN_WIDTH / 2) + (SCREEN_WIDTH * 0.4);
		int width = end - start;
		int distance = width / max;
		int hdistance = 60;

		while (i < max)
		{
			ASIEnemyBase* enemy = nullptr;

			switch (data.second)
			{
			case EEnemyType::ET_BOMBER:
				enemy = new ASIEnemyBomber(start + (distance * i), hdistance * data.first, &Main::GetInstance()->enemy_bomber_texture);
				break;
			case EEnemyType::ET_BASIC:
				enemy = new ASIEnemyBasic(start + (distance * i), hdistance * data.first, &Main::GetInstance()->enemy_basic_texture);
				break;
			case EEnemyType::ET_INTERMEDIATE:
				enemy = new ASIEnemyIntermediate(start + (distance * i), hdistance * data.first, &Main::GetInstance()->enemy_intermediate_texture);
				break;
			case EEnemyType::ET_ADVANCED:
				enemy = new ASIEnemyAdvanced(start + (distance * i), hdistance * data.first, &Main::GetInstance()->enemy_advanced_texture);
				break;
			};

			Main::GetInstance()->AddEntity(enemy);
			current_enemies.push_back(enemy);

			i++;
		}
	}
}

void UMainGameMode::InternalMoveEnemies()
{
	bool bShouldMoveX = true;

	for (ASIEnemyBase* enemy : current_enemies)
	{
		if (!enemy->CheckHorizontalMovementPossible(bMoveEnemiesLeft))
		{
			bShouldMoveX = false;

			bMoveEnemiesLeft = !bMoveEnemiesLeft;

			break;
		}
	}

	for (ASIEnemyBase* enemy : current_enemies)
	{
		enemy->MoveEnemy(bShouldMoveX, bMoveEnemiesLeft ? -enemy->object_width * 0.75 : enemy->object_width * 0.75);

		if (enemy->y_position >= SCREEN_HEIGHT * 0.7)
		{
			Main::GetInstance()->ChangeGameState(EGameState::GS_GameOver);

			break;
		}
	}
}

void UMainGameMode::EnemyAttack()
{
	for (ASIEnemyBase* enemy : current_enemies)
	{
		int random_number = rand() % 3 + 1;

		if (random_number == 1)
		{
			enemy->Attack();
		}
	}
}


void UMainGameMode::AddDeath(int amount_killed, ASIEnemyBase* dead_enemy)
{
	UGameModeBase::AddDeath(amount_killed, dead_enemy);

	current_enemies.erase(std::remove(current_enemies.begin(), current_enemies.end(), dead_enemy), current_enemies.end());
}