#include "Engine.h"
#include <iostream>
using namespace std;
Engine::Engine(int x, int y) {
	this->mapSizeX = x;
	this->mapSizeY = y;
	this->map.assign(y, vector<int>(x));
	this->pointCount = 0;
	this->isBlock = false;
	this->finished = false;
}

std::pair<float, float> Engine::getMousePos(sf::RenderWindow& window) {
	return std::pair<float, float>(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

float Engine::scale(const float ID, const int UNIT) {
	return int(ID / UNIT) * UNIT;
}

int Engine::scaleToID(const float ID, const int UNIT) {
	return int(ID / UNIT) - int(UNIT / 10);
}

void Engine::createPoint(int x, int y, int UNIT) {
	if (this->pointCount < 2) {
		if (this->pointCount == 0)
			this->start = { scaleToID(y,UNIT), scaleToID(x, UNIT)};
		else
			this->end = { scaleToID(y,UNIT), scaleToID(x, UNIT) };
		map[scaleToID(y, UNIT)][scaleToID(x, UNIT)] = 1;
		cout << scaleToID(y, UNIT) << ' ' << scaleToID(x, UNIT) << std::endl;
		this->pointCount++;	
	}
}

int Engine::getPointCount() {
	return pointCount;
}

// --------

void Engine::setWall(int x, int y, const int UNIT) {
	if (this->map[scaleToID(y, UNIT)][scaleToID(x, UNIT)] != 1) {
		this->map[scaleToID(y, UNIT)][scaleToID(x, UNIT)] = -1;
		this->isBlock = true;
	}
}

bool Engine::getIsBlock() {
	return this->isBlock;
}

std::pair<int, int>Engine::getMapSize() {
	return std::make_pair(this->mapSizeX, this->mapSizeY);
}

int Engine::getMapValue(int x, int y) {
	if (y < this->mapSizeY && x < this->mapSizeX)
		return this->map[y][x];
	return 404;
}

int Engine::scaleFromID(const int ID, const int UNIT) {
	return int(ID * UNIT) + int(UNIT * 2);
}

// BFS

pair<float, pair<int, int>> Engine::getmoves(int I, pair<int, int> pos) {
	//n : 0 1 2 3   ->   {+1,.} {-1,.} {.,+1} {.,-1}
	int i = pos.first, j = pos.second;
	float sq;
	if (I == 0) {
		if (i + 1 < this->mapSizeY && this->map[i + 1][j] != -1) {
			sq = sqrt(pow(i + 1 - end.first, 2) + pow(j - end.second, 2));
			return { sq , {i + 1, j} };
		}
	}
	else if (I == 1) {
		if (i - 1 >= 0 && this->map[i - 1][j] != -1) {
			sq = sqrt(pow(i - 1 - end.first, 2) + pow(j - end.second, 2));
			return { sq, {i - 1,j} };

		}
	}
	else if (I == 2) {
		if (j + 1 < this->mapSizeX && this->map[i][j + 1] != -1) {
			sq = sqrt(pow(i - end.first, 2) + pow(j + 1 - end.second, 2));
			return { sq, {i,j + 1} };
		}
	}
	else {
		if (j - 1 >= 0 && this->map[i][j - 1] != -1) {
			sq = sqrt(pow(i - end.first, 2) + pow(j - 1 - end.second, 2));
			return { sq, {i,j - 1} };
		}
	}
	return { NULL, {NULL, NULL} };
}

void Engine::update_q(const pair<int, int>pos, int UNIT) {
	pair<float, pair<int, int>> temp;
	for (int i{}; i < 4; i++) {
		temp = getmoves(i, pos);
		if (temp.first != NULL) 
			this->q.insert(temp);
		this->yellow.push_back(std::make_pair(scaleFromID(temp.second.first, UNIT), scaleFromID(temp.second.second, UNIT)));
	}
}

void Engine::genpath(int UNIT) {

	vector<vector<bool>>visited(this->map.size(), vector<bool>(this->map[0].size(), 0));
	pair<int, int> pos = start;
	visited[pos.first][pos.second] = 1;
	update_q(pos, UNIT);
	while (!q.empty() || pos != end) {
		if (!visited[q.begin()->second.first][q.begin()->second.second]) {
			visited[q.begin()->second.first][q.begin()->second.second] = 1;
			pos = { q.begin()->second.first, q.begin()->second.second };
			this->path.push_back(std::make_pair(scaleFromID(pos.first, UNIT), scaleFromID(pos.second, UNIT)));
			if (q.begin()->first == 1) {
				this->finished = true;
				break;
			}
			q.erase(q.begin());
			update_q(pos, UNIT);

		}
		else
			q.erase(q.begin());
	}
}

bool Engine::isfinished() {
	return this->finished;
}

vector<pair<int, int>> Engine::getPoints(int UNIT) {
	return { {scaleFromID(this->start.first, UNIT), scaleFromID(this->start.second, UNIT)}, {scaleFromID(this->end.first, UNIT), scaleFromID(this->end.second, UNIT)} };
}