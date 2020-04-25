#pragma once
#include "math.h"

class Vector2 {
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	Vector2 add(Vector2 a, Vector2 b);
	Vector2 subtract(Vector2 a, Vector2 b);
	Vector2 multiply_scalar(float scalar, Vector2 vec);
	float length(Vector2 a);
	float distance(Vector2 a, Vector2 b);
	float dot_product(Vector2 a, Vector2 b);
	Vector2 normalize(Vector2 a);

	int inline getX() { return _x; }
	int inline getY() { return _y; }
	void inline setX(int x) { _x = x; }
	void inline setY(int y) { _y = y; }

private:
	float _x, _y = 0;
};