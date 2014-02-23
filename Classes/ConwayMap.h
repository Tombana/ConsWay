// Instances of this class will simulate Conways Game of Life (CGOL)
// on an (n x m) grid which we be loaded in from a file

#include <string> 
#include <vector> 

using std::string;
using std::vector;

namespace ConsWay
{
    class Map
    {
        public:
            // initializes a new map of size (n, m) from the 
            // 'seed' file configFile
            Map(int _n, int _m, string configFile);
            ~Map();

            // initializes from a ASCII configuration file, which
            // should contains (n x m) characters, active squares
            // are indicated by the char '#' and will be given the
            // value 1
            bool initFromConfigurationFile(std::string configFile);

            // simulates one CGOL step this should be called every
            // dt seconds, where dt is the time between 'gameturns'.
            void step(); 

            // returns the integer value of the square at (i, j)
            // where 0 <= i < n, 0 <= j < m. returns -1 if the 
            // square is out of bouds. The integer value is the 
            // color of the square, for future support of multiple
            // colors
            int val(int i, int j);

            // write the current map to a file
            void write(std::string outputFile);

            int getWidth() const { return n; };
            int getHeight() const { return m; }; 

        private:
            int n;
            int m;
            vector<vector<int> > grid;
    };
}
