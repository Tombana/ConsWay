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
		
		int sqdist(const Point& a) const {
			return (x-a.x)*(x-ax)+(y-a.y)*(y-a.y);
		}
    };

    typedef enum 
    {
        UP = 1,
        LEFT,
        DOWN,
        RIGHT
    } DIRECTION;
}
