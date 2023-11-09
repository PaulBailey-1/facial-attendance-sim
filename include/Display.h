#pragma once

#include <thread>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Map.h"

class Display : public ci::app::App {
public:

	Display();

	static Display* start();

	bool isRunning() { return getNumWindows() > 0; }

	void setMap(const Map* map) { 
		_map = map; }

	void draw() override;

private:

	const float DOOR_WIDTH = 6.0; // ft

	const Map* _map = nullptr;

};

