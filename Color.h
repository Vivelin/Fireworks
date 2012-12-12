#pragma once

class RgbColor {
public:
	typedef unsigned char byte;

	double Red;
	double Green;
	double Blue;
	double Alpha;

	RgbColor(double r, double g, double b);
	RgbColor(double r, double g, double b, double a);
	RgbColor(byte r, byte g, byte b);
	RgbColor(byte r, byte g, byte b, byte a);
};

class HslColor {
public:
	double Hue;
	double Saturation;
	double Lightness;

	HslColor(double h, double s, double l);

	RgbColor ToRGB() const;
};

