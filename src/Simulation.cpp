
#include "Simulation.h"

ci::Shape2d makeRect(glm::vec2 topLeft, float width, float height) {
	ci::Shape2d shape;
	shape.moveTo(topLeft);
	shape.lineTo(glm::vec2(topLeft.x + width, topLeft.y));
	shape.lineTo(glm::vec2(topLeft.x + width, topLeft.y + height));
	shape.lineTo(glm::vec2(topLeft.x, topLeft.y + height));
	shape.close();
	return shape;
}

Simulation::Simulation() {

	_map.size = {300, 200};

	_map.inBounds.push_back(makeRect({0, 0}, 300, 200));
	_map.outBounds.push_back(makeRect({50, 50}, 200, 100));

	_map.devs.push_back(Device(0, { 150, 25 }, 180));
	_map.devs.push_back(Device(1, { 150, 25 }, 0));
	_map.devs.push_back(Device(2, { 275, 100 }, 90));
	_map.devs.push_back(Device(3, { 275, 100 }, -90));
	_map.devs.push_back(Device(4, { 150, 175 }, 0));
	_map.devs.push_back(Device(5, { 150, 175 }, 180));
	_map.devs.push_back(Device(6, { 25, 100 }, -90));
	_map.devs.push_back(Device(7, {25, 100}, 90));

	_map.doors.push_back(Door(0, { 25, 0 }, 0));
	_map.doors.push_back(Door(1, { 75, 0 }, 0));
	_map.doors.push_back(Door(2, { 125, 0 }, 0));
	_map.doors.push_back(Door(3, { 175, 0 }, 0));
	_map.doors.push_back(Door(4, { 225, 0 }, 0));
	_map.doors.push_back(Door(5, { 275, 0 }, 0));

	_map.doors.push_back(Door(6, { 300, 25 }, 90));
	_map.doors.push_back(Door(7, { 300, 75 }, 90));
	_map.doors.push_back(Door(8, { 300, 125 }, 90));
	_map.doors.push_back(Door(9, { 300, 175 }, 90));

	_map.doors.push_back(Door(10, { 275, 200 }, 0));
	_map.doors.push_back(Door(11, { 225, 200 }, 0));
	_map.doors.push_back(Door(12, { 175, 200 }, 0));
	_map.doors.push_back(Door(13, { 125, 200 }, 0));
	_map.doors.push_back(Door(14, { 75, 200 }, 0));
	_map.doors.push_back(Door(15, { 25, 200 }, 0));

	_map.doors.push_back(Door(16, { 0, 175 }, 90));
	_map.doors.push_back(Door(17, { 0, 125 }, 90));
	_map.doors.push_back(Door(18, { 0, 75 }, 90));
	_map.doors.push_back(Door(19, { 0, 25 }, 90));

	_display = Display::start();
	_display->setMap(&_map);

	if (_db.connect()) {
		db.getEntities(_entities);
    }

}