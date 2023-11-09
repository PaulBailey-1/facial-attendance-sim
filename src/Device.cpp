

#include "Device.h"

Device::Device(int id, glm::vec2 pos, float angle) : _id(id), _pos(pos) {

	_view.moveTo({0, 0});
	_view.lineTo({ CAM_RANGE, 0 });
	_view.arc({0, 0}, CAM_RANGE, 0.0, CAM_ANGLE);
	_view.close();
	glm::mat3 rot = glm::rotate(glm::mat3(), float(CAM_ANGLE / 2 + angle * (M_PI / 180)));
	_view.transform(rot);
	_view.translate(pos);
}