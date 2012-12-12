#pragma once
#include "Libs.h"

enum ParticleType {
	Spark,
	Spawner
};

class Particle {
public:
	Particle();
	Particle(Vector2 position);
	Particle(Vector2 position, Color color);
	Particle(Vector2 position, Color color, float size);
	Particle(Vector2 position, Color color, float size, Vector2 speed);
	Particle(Vector2 position, Color color, float size, Vector2 speed, Vector2 force);

	virtual ParticleType GetType() const;

    Vector2 GetPosition() const;
    void SetPosition(const Vector2 &v);

    Color GetColor() const;
    void SetColor(const Color &c);

    float GetSize() const;
    void SetSize(const float &f);

	virtual bool IsAlive() const;

    virtual void Update(float frametime);
    virtual void Render();

protected:
	Vector2 position;
	Color color;
	float size;

	Vector2 force;
	Vector2 speed;
	Vector2 acceleration;

	virtual void DoPhysics(float frametime);
};

class SpawnerParticle : public Particle {
public:
	SpawnerParticle();
	SpawnerParticle(Vector2 position);
	SpawnerParticle(Vector2 position, Color color);
	SpawnerParticle(Vector2 position, Color color, float size);
	SpawnerParticle(Vector2 position, Color color, float size, Vector2 speed);
	SpawnerParticle(Vector2 position, Color color, float size, Vector2 speed, Vector2 force);

	ParticleType GetType() const;

	void Update(float frametime);
};