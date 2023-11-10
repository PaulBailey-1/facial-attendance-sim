#pragma once

#include <vector>
#include <thread>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Map.h"
#include "Entity.h"

class Display : public ci::app::App {
public:

	Display();

	static Display* start();

	bool isRunning() { return getNumWindows() > 0; }

	void setMap(const Map* map) { 
		_map = map; }

	void setEntities(const std::vector<Entity>* entities) {
		_entities = entities;
	}

	void setup() override;
	void draw() override;

private:

	const float DOOR_WIDTH = 6.0; // ft

	const Map* _map = nullptr;
	const std::vector<Entity>* _entities = nullptr;

	ci::Font _font;

};

