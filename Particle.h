#pragma once
#include "Libs.h"

class Particle {
public:
	Particle();
	Particle(Vector2 position);
	Particle(Vector2 position, Color color);
	Particle(Vector2 position, Color color, float size);
	Particle(Vector2 position, Color color, float size, float speed);
	Particle(Vector2 position, Color color, float size, float speed, float force);

    Vector2 GetPosition() const;
    void SetPosition(const Vector2 &v);

    Color GetColor() const;
    void SetColor(const Color &c);

    float GetSize() const;
    void SetSize(const float &f);

    virtual void Update(float frametime);
    virtual void Render();

protected:
	Vector2 position;
	Color color;
	float size;

	float force;
	float speed;
	float acceleration;
};

class SpawnerParticle : public Particle {
public:
	void Update(float frametime);
};