#include <stdio.h>
#include <stdlib.h>

//#1
void print_arr_point(const int *arr, size_t count);
//#2
typedef struct {
  int * data;
  size_t size;               //how much elements
  size_t capacity;           //how much elements maybe
} IntVector;

int vec_init(IntVector *v, size_t initial_capacity); //0 sucses, -1 mistake
int vec_push(IntVector *v, int value);               //0 sucses, -1 mistake
void vec_free(IntVector *v);


int main(void) {
  //#1
  printf("1:\n");
  int * arrm = malloc(5 * sizeof *arrm);
  if(arrm == NULL) {
    fprintf(stderr, "not memory\n");
    return 1;
  }
  *(arrm+2) = 16;
  printf("arrm:\n");
  print_arr_point(arrm, 5);
  free(arrm);
  arrm = NULL;
  
  int * arrc = calloc(5, sizeof *arrc);
  if(arrc == NULL) {
    fprintf(stderr, "not memory\n");
    return 1;
  }
  printf("arrc:\n");
  print_arr_point(arrc, 5);
  free(arrc);
  arrc = NULL;
  
  int *tmp = malloc(5 * sizeof *tmp);
  if (tmp == NULL) {
    fprintf(stderr, "not memory\n");
    return 1;
  }
  for (int i = 0; i < 5; i++) {
    tmp[i] = 777 + i;
  }
  printf("инициализированный malloc:\n");
  print_arr_point(tmp, 5);
  free(tmp);

  int *reused = malloc(5 * sizeof *reused);   /* скорее всего тот же блок */
  if (reused == NULL) {
    fprintf(stderr, "not memory\n");
    return 1;
  }
  printf("после повторного malloc:\n");
  print_arr_point(reused, 5);
  free(reused);
  
  //#2
  printf("\n2:\n");
  IntVector v;
  size_t size = 2;
  if(0 != vec_init(&v, size)) {
    fprintf(stderr, "not memory\n");
    return 1;
  }
  int * blocker = malloc(64 * sizeof(int));
  if (blocker == NULL) {
    fprintf(stderr, "not memory\n");
    return 1;
  }
  for(int i = 0; i < 20; i++) {
    if(0 != vec_push(&v, i*100)) {
      fprintf(stderr, "vec_push failed at i=%d\n", i);
      vec_free(&v);
      free(blocker);
      return 1;
    }
  }
  printf("size=%zu capacity=%zu\n", v.size, v.capacity);
  print_arr_point(v.data, v.size);
  vec_free(&v);
  free(blocker);
  
  
  return 0;
}

//#1
void print_arr_point(const int *arr, size_t count) {
  for(size_t i = 0; i < count; i++) {
    printf("%d\n", *(arr+i));
  }
}

//#2
int vec_init(IntVector *v, size_t initial_capacity){ //0 sucses, -1 mistake
  v->data = malloc(initial_capacity * sizeof(*v->data));
  if(v->data == NULL) {
    return -1;
  }
  v->size = 0;
  v->capacity = initial_capacity;
  return 0;
}

int vec_push(IntVector *v, int value) {
  if(v->size >= v->capacity) {
    printf("old address: %p\n", (void *)v->data);
    size_t new_cap = (v->capacity == 0) ? 1 : v->capacity * 2;
    int * tmp = realloc(v->data, new_cap * sizeof *v->data);
    if(tmp == NULL) {
      return -1;
    }
    printf("old capacity: %zu\n", v->capacity);
    v->capacity *= 2;
    v->data = tmp;
    printf("new address: %p\n", (void *)v->data);
    printf("new capacity: %zu\n", v->capacity);
  }
  v->data[v->size] = value;
  v->size++;
  return 0;
}

void vec_free(IntVector *v) {
  v->size = 0;
  v->capacity = 0;
  free(v->data);
  v->data = NULL;
}
