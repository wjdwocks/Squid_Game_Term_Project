#pragma once
#include <iostream>
#include <random>
#include <time.h>

class Player
{
public:
	Player(int number);
	Player(int number, int agility, int fearlessness);
	~Player() {};
	virtual bool act() { return true; };
	virtual bool isPlaying() { return playing; };
	void aliveMessage() { printStatus(); std::cout << " is alive." << std::endl; };
	virtual void dyingMessage() { printStatus(); std::cout << " died." << std::endl; };
	virtual void printStatus() { std::cout << "Player #" << number << "(" << agility << "," << fearlessness << ")"; };
protected:
	unsigned int number;
	unsigned int agility;
	unsigned int fearlessness;
	bool playing = true;
	static std::default_random_engine random_engine;
	static std::uniform_int_distribution<unsigned int> ability_range;
	static std::uniform_real_distribution<float> possibility;
	static std::uniform_int_distribution<unsigned int> card_num;
};



class PlayerRLGL : public Player
{
	static float fallDownRate;
	unsigned int current_distance = 0;
public:
	PlayerRLGL(const Player& player) : Player(player) { playing = true; };
	bool act();
	void dyingMessage();
};

class PlayerRPS : public Player
{
public:
	PlayerRPS(const Player& player) : Player(player) {  };
	bool act();
	void dyingMessage();
};


class PlayerTazza : public Player
{
public:
	PlayerTazza(const Player& player) : Player(player) {};
	bool act(); // 가상 함수 오버라이드
	void dyingMessage(); // 가상 함수 오버라이드
};