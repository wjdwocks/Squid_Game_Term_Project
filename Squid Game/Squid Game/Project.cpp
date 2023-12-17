#include <iostream>
#include "Player.h"
#include "Game.h"

int main()
{
    std::list<Player*> players;
    for (int i = 0; i < 456; ++i)
    {
        players.push_back(new Player(i + 1));
    }

    std::vector<Game*> games;
    games.push_back(new RedLightGreenLight(20));
    games.push_back(new RPS());
    games.push_back(new Tazza());

    for (auto game : games)
    {
        for (auto player : players)
            game->join(player);

        game->play();

        auto alivePlayers = game->getAlivePlayers();
        players.clear();
        for (auto player : alivePlayers)
        {
            players.push_back(new Player(*player));
        }
    }

    for (auto game : games)
        delete game;

    system("pause");
}