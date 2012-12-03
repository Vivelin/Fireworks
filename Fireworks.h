#ifndef _FIREWORKS
#define _FIREWORKS

#include <SFML/Window.hpp>

class Fireworks {
public:
	Fireworks();
	~Fireworks();

	unsigned int width;
	unsigned int height;

	bool Load();
	void Run();
	void Update(float frametime);
	void Render();

private:
	sf::Window *window;

	void DoEvents();
};


#endif _FIREWORKS