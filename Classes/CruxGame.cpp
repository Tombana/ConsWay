#include "CruxGame.h"

#include <iostream>
#include <sstream>

using std::cerr;
using std::stringstream;
using std::endl;

namespace Crux
{
    Game::Game()
    {
        map = 0;
    }

    Game::~Game()
    {
        if(map)
            delete map;
        if(player)
            delete player;
    }

    bool Game::initialize(GameDelegate* _delegate, string mapConfiguration)
    {
        stringstream sin(mapConfiguration);
        int w, h; 
        sin >> w >> h;

        // TODO: should read contents of file?
        map = new Map(w, h);
        map->initFromConfiguration(sin);
        delegate = _delegate;

        finalx = 19;
        finaly = 19;

        gameState = PLAYER_TURN;

        apPerTurn = 3;

        player = new Player();

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

    void Game::finishPlayerTurn()
    {
        if(!gameState == PLAYER_TURN)
            return;

        gameState = NPC_TURN;

        update();
        performNPCMoves();

        player->setActionPoints(apPerTurn);
        gameState = PLAYER_TURN;

        delegate->gameUpdated();
    }

    void Game::checkLegalSquare()
    {
        if(map->val(player->getPosition().x, player->getPosition().y) == '*') {
            // game over
            gameState = PLAYER_LOST;
        }
    }

    void Game::checkFinalSquare()
    {
        if(player->getPosition().x == finalx && player->getPosition().y == finaly) {
            // we won the game
            gameState = PLAYER_WON;
        }
    }

}
