#pragma once
#include "Libs.h"

class Particle {
public:
	Particle();
	Particle(Vector2 position);
	Particle(Vector2 position, Color color);
	Particle(Vector2 position, Color color, float size);
	Particle(Vector2 position, Color color, float size, Vector2 speed);
	Particle(Vector2 position, Color color, float size, Vector2 speed, Vector2 force);

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

	Vector2 force;
	Vector2 speed;
	Vector2 acceleration;
};

class SpawnerParticle : public Particle {
public:
	void Update(float frametime);
};