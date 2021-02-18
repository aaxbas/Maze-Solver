#ifndef TILE_H
#define TILE_H

#include <iostream>

struct coordinate_t {
    int x,y;
    
    friend std::ostream &operator<<(std::ostream &output, coordinate_t c) { 
         output << "x: " << c.x << " y: " << c.y;
         return output;            
    }

    bool operator==(const coordinate_t& c) const {
        return ((x == c.x) && (y == c.y));
    }

    bool operator!=(const coordinate_t& c) const {
        return ((x != c.x) || (y != c.y));
    }


};

struct Tile{
    int type;
    int distance, manhattanD;
    bool history = false;
    bool goal = false;

    coordinate_t parent;

    coordinate_t coordinate;

    bool operator>(const Tile& t) const {
        return type > t.type;
    }

    bool operator<(const Tile& t) const {
        return type < t.type;
    }

    friend std::ostream &operator<<(std::ostream &output, Tile t) { 
         output << t.coordinate;
         return output;            
    }

    bool isEmpty(){
        return (type != 1 && type != 5);
    }

};

typedef struct Tile Tile;

#endif /* TILE_H */
