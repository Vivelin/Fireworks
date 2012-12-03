#include "Libs.h"
#include "Fireworks.h"
#include "Geometry.h"
#include "Shader.h"

Fireworks::Fireworks() : width(1280), height(720), fullscreen(false) { }

Fireworks::~Fireworks() { }

bool Fireworks::Load() {
	// Create window
	unsigned long style = sf::Style::Close;
	if (this->fullscreen)
		style |= sf::Style::Fullscreen;

	window = new sf::Window(sf::VideoMode(width, height), "Fireworks", style);
	window->UseVerticalSync(true);

	// Initialize GLEW
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
	fprintf(stdout, "Frame time: %.4f ms\r", frametime);
}

void Fireworks::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
