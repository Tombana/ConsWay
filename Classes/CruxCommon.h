namespace Crux
{
    struct Point
    {
        Point(_x, _y)
        {
            x = _x;
            y = _y;
        }
        Point() { }
        ~Point() { }

        int x;
        int y;
		
		int sqdist(const Point& a) const {
			return (x-a.x)*(x-ax)+(y-a.y)*(y-a.y);
		}
    }

    typedef enum 
    {
        UP = 1,
        LEFT,
        DOWN,
        RIGHT
    } DIRECTION;
}
