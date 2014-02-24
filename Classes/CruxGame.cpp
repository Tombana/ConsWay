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
        player = 0;
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
        /* stringstream sin(mapConfiguration);
        int w, h; 
        sin >> w >> h;

        if(map)
            delete map;

        map = new Map(w, h);
        map->initFromConfiguration(sin); */
        delegate = _delegate;

        finalx = 19;
        finaly = 19;

        gameState = PLAYER_TURN;

        apPerTurn = 3;

        if(player)
            delete player;
        player = new Player();
		
		NPC tmp(HORSE, Pos2(4,4));
		NPC tmp2(RANDOM, Pos2(10,10));
		NPC tmp3(GREEDY, Pos2(20,20));
		npclist.push_back(tmp);	
		npclist.push_back(tmp2);	
		npclist.push_back(tmp3);	

        delegate->gameUpdated();
        return true;
    }

    void Game::setMapProperties(int w, int h)
    {
        if(map)
            delete map;

        map = new Map(w, h);

    }

    void Game::performNPCMoves()
    {
		for(int i=0; i<npclist.size(); i++)
			npclist[i].move(map, player->getPosition());
        // update npc moves
    }
    
    void Game::update()
    {
        if(!(gameState < PLAYER_LOST))
            return; 

        //map->step();
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
        if(!(gameState == PLAYER_TURN))
            return;

        gameState = NPC_TURN;

        update();
        performNPCMoves();

        player->setActionPoints(player->getActionPoints() + apPerTurn);
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
