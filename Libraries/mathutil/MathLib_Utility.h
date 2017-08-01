#pragma once

#define _PI 3.14159265358979323846f
#define _2PI (_PI*2f)
#define _PIOVER2 _PI/2f
#define _PI_OVER_180 0.01745329f		// 1 radian
#define _180_OVER_PI 57.29578f		 

float degToRad(float degrees) { return degrees * _PI_OVER_180; }
float radToDeg(float radians) { return radians * _180_OVER_PI; }

//Assembly fsqrt 2 - Fastest square root method: https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
///DO NOT CHANGE DOUBLE TO FLOAT, ERRORS WILL OCCUR!
double inline __declspec (naked) __fastcall sqrt14(double n)
{
	_asm fld qword ptr[esp + 4]
		_asm fsqrt
	_asm ret 8
}