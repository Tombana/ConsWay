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
                sin >> grid[i][j];
            }
        }

        return true;
    }

    void Map::step()
    {
        vector<vector<char> > grid_copy = grid;

        for(int i = 1; i < (w - 1); ++i)
            for(int j = 1; j < (h - 1); ++j) {
                if(grid[i][j] != '*') continue;
                if(++burnTime[i][j] > 10) {
                    grid[i][j] = '/';
                    continue;
                }
                
                for(int di = -1; di <= 1; ++di)
                    for(int dj = -1; dj <= 1; ++dj) {
                        if(di == 0 && dj == 0) continue;
                        if(grid[i + di][j + dj] == '|' || grid[i + di][j + dj] == '.') {
                            grid_copy[i + di][j + dj] = '*';
                        }
                    }
            }
        grid = grid_copy;
    }

    char Map::val(int i, int j)
    {
        return grid[i][j];
    }

}
