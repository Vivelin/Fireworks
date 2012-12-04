#include "Libs.h"
#include "Fireworks.h"
#include "Shader.h"

Fireworks::Fireworks(unsigned int width, unsigned int height, bool fullscreen) : width(width), height(height), fullscreen(fullscreen), maxParticles(300) {
	particles = new ParticleSystem(width, height);
}

Fireworks::~Fireworks() { 
	if (window != NULL) {
		delete window;
		window = NULL;
	}

	if (particles != NULL) {
		delete particles;
		particles = NULL;
	}
}

bool Fireworks::Load() {
	// Create window
	unsigned long style = sf::Style::Close;
	if (this->fullscreen)
		style |= sf::Style::Fullscreen;

	window = new sf::Window(sf::VideoMode(width, height), "Fireworks", style);
	//window->UseVerticalSync(true);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum init = glewInit();
	if (init != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(init));
		return false;
	}
	fprintf(stdout, "Loaded GLEW %s\n", glewGetString(GLEW_VERSION));

	glEnable(GL_POINT_SMOOTH);

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
			switch (windowEvent.Key.Code) {
			case sf::Key::Escape:
				window->Close();
				break;

			case sf::Key::Space:
				particles->AddRandom();
				break;
			}
			break;
		}
	}
}

void Fireworks::Update(float frametime) {
	fprintf(stdout, "Frame time: %.1f ms\t%u particle(s)\r", frametime * 1000.0f, particles->Count());

	if (particles->Count() < this->maxParticles) {
		particles->AddRandom();
	}

	particles->Update(frametime);
}

void Fireworks::Render() {
	glViewport(0, 0, this->width, this->height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, this->width, this->height, 0.0f, -1.0f, 1.0f);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	particles->Render();
}


void Fireworks::SetParticleLimit(size_t maxParticles) {
    this->maxParticles = maxParticles;
}

size_t Fireworks::GetParticleLimit() const {
    return this->maxParticles;
}
