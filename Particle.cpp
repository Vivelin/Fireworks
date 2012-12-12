#include "Libs.h"
#include "Particle.h"

Particle::Particle() : 
	position(0, 0), color(0.0f, 0.0f, 0.0f), size(1.0f), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position) : 
	position(position), color(0.0f, 0.0f, 0.0f), size(1.0f), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position, Color color) : 
	position(position), color(color), size(1.0f), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position, Color color, float size) : 
	position(position), color(color), size(size), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position, Color color, float size, Vector2 speed) : 
	position(position), color(color), size(size), speed(speed), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position, Color color, float size, Vector2 speed, Vector2 force) : 
	position(position), color(color), size(size), speed(speed), force(force), lifetime(0.0f) { }

ParticleType Particle::GetType() const {
	return ParticleType::Spark;
}

Vector2 Particle::GetPosition() const {
    return this->position;
}

void Particle::SetPosition(const Vector2 &v) {
    this->position = v;
}

Color Particle::GetColor() const {
    return this->color;
}

void Particle::SetColor(const Color &c) {
    this->color = c;
}

float Particle::GetSize() const {
    return this->size;
}

void Particle::SetSize(const float &f) {
    this->size = f;
}

bool Particle::IsAlive() const {
	return (this->size > 0.5f && this->color.Lightness > 0.0f);
}

void Particle::DoPhysics(float frametime) {
	this->lifetime += frametime;

	this->acceleration = this->force * this->size;
	this->speed += acceleration * frametime;
	this->position -= this->speed * frametime;
}

void Particle::Update(float frametime) {
	DoPhysics(frametime);

	if (this->size > 2.0f)
		this->size -= 6 * frametime;
	else
		this->size -= 2 * frametime;

	if (this->color.Lightness > 0.66f)
		this->color.Lightness -= frametime;
	else
		this->color.Lightness -= 0.33 * frametime;
}

void Particle::Render() {
    glPointSize(this->size);
	glBegin(GL_POINTS);

	RgbColor rgb = this->color.ToRGB();
	glColor3d(rgb.Red, rgb.Green, rgb.Blue);
	glVertex2f(this->position.x(), this->position.y());

	glEnd();
}

SpawnerParticle::SpawnerParticle() : 
	Particle() { }
SpawnerParticle::SpawnerParticle(Vector2 position) :
	Particle(position) { }
SpawnerParticle::SpawnerParticle(Vector2 position, Color color) :
	Particle(position, color) { }
SpawnerParticle::SpawnerParticle(Vector2 position, Color color, float size) :
	Particle(position, color, size) { }
SpawnerParticle::SpawnerParticle(Vector2 position, Color color, float size, Vector2 speed) : 
	Particle(position, color, size, speed) { }
SpawnerParticle::SpawnerParticle(Vector2 position, Color color, float size, Vector2 speed, Vector2 force) :
	Particle(position, color, size, speed, force) { }

ParticleType SpawnerParticle::GetType() const { 
	return ParticleType::Spawner;
}

bool SpawnerParticle::IsAlive() const {
	return (lifetime < 1.0f);
}

void SpawnerParticle::Update(float frametime) {
	DoPhysics(frametime);
}