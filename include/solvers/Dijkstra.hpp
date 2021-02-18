#include "../Tile.hpp"
#include "../Map.hpp"
#include "../Screen.hpp"

class Dijkstra
{

public:
    std::vector<Tile *> queue;
    bool isStep;
    double stepDelay = 250;

    void solve(Map *map, Screen *s);

    Dijkstra(){};

private:
    template <typename T>
    static T dequeue(std::vector<T> q);
    static bool findInQueue(std::vector<Tile *> queue, Tile tile);
    void drawPath(Map *map, Screen *s);
};