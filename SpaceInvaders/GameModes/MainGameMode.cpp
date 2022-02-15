//Copyright Eshwary Mishra 2022

#include "MainGameMode.h"

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

	enemy_data.emplace(1, EEnemyType::ET_BOMBER);
	enemy_data.emplace(2, EEnemyType::ET_BASIC);
	enemy_data.emplace(3, EEnemyType::ET_INTERMEDIATE);
	enemy_data.emplace(4, EEnemyType::ET_ADVANCED);
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
			std::shared_ptr<APawn> enemy = nullptr;

			switch (data.second)
			{
			case EEnemyType::ET_BOMBER:
				enemy = std::make_shared<ASIEnemyBomber>(start + (distance * i), hdistance * data.first, &Main::GetInstance()->enemy_bomber_texture);
				break;
			case EEnemyType::ET_BASIC:
				enemy = std::make_shared<ASIEnemyBasic>(start + (distance * i), hdistance * data.first, &Main::GetInstance()->enemy_basic_texture);
				break;
			case EEnemyType::ET_INTERMEDIATE:
				enemy = std::make_shared<ASIEnemyIntermediate>(start + (distance * i), hdistance * data.first, &Main::GetInstance()->enemy_intermediate_texture);
				break;
			case EEnemyType::ET_ADVANCED:
				enemy = std::make_shared<ASIEnemyAdvanced>(start + (distance * i), hdistance * data.first, &Main::GetInstance()->enemy_advanced_texture);
				break;
			};

			Main::GetInstance()->AddEntity(enemy);
			current_enemies.push_back(enemy);

			i++;
		}
	}
}