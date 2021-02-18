#include "../Tile.hpp"
#include "../Map.hpp"
#include "../Screen.hpp"

class Astar
{

public:
    std::vector<Tile *> queue;
    bool isStep;

    void solve(Map *map, Screen *s);

    Astar(){};

private:
    template <typename T>
    static T dequeue(std::vector<T> q);
    static bool findInQueue(std::vector<Tile *> queue, Tile tile);
};