#include "Color.hpp"

Color::Color()
{
	Red = 0xFF;
	Green = 0xFF;
	Blue = 0xFF;
	Alpha = 0xFF;
}

Color Color::addRed()
{
	return addRed(1);
}

Color Color::addRed(int add)
{
	Red += add;

	if (255 <= Red) {
		Red = 255;
	}

	return *this;
}

Color Color::subRed() {
	return subRed(1);
}

Color Color::subRed(int sub) {
	Red -= sub;

	if (Red <= 0) {
		Red = 0;
	}

	return *this;
}

Color Color::setRed(int red)
{
	Red = red % 256;
	return *this;
}

Color Color::addGreen()
{
	return addGreen(1);
}

Color Color::addGreen(int add)
{
	Green += add;

	if (255 <= Green) {
		Green = 255;
	}

	return *this;
}

Color Color::subGreen() {
	return subGreen(1);
}

Color Color::subGreen(int sub) {
	Green -= sub;

	if (Green <= 0) {
		Green = 0;
	}

	return *this;
}

Color Color::setGreen(int green)
{
	Green = green % 256;
	return *this;
}

Color Color::addBlue()
{
	return addBlue(1);
}

Color Color::addBlue(int add)
{
	Blue += add;

	if (255 <= Blue) {
		Blue = 255;
	}

	return *this;
}

Color Color::subBlue() {
	return subBlue(1);
}

Color Color::subBlue(int sub) {
	Blue -= sub;

	if (Blue <= 0) {
		Blue = 0;
	}

	return *this;
}

Color Color::setBlue(int blue)
{
	Blue = blue % 256;
	return *this;
}

Color Color::addAlpha()
{
	return addAlpha(1);
}

Color Color::addAlpha(int add)
{
	Alpha += add;

	if (255 <= Alpha) {
		Alpha = 255;
	}

	return *this;
}

Color Color::subAlpha() {
	return subAlpha(1);
}

Color Color::subAlpha(int sub) {
	Alpha -= sub;

	if (Alpha <= 0) {
		Alpha = 0;
	}

	return *this;
}

Color Color::setAlpha(int alpha)
{
	Alpha = alpha % 256;
	return *this;
}