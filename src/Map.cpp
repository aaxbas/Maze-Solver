#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Map.hpp"

void Map::readMap(std::string file_path){
    std::ifstream file(file_path);
    
    if (file.eof() || !file){
        std::cerr << "Could not open file! " << std::endl;
        exit(1);
    }

    file >> rows >> cols >> size >> goal.x >> goal.y >> start.x >> start.y;
    map.resize(rows);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            map[i].resize(cols);
            file >> map[i][j].type;    
            map[i][j].coordinate = {j,i};
        }
    }

    file.close();
}

void Map::printMap(){
    std::cout << "Size: " << size
    << "\nRows: " << rows
    << "\nCols: " << cols
    << "\nGoal: " << goal.x << "," << goal.y
    << "\nStart: " << start.x << "," << start.y 
    << std::endl;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cout << map[i][j].type << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Map::writeMap(std::string file_path){
    std::ofstream file(file_path);

    file << rows << "\n" 
    << cols << "\n"
    << size << "\n"
    << goal.x << " " << goal.y << "\n"
    << start.x << " " << start.y << "\n"
    << std::endl;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            file << map[i][j].type << " ";
        }
        file << std::endl;
    }
}

/**
 * @brief Initialize empty Map object with size specified
 * @param s total size
 * @param r number of rows
 * @param c number of columns 
 */ 
Map::Map(int s, int r, int c): size(s), rows(r), cols(c){

    if (s != r*c){
        std::cerr << "Total size must equal rows x cols" << std::endl;  // Is this needed?
        exit(1);
    }

    map.resize(rows);
    for(int i = 0; i < rows; i++)
        map[i].resize(cols);
}

/**
 * @brief return all adjacent empty tiles
 * @param x the x coordinate of the current tile
 * @param y the y coordinate of the current tile
 * @return vector of Tile containing the adjacent tiles
 */ 
std::vector<Tile> Map::adjacentTiles(int x, int y){
    std::vector<Tile> tiles;

    if(isValid(x, y-1)){
        if(map[y-1][x].isEmpty())
            tiles.push_back(map[y-1][x]);
    }

    if(isValid(x, y+1)){
        if(map[y+1][x].isEmpty())
            tiles.push_back(map[y+1][x]);
    }

    if(isValid(x-1, y)){
        if(map[y][x-1].isEmpty())
            tiles.push_back(map[y][x-1]);
    }


    if(isValid(x+1, y)){
        if(map[y][x+1].isEmpty())
            tiles.push_back(map[y][x+1]);
    }

    
    return tiles;

}

/**
 * @brief Get adjacent unvisited tiles
 * @param x the x coordinate of the current tile
 * @param y the y coordinate of the current tile
 * @return vector of Tile containing the adjacent unvisited tiles
 */
std::vector<Tile> Map::adjUnvisitedTiles(int x, int y){
    std::vector<Tile> tiles = adjacentTiles(x,y);
    
    tiles.erase(std::remove_if(tiles.begin(), tiles.end(), 
    [](const Tile &t){return t.history;}),
    tiles.end());
   
   return tiles;

}

/**
 * @brief check if the coordinates are within the map
 * @param x the x coordinate of the current tile
 * @param y the y coordinate of the current tile
 * @return true if it is within, false otherwise
 */ 
bool Map::isValid(int x, int y){
    return (x < cols && y < rows && x >= 0 && y >= 0);
}