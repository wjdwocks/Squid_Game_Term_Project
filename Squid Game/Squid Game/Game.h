#pragma once
#include <string>
#include <list>

class Player;

class Game
{
protected:
	std::string gameName;
	std::list<Player*> players;
	virtual void printGameName();
public:
	Game(std::string name) :gameName(name) {};
	~Game();
	virtual void join(Player* player) = 0;
	virtual void play() = 0;
	void printAlivePlayers();
	std::list<Player*> getAlivePlayers() { return players; };

	//Player* operator[](int index) { return players[index]; };
};





class RedLightGreenLight : public Game
{
	friend class PlayerRLGL;

	static const unsigned int distance;
	static const float fallDownRate;

	const unsigned int turn = 20;
public:
	RedLightGreenLight() : Game("Red Light Green Light") {};
	RedLightGreenLight(int t) : Game("Red Light Green Light"), turn(t) {};
	~RedLightGreenLight() {};
	void join(Player* player);
	void play();
};





class RPS : public Game
{
	friend class PlayerRPS;

public:
	RPS() : Game("Rock Paper Scissors") {};
	~RPS() {};
	void join(Player* player);
	void play();
};


// 간단해진 섯다 게임(타짜)
// 적은 컴퓨터라고 하고, 랜덤으로 서로 화투패를 두개씩 뽑아서 땡과 끗 으로만 승부를 보게 설계해봤습니다.
// 섯다의 족보처럼 땡(x * 100) -> 알리(90) -> 독사(80) -> 구삥(70) -> 장삥(60) -> 장사(50) -> 세륙(40) -> 끗(0~9) 순서로 점수를 부여하고, 
// 같은 땡이라면 수가 더 큰 사람이 더 높은 점수를 맞도록 설계했습니다.
// 만약 같은 점수라면 즉시 재경기를 진행하도록 했습니다.
class Tazza : public Game 
{
public:
	Tazza() : Game("Tazza Game") {}; // 이름만 정해준다.
	~Tazza() {};
	void join(Player* player); // 똑같이 살아있는 플레이어만 추가.
	void play();
};