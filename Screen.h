#pragma once
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <vector>
class Screen
{
private:
	struct Matrix		// 
	{
		int x;
		int y;
	};
	Matrix currBox;
	const int UNIT = 25;	// Square box size in px
	const float RES;		// Resolution
	const float W;		// Width
	const float H;		// Height
	std::vector<std::vector<Matrix>> box;	//vector with positon of boxes
	sf::RenderWindow window;
	bool refresh = true;
	Engine* engine;
public:
	bool repath = true;
	Screen(float Resolution, float Width);
	~Screen();
	sf::RenderWindow& _window();	// get window
	void createMatrix();	// draw square boxes
	void createBgc();		// create background on box where mouse is pointing
	bool mouseOnMatrix();	// check if mouse is on box of matrix
	void setPoint();
	void drawPoints();
	//---
	void setWall();
	void drawWall();
	void draw(sf::Color color);
	void drawSolution();
	void vis();
};

