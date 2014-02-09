#ifndef DMathRadian
#define DMathRadian

#include "Vector2.h"

class Radian
{
public:
	static double convertToGame(double myMathRadian)
	{
		Vector2 vectored = Vector2::ToVector2(myMathRadian);
		vectored.x = -vectored.x;

		return Vector2::ToMathRadian(vectored) + 3.1459/2;
	}
	static double convertToMath(double myGameRadian)
	{
		Vector2 vectored = Vector2::ToVector2(myGameRadian);
		vectored.y = -vectored.y;

		return Vector2::ToMathRadian(vectored) + 3.1459/2;
	}

};

#endif