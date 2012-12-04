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
