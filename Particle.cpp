#include "Libs.h"
#include "Particle.h"

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
    this->position -= Vector2(0.0f, -frametime * 30.0f);
	this->size -= frametime;
}

void Particle::Render() {
    glPointSize(this->size);
	glBegin(GL_POINTS);

	glColor4b(this->color.r(), this->color.g(), this->color.b(), this->color.a());
	glVertex2f(this->position.x(), this->position.y());

	glEnd();
}
