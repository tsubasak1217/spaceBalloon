#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
// range(t): 0 ~ 1;

float EaseInSine(float t);
float EaseOutSine(float t);
float EaseInOutSine(float t);

float EaseInQuad(float t);
float EaseOutQuad(float t);
float EaseInOutQuad(float t);

float EaseInCubic(float t);
float EaseOutCubic(float t);
float EaseInOutCubic(float t);

float EaseInQuart(float t);
float EaseOutQuart(float t);
float EaseInOutQuart(float t);

float EaseInQuint(float t);
float EaseOutQuint(float t);
float EaseInOutQuint(float t);

float EaseInExpo(float t);
float EaseOutExpo(float t);
float EaseInOutExpo(float t);

float EaseInCirc(float t);
float EaseOutCirc(float t);
float EaseInOutCirc(float t);

float EaseInBack(float t);
float EaseOutBack(float t);
float EaseInOutBack(float t);

float EaseInElastic(float t);
float EaseOutElastic(float t);
float EaseInOutElastic(float t);

float EaseInBounce(float t);
float EaseOutBounce(float t);
float EaseInOutBounce(float t);


