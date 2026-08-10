#include <stdio.h>
#include "vector.h"

int main() {
	Vector2D v1 = {2.0, 4.0};
	Vector2D v2 = {3.0, 1.0};
	
	Vector2D sum = vector_add(v1, v2);
	printf("Summa vectorov = %f ,%f!\n", sum.x, sum.y);
	
	Vector2D sub = vector_sub(v1, v2);	
	printf("Minus vectorov = %f ,%f!\n", sub.x, sub.y);
	
	double dot = vector_dot(v1, v2);
	printf("Skalar vectorov = %f!\n", dot);
	
	double len = vector_length(v1);
	printf("Length vector = %f!\n", len);
	
	return 0;
}
