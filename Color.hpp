#pragma once

#define RED 0xFF0000FF
#define GREEN 0x008000FF
#define BLUE 0x0000FFFF
#define WHITE 0xFFFFFFFF
#define BLACK 0x000000FF

#define YELLOW 0xFFFF00FF
#define GOLD 0xFFD700FF
#define ORANGE 0xFFA500FF
#define BROWN 0xA52A2AFF
#define PINK 0xFFC0CBFF
#define MAGENTA 0xFF00FFFF
#define PURPLE 0x800080FF
#define CYAN 0x00A1E9FF
#define AQUA 0x00FFFFFF
#define LIME 0x00FF00FF

class Color
{
private:
	unsigned int Red,
		Green,
		Blue,
		Alpha;

public:
	Color();

	Color addRed();
	Color addRed(int add);
	Color subRed();
	Color subRed(int sub);
	Color setRed(int red);

	Color addGreen();
	Color addGreen(int add);
	Color subGreen();
	Color subGreen(int sub);
	Color setGreen(int green);

	Color addBlue();
	Color addBlue(int add);
	Color subBlue();
	Color subBlue(int sub);
	Color setBlue(int blue);

	Color addAlpha();
	Color addAlpha(int add);
	Color subAlpha();
	Color subAlpha(int sub);
	Color setAlpha(int alpha);

	unsigned int to_int() const {
		return ((Red & 0xFF) << 24) | ((Green & 0xFF) << 16) | ((Blue & 0xFF) << 8) | (Alpha & 0xFF);
	}

	Color setCode(unsigned int code) {
		Red = (code >> 24) & 0xFF;
		Green = (code >> 16) & 0xFF;
		Blue = (code >> 8) & 0xFF;
		Alpha = code & 0xFF;

		return *this;
	}
};

