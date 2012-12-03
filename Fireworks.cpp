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

	return true;
}

void Fireworks::Run() {
	while (window->IsOpened()) {
		DoEvents();
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

void Fireworks::Update() {

}

void Fireworks::Render() {

}
