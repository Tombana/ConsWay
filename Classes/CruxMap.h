#pragma once
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

#include <sstream> 
#include <vector> 

using std::stringstream;
using std::vector;

namespace Crux
{
    class Map
    {
        public:
            // initializes a new map of size (n, m) from the 
            // 'seed'  config
            Map(int _w, int _h);
            ~Map();

            // initializes from a ASCII configuration file, which
            // is represented a string and should contain (n x m)
            // characters.
            bool initFromConfiguration(stringstream& sin);

            // simulates one CGOL step this should be called every
            // dt seconds, where dt is the time between 'gameturns'.
            void step(); 

            // returns the char value of the square at (i, j)
            // where 0 <= i < n, 0 <= j < m. returns -1 if the 
            // square is out of bouds. The char value is the 
            // type of the square, see the legend at the top
            // of this file
            char val(int i, int j);

            int getWidth() const { return w; };
            int getHeight() const { return h; }; 

        private:
            int w;
            int h;
            vector<vector<char> > grid;
            vector<vector<short> > burnTime;
    };
}
