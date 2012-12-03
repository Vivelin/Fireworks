#include "Libs.h"
#include "Fireworks.h"

int main(int argc, char *argv[]) {
	srand(time(0));

	Fireworks fireworks(1280, 720, false);
	if (fireworks.Load()) {
		fireworks.Run();
		return EXIT_SUCCESS;
	}

	sf::Sleep(1.0f);
	return EXIT_FAILURE;
}