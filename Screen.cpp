#include "Screen.h"
#include <iostream>
#include <Windows.h>
Screen::Screen(float Resolution, float Width) :RES(Resolution), W(Width), H(Width / Resolution) {
	this->currBox = { NULL, NULL };
	this->engine = new Engine((this->W - 4 * this->UNIT) / this->UNIT, (this->H - 4 * this->UNIT) / this->UNIT);
	this->window.create(sf::VideoMode(this->W, this->H), "PF_Vis");
	this->box.resize(this->H);
	for (int i = this->UNIT * 2; i <= this->H - (this->UNIT * 2); i += this->UNIT) {
		this->box[i].resize(this->W);
		for (int j = this->UNIT * 2; j <= this->W - (this->UNIT * 2); j += this->UNIT) {
			this->box[i][j] = { j,i };
		}
	}
}

Screen::~Screen() {
	delete this->engine;
}

sf::RenderWindow& Screen::_window() {
	return this->window;
}

void Screen::createMatrix() {
	for (int i = this->UNIT * 2; i <= this->H - (this->UNIT * 2); i += this->UNIT) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(this->UNIT * 2, i), sf::Color::Black),
			sf::Vertex(sf::Vector2f(this->W - (this->UNIT * 2), i), sf::Color::Black)
		};
		this->window.draw(line, 2, sf::Lines);
	}
	for (int i = this->UNIT * 2; i <= this->W - (this->UNIT * 2); i += this->UNIT) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(i, this->UNIT * 2), sf::Color::Black),
			sf::Vertex(sf::Vector2f(i, this->H - (this->UNIT * 2)), sf::Color::Black)
		};
		this->window.draw(line, 2, sf::Lines);
	}
}

bool Screen::mouseOnMatrix() {
	float* x = new float(Engine::getMousePos(this->window).first);
	float* y = new float(Engine::getMousePos(this->window).second);
	Matrix f = { -1,-1 };

	auto destruct = [](float* x, float* y) {
		delete x;
		delete y;
	};
	if (*y > 2*this->UNIT && *y < this->H - 2*this->UNIT && *x>2*this->UNIT && *x < this->W - 2*this->UNIT) {
		*y = Engine::scale(*y, this->UNIT);
		*x = Engine::scale(*x, this->UNIT);
		if (this->box[(int)*y][(int)*x].x != 0) {
			this->currBox = this->box[(int)*y][(int)*x];
			destruct(x, y);
			return true;
		}
	}
	destruct(x, y);
	return false;
}

void Screen::createBgc() {
	sf::RectangleShape bg;
	bg.setFillColor(sf::Color(119, 123, 128));
	bg.setPosition(this->currBox.x, this->currBox.y);
	bg.setSize(sf::Vector2f(this->UNIT, this->UNIT));
	this->window.draw(bg);
}

void Screen::drawPoints() {
	if (engine->getPointCount() != 0) {
		for (int i = 0; i < engine->getPointCount(); i++) {
			sf::RectangleShape bg;
			bg.setSize(sf::Vector2f(this->UNIT, this->UNIT));
			bg.setFillColor(sf::Color(0, 0, 255));
			if (i == 1)
				bg.setFillColor(sf::Color(255, 0, 0));
			bg.setPosition(engine->getPoints(UNIT)[i].second, engine->getPoints(UNIT)[i].first);
			this->window.draw(bg);
		}
	}
}

void Screen::setPoint() {
	int x = Engine::scale(Engine::getMousePos(this->window).first, this->UNIT);
	int y = Engine::scale(Engine::getMousePos(this->window).second, this->UNIT);
	std::cout << x << ' ' << y << std::endl;
	engine->createPoint(x, y, this->UNIT);
}
//----
void Screen::setWall() {
	int x = Engine::scale(Engine::getMousePos(this->window).first, this->UNIT);
	int y = Engine::scale(Engine::getMousePos(this->window).second, this->UNIT);
	engine->setWall(x, y, this->UNIT);
}

void Screen::drawWall() {
	if (engine->getIsBlock()) {
		for (int i = 0; i < engine->getMapSize().second; i++) {
			for (int j = 0; j < engine->getMapSize().first; j++) {
				if (engine->getMapValue(j, i) == -1) {
					sf::RectangleShape bg;
					bg.setSize(sf::Vector2f(this->UNIT, this->UNIT));
					bg.setFillColor(sf::Color(0, 0, 0));
					bg.setPosition(Engine::scaleFromID(j, this->UNIT), Engine::scaleFromID(i, this->UNIT));
					this->window.draw(bg);
				}
			}
		}
	}
}

void Screen::drawSolution() {
	if (engine->getPointCount() == 2) {
		if (engine->getPointCount() == 2) {
			engine->genpath(UNIT);
			this->refresh = false;
		}
		
		
	}
}

void Screen::vis(){
	if (engine->isfinished() && repath) {
		for (int i{}; i < engine->yellow.size(); i++) {
			sf::RectangleShape bg;
			bg.setFillColor(sf::Color(120, 50, 200));
			bg.setSize(sf::Vector2f(this->UNIT, this->UNIT));
			bg.setPosition(engine->yellow[i].second, engine->yellow[i].first);
			//this->drawWall();
			//this->createMatrix();
			this->window.draw(bg);
			this->drawPoints();	
			this->window.display();
			Sleep(.8);
		}

		for (int i{}; i < engine->path.size(); i++) {
			sf::RectangleShape bg;
			bg.setFillColor(sf::Color(50, 200, 120));
			bg.setSize(sf::Vector2f(this->UNIT, this->UNIT));
			bg.setPosition(engine->path[i].second, engine->path[i].first);
			this->window.draw(bg);

		}
		this->createMatrix();
		this->window.display();

		this->repath = false;
	}
}

void Screen::draw(sf::Color color) {
	if (this->refresh) {
		this->_window().clear(color);
		if (this->mouseOnMatrix())
			this->createBgc();
		this->drawSolution();
		this->drawPoints();
		this->drawWall();
		this->createMatrix();
		this->_window().display(); 
	}
	else
	{
		vis();
	}
	
}
