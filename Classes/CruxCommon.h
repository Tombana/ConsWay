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
    }

    typedef enum 
    {
        UP = 1,
        LEFT,
        DOWN,
        RIGHT
    } DIRECTION;
}
