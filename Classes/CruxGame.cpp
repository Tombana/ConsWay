#include "CruxGame.h"

#include <iostream>

using std::cerr;
using std::endl;

namespace Crux
{
    Game::Game()
    {
        map = 0;
        gameState = PLAYER_TURN;
    }

    Game::~Game()
    {
        if(map)
            delete map;
    }

    bool Game::initialize(GameDelegate* _delegate)
    {
        // TODO: should read contents of file?
        map = new Map(4, 2, "****====");
        delegate = _delegate;

        finalx = 9;
        finaly = 9;

        player.x = 0;
        player.y = 0;

        delegate->gameUpdated();
        return true;
    }

    void Game::performNPCMoves()
    {
        // update npc moves
    }
    
    void Game::update()
    {
        if(!(gameState < PLAYER_LOST))
            return; 
        
        map->step();
        checkLegalSquare();

        delegate->gameUpdated();
    }

    void Game::move(DIRECTION dir)
    {
        if(!(gameState == PLAYER_TURN))
            return;

        player->move(dir, map);
        checkLegalSquare();
        checkFinalSquare();

        delegate->gameUpdated();
    }

    void Game::checkLegalSquare()
    {
        if(map->val(player.x, player.y) == '*') {
            // game over
            gameState = PLAYER_LOST;
        }
    }

    void Game::checkFinalSquare()
    {
        if(player.x == finalx && player.y == finaly) {
            // we won the game
            gameState = PLAYER_WON;
        }
    }


}
