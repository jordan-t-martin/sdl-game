#pragma once

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

	float _x, _y;
};