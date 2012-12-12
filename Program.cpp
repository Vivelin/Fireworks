#include "Libs.h"
#include "Fireworks.h"

#define PARTICLE_DENSITY 2500

int main(int argc, char *argv[]) {
	srand((unsigned int)time(0));

    unsigned int width = 1280;
    unsigned int height = 720;
    size_t particles = (width * height) / PARTICLE_DENSITY;

	Fireworks fireworks(width, height, false);
    fireworks.SetParticleLimit(particles);
	if (fireworks.Load()) {
		fireworks.Run();
		return EXIT_SUCCESS;
	}

	sf::Sleep(1.0f);
	return EXIT_FAILURE;
}