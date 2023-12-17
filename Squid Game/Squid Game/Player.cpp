#include "Player.h"
#include "Game.h"

std::default_random_engine Player::random_engine(time(nullptr));
std::uniform_int_distribution<unsigned int> Player::ability_range(0, 100);
std::uniform_real_distribution<float> Player::possibility(0.f, 1.f); 
std::uniform_int_distribution<unsigned int> Player::card_num(1, 10);

float PlayerRLGL::fallDownRate = 0.1f;

Player::Player(int number)
{
	this->number = number;

	agility = ability_range(random_engine);
	fearlessness = ability_range(random_engine);
}

Player::Player(int number, int agility, int fearlessness)
{
	this->number = number;
	this->agility = agility;
	this->fearlessness = fearlessness;
}




bool PlayerRLGL::act()
{
	int FearlessBonusDistance = 0;
	if (fearlessness > possibility(random_engine)*100) // fearlessness�� �������� �� �̺�Ʈ�� ���� �߻��ϵ��� ������.
	{
		double rand_num = possibility(random_engine); // Ȯ���� �ϳ� ���´�.

		if (rand_num < fallDownRate) // 0.1���� �۴ٸ� -> 10%�� Ȯ��. �Ѿ����� �״´�.
		{ 
			this->playing = false; // ���̻� �÷��� �ϰ� ���� ����.
			return false; // �׾��ٰ� ��г����� ����.
		}
		else if(rand_num < 0.85) // 0.1�� ������ 0.75�� Ȯ���� ��. 
			FearlessBonusDistance = (agility * double(fearlessness * 0.01)); // �߰� �Ÿ� ���ʽ��� ��´�.
	}

	current_distance += agility + rand() % 11 + FearlessBonusDistance; // ��, ������ �Ÿ��� agility + [0:10] + fearlessbonusdistance�̴�.
	if (current_distance >= 1000) // ������ �Ÿ��� ��ü �Ÿ��� �Ѵ´ٸ�
	{
		printStatus(); 
		std::cout << " safely escaped from the ground." << '\n';
		this->playing = false; // ������ �ϰ� ���� �ʰ� �ǰ�
		return true; // �������� ������.
	}
	return true; // �̹��� �����̱⸸ �ϰ�, ����� ���� ��� ���� turn�� ���� ���� true�� ��ȯ.
}

void PlayerRLGL::dyingMessage()
{
	if (isPlaying())
	{
		printStatus();
		std::cout << " is still on the ground and died." << std::endl;
	}

	else
	{
		printStatus();
		std::cout << " fell down and died." << std::endl;
	}
};





bool PlayerRPS::act()
{
	enum rpsType { Rock, Paper, Scissors };
	auto rps = [] {
		float p = possibility(random_engine);

		if (p < float(1.f / 3.f))
			return rpsType::Rock;
		else if (p < float(2.f / 3.f))
			return rpsType::Paper;
		else
			return  rpsType::Scissors;
	};

	rpsType myRPS, yourRPS;
	do {
		myRPS = rps();
		yourRPS = rps();
	} while (myRPS == yourRPS);

	if (myRPS == Rock)
	{
		if (yourRPS == Paper)
			return false;
		else
			return true;
	}
	else if (myRPS == Paper)
	{
		if (yourRPS == Scissors)
			return false;
		else
			return true;
	}
	else
	{
		if (yourRPS == Rock)
			return false;
		else
			return true;
	}
}


void PlayerRPS::dyingMessage()
{
	printStatus();
	std::cout << " died." << std::endl;
};




bool PlayerTazza::act() // true�� �÷��̾ �̱��, false�� �÷��̾ ����.
{
	std::pair<int, int> enemyCard = { card_num(random_engine), card_num(random_engine) }; // 1~10������ ī�带 ���� �̴´�.
	std::pair<int, int> playerCard = { card_num(random_engine), card_num(random_engine) }; // 1~10������ ī�带 ���� �̴´�.
	int enemyPoint;
	int playerPoint;

	// ��(��ǻ��)�� ����
	if (enemyCard.first == enemyCard.second)
		enemyPoint = enemyCard.first * 100;
	else if (enemyCard.first + enemyCard.second == 3) // 3�� �Ǵ°� 1,2 �ۿ� ����. �˸�
		enemyPoint = 90;
	else if ((enemyCard.first == 1 && enemyCard.second == 4) || (enemyCard.first == 4 && enemyCard.second == 1)) // ����
		enemyPoint = 80;
	else if ((enemyCard.first == 1 && enemyCard.second == 9) || (enemyCard.first == 9 && enemyCard.second == 1)) // ����
		enemyPoint = 70;
	else if ((enemyCard.first == 1 && enemyCard.second == 10) || (enemyCard.first == 10 && enemyCard.second == 1)) // ���
		enemyPoint = 60;
	else if ((enemyCard.first == 4 && enemyCard.second == 10) || (enemyCard.first == 10 && enemyCard.second == 4)) // ���
		enemyPoint = 50;
	else if ((enemyCard.first == 6 && enemyCard.second == 4) || (enemyCard.first == 4 && enemyCard.second == 6)) // ����
		enemyPoint = 40;
	else
		enemyPoint = (enemyCard.first + enemyCard.second) % 10; // 0~9������ ���� ���´�.


	// �÷��̾� ����
	if (playerCard.first == playerCard.second)
		playerPoint = playerCard.first * 100;
	else if (playerCard.first + playerCard.second == 3) // 3�� �Ǵ°� 1,2 �ۿ� ����. �˸�
		playerPoint = 90;
	else if ((playerCard.first == 1 && playerCard.second == 4) || (playerCard.first == 4 && playerCard.second == 1)) // ����
		playerPoint = 80;
	else if ((playerCard.first == 1 && playerCard.second == 9) || (playerCard.first == 9 && playerCard.second == 1)) // ����
		playerPoint = 70;
	else if ((playerCard.first == 1 && playerCard.second == 10) || (playerCard.first == 10 && playerCard.second == 1)) // ���
		playerPoint = 60;
	else if ((playerCard.first == 4 && playerCard.second == 10) || (playerCard.first == 10 && playerCard.second == 4)) // ���
		playerPoint = 50;
	else if ((playerCard.first == 6 && playerCard.second == 4) || (playerCard.first == 4 && playerCard.second == 6)) // ����
		playerPoint = 40;
	else
		playerPoint = (playerCard.first + playerCard.second) % 10; // 0~9������ ���� ���´�.


	if (playerPoint > enemyPoint)
		return true;
	else if (playerPoint < enemyPoint)
		return false;
	else
	{
		printStatus();
		std::cout << "�� ī����ӿ��� ���⿡ ���⸦ �����մϴ�." << '\n';
		act();
	}

}


void PlayerTazza::dyingMessage()
{
	printStatus();
	std::cout << "�� ī�� ���ӿ��� �����ϴ�..." << std::endl;
}


