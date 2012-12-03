#include <cstdlib>

#include "Fireworks.h"

int main(int argc, char *argv[]) {
	Fireworks fireworks;
	fireworks.width = 1280;
	fireworks.height = 720;
	if (fireworks.Load()) {
		fireworks.Run();
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}