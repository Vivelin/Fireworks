#include "Libs.h"
#include "Fireworks.h"
#include "Geometry.h"
#include "Shader.h"

Fireworks::Fireworks() : width(1280), height(720), fullscreen(false) { }

Fireworks::~Fireworks() { 
	glDetachShader(shaderProgram, vertexShader->GetRef());
	glDetachShader(shaderProgram, fragmentShader->GetRef());
	glDeleteShader(vertexShader->GetRef());
	glDeleteShader(fragmentShader->GetRef());
}

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

	// Load shaders
	vertexShader = new Shader("Vertex.glsl", GL_VERTEX_SHADER);
	fragmentShader = new Shader("Fragment.glsl", GL_FRAGMENT_SHADER);
	if (!vertexShader->Compile() || !fragmentShader->Compile()) {
		return false;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader->GetRef());
	glAttachShader(shaderProgram, fragmentShader->GetRef());
	glBindAttribLocation(shaderProgram, 0, "in_position");
	glBindAttribLocation(shaderProgram, 1, "in_normal");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Initialize view points and stuff
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	viewpoint = Vector3(5.0f, 5.0f, 5.0f);
	viewtarget = Vector3(0.0f, 0.0f, 0.0f);
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
	glViewport(0, 0, this->width, this->height);
	viewmatrix = Matrix4::lookAtMatrix(viewpoint, viewtarget, Vector3(0.0f, 0.0f, 1.0f));
	projectionmatrix = Matrix4::perspectiveMatrix((float)M_PI_4, (float)width / height, 1.0f, 1000.0f);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
