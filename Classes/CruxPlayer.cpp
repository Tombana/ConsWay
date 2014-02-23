#include "CruxPlayer.h"
#include <iostream>
using std::cerr;
using std::endl;

namespace Crux
{
    Player::Player()
    {
    }

    Player::~Player()
    {

    }

    void Player::initialize()
    {
        position.x = 0;
        position.y = 0;
    }

    void Player::move(DIRECTION dir, Map* map)
    {
        switch(dir) {
            case UP:
                if(position.y == (map->getHeight() - 1))
                    break;
                position.y++;
                break;
            case LEFT:
                if(position.x == 0)
                    break;
                position.x--;
                break;
            case DOWN:
                if(position.y == 0)
                    break;
                position.y--;
                break;
             case RIGHT:
                if(position.x == (map->getWidth() - 1))
                    break;
                position.x++;
                break;
            default:
                cerr << "ERROR: Unknown move command: " << dir << endl;
                break;
        }
    }

}
