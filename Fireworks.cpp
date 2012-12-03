#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <cstddef>

#include "Fireworks.h"

Fireworks::Fireworks() {
	width = 1280;
	height = 720;
}

Fireworks::~Fireworks() {

}

bool Fireworks::Load() {
	window = new sf::Window(sf::VideoMode(width, height), "Fireworks", sf::Style::Close);
	window->UseVerticalSync(true);

	glewExperimental = GL_TRUE;
	GLenum init = glewInit();
	if (init != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(init));
		return false;
	}

	fprintf(stdout, "Loaded GLEW %s\n", glewGetString(GLEW_VERSION));
	return true;
}

void Fireworks::Run() {
	while (window->IsOpened()) {
		DoEvents();

		float frametime = window->GetFrameTime();
		Update(frametime);
		Render();

		window->Display();
	}
}

void Fireworks::DoEvents() {
	sf::Event windowEvent;
	while (window->GetEvent(windowEvent)) {
		switch (windowEvent.Type) {
		case sf::Event::Closed:
			window->Close();
			break;

		case sf::Event::KeyPressed:
			if (windowEvent.Key.Code == sf::Key::Escape)
				window->Close();
			break;
		}
	}
}

void Fireworks::Update(float frametime) {
	fprintf(stdout, "Frame time: %.3f ms\r", frametime);
}

void Fireworks::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
