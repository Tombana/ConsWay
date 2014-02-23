#include "CruxMap.h"

#include <iostream>
#include <sstream>

using std::stringstream;
using std::cerr;
using std::endl;

namespace Crux
{
    Map::Map(int _n, int _m, string config)
    {
        n = _n;
        m = _m;
        initFromConfiguration(config);
    }

    Map::~Map()
    {

    }

    bool Map::initFromConfiguration(string config)
    {
        grid = vector<vector<char> >(n, vector<char>(m, 0));
        stringstream sin(config);

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                sin >> grid[i][j];
            }
        }

        return true;
    }

    void Map::step()
    {
        vector<vector<char> > grid_copy = grid;

        for(int i = 1; i < (n - 1); ++i)
            for(int j = 1; j < (m - 1); ++j) {
                if(grid[i][j] != '*') continue;
                
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
