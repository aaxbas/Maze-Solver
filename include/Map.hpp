#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <vector>
#include <string>
#include "Tile.hpp"

class Map
{

public:
    std::vector<std::vector<Tile>> map;
    int size, rows, cols;

    coordinate_t goal, start;

    Map(std::vector<std::vector<Tile>> m, int s, int r, int c)
        : map(m), size(s), rows(r), cols(c) {}

    Map() {}

    Map(int s, int r, int c);

    void readMap(std::string file_path);
    void printMap();
    void writeMap(std::string file_path);
    std::vector<Tile> adjacentTiles(int x, int y);
    std::vector<Tile> adjUnvisitedTiles(int x, int y);

private:
    bool isValid(int x, int y);
};
#endif /* MAP_H */
