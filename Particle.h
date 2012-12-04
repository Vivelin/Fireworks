#pragma once
#include "Libs.h"

class Particle {
public:
	Particle() : 
		position(0, 0), color(255, 255, 255), size(1.0f) {	}

	Particle(Vector2 position) : 
		position(position), color(255, 255, 255), size(1.0f) { }

	Particle(Vector2 position, Color color) : 
		position(position), color(color), size(1.0f) { }

	Particle(Vector2 position, Color color, float size) : 
		position(position), color(color), size(size) { }

    Vector2 GetPosition() const;
    void SetPosition(const Vector2 &v);

    Color GetColor() const;
    void SetColor(const Color &c);

    float GetSize() const;
    void SetSize(const float &f);

    void Update(float frametime);
    void Render();

private:
	Vector2 position;
	Color color;
	float size;
};
