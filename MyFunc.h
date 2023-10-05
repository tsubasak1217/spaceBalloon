#pragma once
#include <math.h>
#include <Vector2.h>
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Matrix2x2.h"
//================================================================
//LoadFileに使う
#include <fstream>
#include <sstream>
#include <vector>
//================================================================
#include "Easing.h"

std::vector<std::vector<int>>LoadFile(const std::string& csvFilePath);

float CheckLength(Vector2 pos1, Vector2 pos2);

float Cross(
	float line1StartX, float line1StartY,
	float line1EndX, float line1EndY,
	float targetX, float targetY
);

float CrossV(Vector2 pos1, Vector2 pos2, Vector2 targetPos);

Vector2 CrossPos(
	Vector2 line1Pos1, Vector2 line1Pos2,
	Vector2 line2Pos1, Vector2 line2Pos2
);

Vector2 ShiftLine(Vector2 pos1, Vector2 pos2, float distance);

Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix);

void MatrixScreenPrintf(int posX, int posY, Matrix2x2 matrix);
void Vector2ScreenPrintf(int posX, int posY, Vector2 vector);

float CalculateBuoyantForce(float densityObject, float densityLiquid, float volumeObject, float gravity);

float calculateSinkingSpeed(float densityObject, float densityLiquid, float gravity);

float CalcSinkSpeed(float objectWeight, float spaceWeight, float gravity);