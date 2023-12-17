#include <iostream>
#include "Game.h"
#include "Player.h"

Game::~Game()
{
	for (auto player = players.begin(); player != players.end(); ++player)
	{
		delete (*player);
	}
	players.clear();
}

void Game::printGameName()
{
	std::cout << "[[[" << gameName << "]]]" << std::endl;
}

void Game::printAlivePlayers()
{
	for (auto player = players.begin(); player != players.end(); ++player)
	{
		(*player)->aliveMessage();
	}
}



const unsigned int RedLightGreenLight::distance = 1000;
const float RedLightGreenLight::fallDownRate = 0.1f;



void RedLightGreenLight::join(Player* player)
{
	players.push_back(new PlayerRLGL(*player));
}

void RedLightGreenLight::play()
{
	printGameName(); // 게임 이름 출력.

	for (int t = 0; t < turn; ++t) // 0~19까지 20번 반복한다.
	{
		std::cout << "[Turn #" << t+1 << ']' << '\n'; // 0~19로 t가 바뀌므로 +1을 해줌.
		auto cursor = players.begin(); // 생존해 있는 플레이어들을 하나씩 돌면서 act()를 수행할 때 그 플레이어를 추적해줄 커서.

		while(cursor != players.end()) // 처음부터 끝까지 순회함.
		{
			if ((*cursor)->isPlaying() && !((*cursor)->act())) // 이 플레이어가 플레이 중이고, 한 턴을 실행한 뒤 죽었다면,
			{
				(*cursor)->dyingMessage(); // 죽었다고 메시지를 보내고, 
				delete (*cursor); // 이 커서가 가리키는 공간을 없앤다.
				cursor = players.erase(cursor); // 그리고, players리스트에서 죽은 이 플레이어를 제거함.
			}
			else // 플레이중이지 않다 : 죽었거나 이미 통과함. 
				++cursor; // 다음 플레이어로 넘어감.
		}
	}

	std::cout << "[Game Over]" << std::endl;

	auto player = players.begin();
	while (player != players.end())
	{
		if ((*player)->isPlaying())
		{
			(*player)->dyingMessage();
			delete (*player);
			player = players.erase(player);
		}
		else
		{
			++player;
		}
	}

	printAlivePlayers();

	std::cout << players.size() << " players are alive." << std::endl << std::endl;
}





void RPS::join(Player* player)
{
	players.push_back(new PlayerRPS(*player));
}

void RPS::play()
{
	printGameName();

	if (players.size() < 2)
	{
		std::cout << "There are not sufficient players.";
		return;
	}

	auto player = players.begin();

	while (player != players.end())
	{
		if ((*player)->act())
		{
			++player;
		}
		else
		{
			(*player)->dyingMessage();
			delete (*player);
			player = players.erase(player);
		}
	}

	printAlivePlayers();

	std::cout << players.size() << " players are alive." << std::endl << std::endl;
}




void Tazza::join(Player* player) // 살아있는 플레이어를 받아옴.
{
	players.push_back(new PlayerTazza(*player)); // 이번 게임의 참가자로 추가.
}

void Tazza::play()
{
	printGameName(); // 게임 이름 출력

	auto cursor = players.begin(); // 플레이어들 하나하나를 추적할 커서.
	while (cursor != players.end()) // 플레이어들을 한번씩만 순회함.(한번의 act로 생사를 결정할 것임.)
	{
		if (!(*cursor)->act()) // 게임에 플레이어가 지면 false이므로 
		{
			(*cursor)->dyingMessage(); // 죽었다고 띄우고
			delete (*cursor); // 이 플레이어 객체를 동적으로 저장한 공간을 제거.
			cursor = players.erase(cursor); // 생존자 리스트에서도 제거.
		}
		else
			++cursor; // 살았다면 다음 플레이어로
	}

	printAlivePlayers(); // 이 게임을 한 뒤에 살아남은 플레이어들을 출력.

	std::cout << players.size() << " players are alive." << std::endl << std::endl;
}
