#include "ConwayMap.h"

#include <fstream>
#include <iostream>

using std::fstream;
using std::cerr;
using std::endl;

namespace ConsWay
{
    Map::Map(int _n, int _m, string configFile)
    {
        n = _n;
        m = _m;
        initFromConfigurationFile(configFile);
    }

    Map::~Map()
    {

    }

    bool Map::initFromConfigurationFile(string configFile)
    {
        grid = vector<vector<int> >(n, vector<int>(m, 0));
        fstream fin;
        fin.open(configFile.c_str());
        if(!fin.is_open()) {
            cerr << "ERROR: Could not open file: " << configFile << endl;
            return false;
        }
        char a;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                fin >> a;
                if(a == '#') {
                    grid[i][j] = 1;
                }
            }
        fin.close();

        return true;
    }

    void Map::step()
    {
        vector<vector<int> > grid_copy = grid;

        for(int i = 1; i < (n - 1); ++i)
            for(int j = 1; j < (m - 1); ++j) {
                // count live neighbours
                int nbs = 0;
                for(int di = -1; di <= 1; ++di)
                    for(int dj = -1; dj <= 1; ++dj) {
                        if(di == 0 && dj == 0) continue;
                        if(grid[i + di][j + dj] == 1) {
                            ++nbs;
                        }
                    }
                // is it live? then we turn it off if there are not
                // exactly 2 or 3 neighbours
                if(grid[i][j] == 1) {
                    if(nbs < 2 || nbs > 3) {
                        grid_copy[i][j] = 0;
                    }
                } else { // it is off
                    if(nbs == 3) {
                        grid_copy[i][j] = 1;
                    }
                }
            }
        grid = grid_copy;
    }

    int Map::val(int i, int j)
    {
        return grid[i][j];
    }

    void Map::write(string outputFile)
    {
        fstream fout;
        fout.open(outputFile.c_str(), std::ios::out);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                fout << (val(i, j) > 0 ? '#' : '.');
            }
            fout << std::endl;
        }
        fout.close();
    }


}
