#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;
class Engine
{
private:
    bool isBlock;
    int pointCount;
    int mapSizeX;
    int mapSizeY;
    bool finished;
    std::pair<int, int> start;
    std::pair<int, int> end;
    vector<vector<int>>map;
    set<pair<float, pair<int, int>>>q;

public:
    std::vector<std::pair<int, int>>path;
    std::vector<std::pair<int, int>>yellow;
    Engine(int x, int y);
    static std::pair<float, float> getMousePos(sf::RenderWindow& window);
    void createPoint(int x, int y, int UNIT);
    static float scale(const float ID, const int UNIT);
    int getPointCount();
    static int scaleToID(const float ID, const int UNIT);
    //-----
    void setWall(int x, int y, const int UNIT);
    bool getIsBlock();
    std::pair<int, int>getMapSize();
    int getMapValue(int x, int y);
    static int scaleFromID(const int ID, const int UNIT);
    //BFS
    void genpath(int UNIT);
    vector<pair<int, int>>getPoints(int UNIT);
    void update_q(const pair<int, int>pos, int UNIT);
    pair<float, pair<int, int>> getmoves(int I, pair<int, int> pos);
    bool isfinished();
};

