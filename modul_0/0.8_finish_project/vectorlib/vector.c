#ifndef VECTOR_C
#define VECTOR_C

#include "vector.h"
#include <math.h>

Vector2D vector_add(Vector2D a, Vector2D b) {
	Vector2D res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}

Vector2D vector_sub(Vector2D a, Vector2D b) {
	Vector2D res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}

double vector_length(Vector2D v){
	double res;
	res = sqrt(v.x*v.x + v.y*v.y);
	return res;
}

double vector_dot(Vector2D a, Vector2D b) {
	double res;
	res = a.x * b.x + a.y * b.y;
	return res;
}

#endif
