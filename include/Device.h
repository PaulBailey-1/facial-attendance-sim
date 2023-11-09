#pragma once

#include <glm/glm.hpp>
#include <cinder/Shape2d.h>

class Device {
    
public:

	Device(int id, glm::vec2 pos, float angle);

private:

	const float CAM_ANGLE = 90 * (M_PI / 180); // degrees
	const float CAM_RANGE = 10; // ft

	int _id;
	glm::vec2 _pos;
	ci::Shape2d _view;

};