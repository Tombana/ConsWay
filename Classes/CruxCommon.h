#pragma once

namespace Crux
{
    struct Pos2
    {
        Pos2(int _x, int _y)
        {
            x = _x;
            y = _y;
        }
        Pos2() { }
        ~Pos2() { }

        int x;
        int y;
    };

    typedef enum 
    {
        UP = 1,
        LEFT,
        DOWN,
        RIGHT
    } DIRECTION;
}
