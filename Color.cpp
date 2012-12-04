#include <cmath>
#include "Color.h"

RgbColor::RgbColor(double r, double g, double b) : 
	Red(r), Green(g), Blue(b), Alpha(1.0f) { }

RgbColor::RgbColor(double r, double g, double b, double a) : 
	Red(r), Green(g), Blue(b), Alpha(a) { }

RgbColor::RgbColor(byte r, byte g, byte b) : 
	Red(r / 255.0f), Green(g / 255.0f), Blue(b / 255.0f), Alpha(1.0f) { } 

RgbColor::RgbColor(byte r, byte g, byte b, byte a) : 
	Red(r / 255.0f), Green(g / 255.0f), Blue(b / 255.0f), Alpha(a / 255.0f) { }

HslColor::HslColor(double h, double s, double l) : Saturation(s), Lightness(l) {
	this->Hue = h - 360.0f * floor(h / 360.0f);
}

RgbColor HslColor::ToRGB() {
	double chroma  = (1 - abs(2*Lightness - 1)) * Saturation;
	double hh = Hue / 60;
	double x = chroma * (1 - fabs(fmod(hh, 2) - 1));

	double r = 0, g = 0, b = 0;
	if (0 <= hh && hh < 1) {
		r = chroma; g = x; b = 0;
	}
	else if (1 <= hh && hh < 2) {
		r = x; g = chroma; b = 0;
	}
	else if (2 <= hh && hh < 3) {
		r = 0; g = chroma; b = x;
	}
	else if (3 <= hh && hh < 4) {
		r = 0; g = x; b = chroma;
	}
	else if (4 <= hh && hh < 5) {
		r = x; g = 0; b = chroma;
	}
	else if (5 <= hh && hh < 6) {
		r = chroma; g = 0; b = x;
	}

	double m = Lightness - 0.5f * chroma;
	return RgbColor(r + m, g + m, b + m);
}