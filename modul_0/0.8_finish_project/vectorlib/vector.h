#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	double x;
	double y;
} Vector2D;

Vector2D vector_add(Vector2D a, Vector2D b);
Vector2D vector_sub(Vector2D a, Vector2D b);
double vector_dot(Vector2D a, Vector2D b);
double vector_length(Vector2D v);

#endif
