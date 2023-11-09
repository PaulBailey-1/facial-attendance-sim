#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <cinder/Shape2d.h>

#include "Map.h"
#include "Device.h"
#include "Display.h"

class Simulation {
public:

	Simulation();

private:

	Map _map;
	Display* _display;

	//devs
	//enties

};