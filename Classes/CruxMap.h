// Instances of this class will represent the map. we have
// the following legend: 
// 
// . grass
// | forest
// # stone
// * fire
// = road
// ~ water
// / burned
//
// on an (n x m) grid which we be loaded in from a file

#include <string> 
#include <vector> 

using std::string;
using std::vector;

namespace Crux
{
    class Map
    {
        public:
            // initializes a new map of size (n, m) from the 
            // 'seed'  config
            Map(int _n, int _m, string config);
            ~Map();

            // initializes from a ASCII configuration file, which
            // is represented a string and should contain (n x m)
            // characters.
            bool initFromConfiguration(std::string config);

            // simulates one CGOL step this should be called every
            // dt seconds, where dt is the time between 'gameturns'.
            void step(); 

            // returns the integer value of the square at (i, j)
            // where 0 <= i < n, 0 <= j < m. returns -1 if the 
            // square is out of bouds. The integer value is the 
            // color of the square, for future support of multiple
            // colors
            char val(int i, int j);

            int getWidth() const { return n; };
            int getHeight() const { return m; }; 

        private:
            int n;
            int m;
            vector<vector<char> > grid;
    };
}