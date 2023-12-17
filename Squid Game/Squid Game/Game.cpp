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
	printGameName(); // ���� �̸� ���.

	for (int t = 0; t < turn; ++t) // 0~19���� 20�� �ݺ��Ѵ�.
	{
		std::cout << "[Turn #" << t+1 << ']' << '\n'; // 0~19�� t�� �ٲ�Ƿ� +1�� ����.
		auto cursor = players.begin(); // ������ �ִ� �÷��̾���� �ϳ��� ���鼭 act()�� ������ �� �� �÷��̾ �������� Ŀ��.

		while(cursor != players.end()) // ó������ ������ ��ȸ��.
		{
			if ((*cursor)->isPlaying() && !((*cursor)->act())) // �� �÷��̾ �÷��� ���̰�, �� ���� ������ �� �׾��ٸ�,
			{
				(*cursor)->dyingMessage(); // �׾��ٰ� �޽����� ������, 
				delete (*cursor); // �� Ŀ���� ����Ű�� ������ ���ش�.
				cursor = players.erase(cursor); // �׸���, players����Ʈ���� ���� �� �÷��̾ ������.
			}
			else // �÷��������� �ʴ� : �׾��ų� �̹� �����. 
				++cursor; // ���� �÷��̾�� �Ѿ.
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




void Tazza::join(Player* player) // ����ִ� �÷��̾ �޾ƿ�.
{
	players.push_back(new PlayerTazza(*player)); // �̹� ������ �����ڷ� �߰�.
}

void Tazza::play()
{
	printGameName(); // ���� �̸� ���

	auto cursor = players.begin(); // �÷��̾�� �ϳ��ϳ��� ������ Ŀ��.
	while (cursor != players.end()) // �÷��̾���� �ѹ����� ��ȸ��.(�ѹ��� act�� ���縦 ������ ����.)
	{
		if (!(*cursor)->act()) // ���ӿ� �÷��̾ ���� false�̹Ƿ� 
		{
			(*cursor)->dyingMessage(); // �׾��ٰ� ����
			delete (*cursor); // �� �÷��̾� ��ü�� �������� ������ ������ ����.
			cursor = players.erase(cursor); // ������ ����Ʈ������ ����.
		}
		else
			++cursor; // ��Ҵٸ� ���� �÷��̾��
	}

	printAlivePlayers(); // �� ������ �� �ڿ� ��Ƴ��� �÷��̾���� ���.

	std::cout << players.size() << " players are alive." << std::endl << std::endl;
}