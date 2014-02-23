#include "CruxMap.h"

#include <iostream>
#include <sstream>

using std::stringstream;
using std::cerr;
using std::endl;

namespace Crux
{
    Map::Map(int _w, int _h)
    {
        w = _w;
        h = _h;
    }

    Map::~Map()
    {

    }

    bool Map::initFromConfiguration(stringstream& sin)
    {
        grid = vector<vector<char> >(w, vector<char>(h, 0));
        burnTime = vector<vector<short> >(w, vector<short>(h, 0));

        for(int i = 0; i < w; ++i) {
            for(int j = 0; j < h; ++j) {
                sin >> grid[j][h - 1 - i];
            }
        }

        return true;
    }

    void Map::step()
    {
        vector<vector<char> > grid_copy = grid;

        for(int i = 0; i < w; ++i)
            for(int j = 0; j < h; ++j) {
                if(grid[i][j] != '*') continue;
                if(++burnTime[i][j] > 10) {
                    grid_copy[i][j] = '/';
                    continue;
                }
                
                for(int di = -1; di <= 1; ++di)
                    for(int dj = -1; dj <= 1; ++dj) {
                        if(di == 0 && dj == 0) continue;
                        if(val(i + di, j + dj) == 0) continue;
                        if(val(i + di, j + dj) == '|' || val(i + di, j + dj) == '.') {
                            grid_copy[i + di][j + dj] = '*';
                        }
                    }
            }
        grid = grid_copy;
    }

    char Map::val(int i, int j)
    {
        if((i < 0 || i >= w) || (j < 0 || j >= h)) {
            return 0;
        }
        return grid[i][j];
    }

}
