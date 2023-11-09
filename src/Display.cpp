
#include "Display.h"

bool displayRunning = false;

Display::Display() {
	displayRunning = true;
}

Display* Display::start() {
	std::thread thread([] {
		cinder::app::RendererRef renderer(new ci::app::RendererGl);
		cinder::app::AppMsw::main<Display>(renderer, "Simulation");
	});
	thread.detach();
	while (cinder::app::AppMsw::get() == nullptr || !displayRunning) {}
	return (Display*) cinder::app::AppMsw::get();
}

void Display::draw() {
	ci::ColorA grey = ci::Color::gray(0.5);

	ci::gl::clear(grey);

	if (_map == nullptr) {
		return;
	}

	ci::gl::setMatricesWindow(getWindowSize());

	float scale = getWindowSize().x / _map->size.x * 0.9;
	ci::gl::translate(getWindowSize().x * 0.05, getWindowSize().y * 0.05);
	ci::gl::scale(scale, scale);

	ci::gl::color(ci::Color::white());
	for (const ci::Shape2d& shape : _map->inBounds) {
		ci::gl::drawSolid(shape);
	}

	ci::gl::color(grey);
	for (const ci::Shape2d& shape : _map->outBounds) {
		ci::gl::drawSolid(shape);
	}

	ci::gl::color(ci::Color(1, 0, 0));
	for (const Door &door : _map->doors) {
		ci::gl::pushModelMatrix();
		ci::gl::translate(door.pos);
		ci::gl::rotate(door.angle * (M_PI / 180));
		//ci::gl::drawLine({ -DOOR_WIDTH / 2, 0 }, {DOOR_WIDTH / 2, 0});
		ci::gl::drawSolidRect(ci::Rectf());
		ci::gl::popModelMatrix();
	}

}