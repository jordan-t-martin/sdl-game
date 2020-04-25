#include "vector2.h"

Vector2::Vector2() {

}

Vector2::Vector2(float x, float y) : _x(x), _y(y) {

}

Vector2::~Vector2() {

}

Vector2 Vector2::add(Vector2 a, Vector2 b) {
	float x = a._x + b._x; 
	float y = a._y + b._y;
	return Vector2(x, y);
}

Vector2 Vector2::subtract(Vector2 a, Vector2 b) {
	float x = a._x - b._x;
	float y = a._y - b._y;
	return Vector2(x, y);
}

Vector2 Vector2::multiply_scalar(float scalar, Vector2 vec) {
	float x = vec._x * scalar;
	float y = vec._y * scalar;
	return Vector2(x, y);
}

float Vector2::length(Vector2 a) {
	return sqrtf((a._x * a._x) + (a._y * a._y));
}

float Vector2::distance(Vector2 a, Vector2 b) {
	return length(subtract(b, a));
}

float Vector2::dot_product(Vector2 a, Vector2 b) {
	return ((a._x * b._x) + (a._y * b._y));
}

Vector2 Vector2::normalize(Vector2 a) {
	float x = a._x / length(a);
	float y = a._y / length(a);
	return Vector2(x, y);
}