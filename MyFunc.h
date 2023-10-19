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
#include <algorithm>
//================================================================
#include "Easing.h"

std::vector<std::vector<int>>LoadFile(const std::string& csvFilePath);

float CheckLength(Vector2 pos1, Vector2 pos2);
float CheckLength(float pos1x, float pos1y, float pos2x, float pos2y);

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

float CalcSinkSpeed(float objectWeight, float spaceWeight, float gravity);

bool IsHitBox_Ball(Vector2 boxCenter, Vector2 ballPos, Vector2 boxSize, float ballRasius);
int IsHitBox_BallDirection(Vector2 boxCenter, Vector2 ballPos, Vector2 boxSize, float ballRasius);

bool CheckBalloonLimit(int hitDirection, int preHitDirection);

void SetColor(unsigned int startColor, unsigned int aimColor, int propotion);

//色を変える関数
int Red(int color);
int Green(int color);
int Blue(int color);
int Alpha(int color);

int ChangeColor(int startColor, int aimColor, float divideNum, float rate);
int GrayScale(int color);

//星を描く関数
void DrawStar(Vector2 center, float radius, float theta, int color);

//中心点基準に三角形を描く関数
void DrawTriangle(Vector2 center, float radius, float theta, int color);