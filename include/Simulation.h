#pragma once

#include <vector>

#include "Map.h"
#include "Device.h"
#include "Display.h"
#include "DBConnection.h"

class Simulation {
public:

	Simulation();

private:

	DBConnection _db;

	Map _map;
	Display* _display;
	std::vector<Entity> _entities;

};