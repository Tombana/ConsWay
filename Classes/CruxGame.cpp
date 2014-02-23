#include "ConwayGame.h"

#include <iostream>

using std::cerr;
using std::endl;

namespace Crux
{
    Game::Game()
    {
        map = 0;
        gameState = ACTIVE;
    }

    Game::~Game()
    {
        if(map)
            delete map;
    }

    bool Game::initialize(GameDelegate* _delegate)
    {
        // TODO: should be contents of file
        map = new Map(4, 2, "****====");
        delegate = _delegate;

        finalx = 9;
        finaly = 9;

        player.x = 0;
        player.y = 0;

        delegate->gameUpdated();
        return true;
    }

    void Game::update()
    {
        if(!(gameState == ACTIVE))
            return; 
        
        map->step();
        checkLegalSquare();

        delegate->gameUpdated();
    }

    void Game::move(DIRECTION dir)
    {
        if(!(gameState == ACTIVE))
            return;

        switch(dir) {
            case UP:
                if(player.y == (map->getHeight() - 1))
                    break;
                player.y++;
                break;
            case LEFT:
                if(player.x == 0)
                    break;
                player.x--;
                break;
            case DOWN:
                if(player.y == 0)
                    break;
                player.y--;
                break;
             case RIGHT:
                if(player.x == (map->getWidth() - 1))
                    break;
                player.x++;
                break;
            default:
                cerr << "ERROR: Unknown move command: " << dir << endl;
                break;
        }

        checkLegalSquare();
        checkFinalSquare();

        delegate->gameUpdated();
    }

    void Game::checkLegalSquare()
    {
        if(map->val(player.x, player.y) == 1) {
            // game over
            gameState = GAMEOVER;
        }
    }

    void Game::checkFinalSquare()
    {
        if(player.x == finalx && player.y == finaly) {
            // we won the game
            gameState = WON;
        }
    }


}
