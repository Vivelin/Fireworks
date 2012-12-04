#pragma once
#include "Libs.h"

enum ParticleType {
	Snow
};

class Particle {
public:
	Particle(ParticleType type);
	Particle(ParticleType type, Vector2 position);
	Particle(ParticleType type, Vector2 position, Color color);
	Particle(ParticleType type, Vector2 position, Color color, float size);

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
	ParticleType type;
};
