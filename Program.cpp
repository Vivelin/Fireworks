#include "Libs.h"
#include "Fireworks.h"

int main(int argc, char *argv[]) {
	Fireworks fireworks;
	fireworks.width = 1280;
	fireworks.height = 720;
	fireworks.fullscreen = false;
	if (fireworks.Load()) {
		fireworks.Run();
		return EXIT_SUCCESS;
	}

	sf::Sleep(1.0f);
	return EXIT_FAILURE;
}