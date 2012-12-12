#include "Libs.h"
#include "Particle.h"

Particle::Particle() : 
	position(0, 0), color(0.0f, 0.0f, 0.0f), size(1.0f), speed(0.0f), acceleration(0.0f) {	}

Particle::Particle(Vector2 position) : 
	position(position), color(0.0f, 0.0f, 0.0f), size(1.0f), speed(0.0f), acceleration(0.0f) { }

Particle::Particle(Vector2 position, Color color) : 
	position(position), color(color), size(1.0f), speed(0.0f), acceleration(0.0f) { }

Particle::Particle(Vector2 position, Color color, float size) : 
	position(position), color(color), size(size), speed(0.0f), acceleration(0.0f) { }

Particle::Particle(Vector2 position, Color color, float size, float speed) : 
	position(position), color(color), size(size), speed(speed), acceleration(0.0f) { }

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

void Particle::Update(float frametime) {
	this->acceleration = -15.0f * this->size;
	this->speed += acceleration * frametime;
	this->position -= Vector2(0.0f, this->speed * frametime);

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

void SpawnerParticle::Update(float frametime) {
	//this->position = Vector2(0.0f, 
}