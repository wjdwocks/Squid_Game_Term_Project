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
	if (fearlessness > possibility(random_engine)*100) // fearlessness가 높을수록 이 이벤트가 자주 발생하도록 설계함.
	{
		double rand_num = possibility(random_engine); // 확률을 하나 집는다.

		if (rand_num < fallDownRate) // 0.1보다 작다면 -> 10%의 확률. 넘어져서 죽는다.
		{ 
			this->playing = false; // 더이상 플레이 하고 있지 않음.
			return false; // 죽었다고 결론내리고 끝냄.
		}
		else if(rand_num < 0.85) // 0.1을 제외한 0.75의 확률이 됨. 
			FearlessBonusDistance = (agility * double(fearlessness * 0.01)); // 추가 거리 보너스를 얻는다.
	}

	current_distance += agility + rand() % 11 + FearlessBonusDistance; // 즉, 지나간 거리는 agility + [0:10] + fearlessbonusdistance이다.
	if (current_distance >= 1000) // 증가한 거리가 전체 거리를 넘는다면
	{
		printStatus(); 
		std::cout << " safely escaped from the ground." << '\n';
		this->playing = false; // 게임을 하고 있지 않게 되고
		return true; // 생존으로 마무리.
	}
	return true; // 이번에 움직이기만 하고, 통과는 못한 경우 다음 turn을 가기 위해 true를 반환.
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




bool PlayerTazza::act() // true면 플레이어가 이긴거, false면 플레이어가 진거.
{
	std::pair<int, int> enemyCard = { card_num(random_engine), card_num(random_engine) }; // 1~10사이의 카드를 두장 뽑는다.
	std::pair<int, int> playerCard = { card_num(random_engine), card_num(random_engine) }; // 1~10사이의 카드를 두장 뽑는다.
	int enemyPoint;
	int playerPoint;

	// 적(컴퓨터)의 점수
	if (enemyCard.first == enemyCard.second)
		enemyPoint = enemyCard.first * 100;
	else if (enemyCard.first + enemyCard.second == 3) // 3이 되는건 1,2 밖에 없음. 알리
		enemyPoint = 90;
	else if ((enemyCard.first == 1 && enemyCard.second == 4) || (enemyCard.first == 4 && enemyCard.second == 1)) // 독사
		enemyPoint = 80;
	else if ((enemyCard.first == 1 && enemyCard.second == 9) || (enemyCard.first == 9 && enemyCard.second == 1)) // 구삥
		enemyPoint = 70;
	else if ((enemyCard.first == 1 && enemyCard.second == 10) || (enemyCard.first == 10 && enemyCard.second == 1)) // 장삥
		enemyPoint = 60;
	else if ((enemyCard.first == 4 && enemyCard.second == 10) || (enemyCard.first == 10 && enemyCard.second == 4)) // 장사
		enemyPoint = 50;
	else if ((enemyCard.first == 6 && enemyCard.second == 4) || (enemyCard.first == 4 && enemyCard.second == 6)) // 세륙
		enemyPoint = 40;
	else
		enemyPoint = (enemyCard.first + enemyCard.second) % 10; // 0~9사이의 수를 갖는다.


	// 플레이어 점수
	if (playerCard.first == playerCard.second)
		playerPoint = playerCard.first * 100;
	else if (playerCard.first + playerCard.second == 3) // 3이 되는건 1,2 밖에 없음. 알리
		playerPoint = 90;
	else if ((playerCard.first == 1 && playerCard.second == 4) || (playerCard.first == 4 && playerCard.second == 1)) // 독사
		playerPoint = 80;
	else if ((playerCard.first == 1 && playerCard.second == 9) || (playerCard.first == 9 && playerCard.second == 1)) // 구삥
		playerPoint = 70;
	else if ((playerCard.first == 1 && playerCard.second == 10) || (playerCard.first == 10 && playerCard.second == 1)) // 장삥
		playerPoint = 60;
	else if ((playerCard.first == 4 && playerCard.second == 10) || (playerCard.first == 10 && playerCard.second == 4)) // 장사
		playerPoint = 50;
	else if ((playerCard.first == 6 && playerCard.second == 4) || (playerCard.first == 4 && playerCard.second == 6)) // 세륙
		playerPoint = 40;
	else
		playerPoint = (playerCard.first + playerCard.second) % 10; // 0~9사이의 수를 갖는다.


	if (playerPoint > enemyPoint)
		return true;
	else if (playerPoint < enemyPoint)
		return false;
	else
	{
		printStatus();
		std::cout << "는 카드게임에서 비겼기에 재경기를 진행합니다." << '\n';
		act();
	}

}


void PlayerTazza::dyingMessage()
{
	printStatus();
	std::cout << "가 카드 게임에서 졌습니다..." << std::endl;
}



