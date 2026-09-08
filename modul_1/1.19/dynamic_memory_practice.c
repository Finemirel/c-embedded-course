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
//#4
int *make_range(size_t n);


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
  size_t initial_capacity = 2;
  if(0 != vec_init(&v, initial_capacity)) {
    fprintf(stderr, "not memory\n");
    return 1;
  }
  int * blocker = malloc(64 * sizeof *blocker);
  if (blocker == NULL) {
    fprintf(stderr, "not memory\n");
    vec_free(&v);
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
  
  //#3
  /*В отличии от стандартного создания двухмерного массива,
  выделение памяти динамически позволяет нам выделить область памяти
  не линейно (одним куском памяти), а разбить её на части, что даёт возможность
  создания многомерных массивов не имея в куче целого отрезка для выделения 
  для подобного массива нужного количества памяти.
  В случае с плоским массивом мы обращаемся к памяти один раз, а далее значение
  в нужной ячейке находим через арифметику указателей. С многомерными массивами выделеных
  динамически нам нужно обраощатся к памяти как минимум 2 раза для нахождения
  нужной ячейки: первый раз к массиву указателей, потом прочитав указатель перейти по 
  этому адресу и если это уже не массив указателей, при помощи арифметики указателей
  найти нужную ячейку. Повторный запрос в память может увеличивает шанс на ошибку.*/
  printf("\n3:\n");
  int **matrix = malloc(3 * sizeof(*matrix));
  if (matrix == NULL) {
    fprintf(stderr, "not memory\n");
    return 1;
  }
  for(int i = 0; i < 3; i++) {
    matrix[i] = malloc(4 * sizeof(*matrix[i]));
    if (matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {   /* освобождаем то, что успели выделить */
        free(matrix[j]);
      }
      free(matrix);
      fprintf(stderr, "out of memory\n");
      return 1;
    }
  }
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 4; j++) {
      matrix[i][j] = i * 10 + j;
    }
  }
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 4; j++) {
      printf("%2d\t", matrix[i][j]);
    }
    printf("\n");
  }
  for(int i = 0; i < 3; i++) {
    free(matrix[i]);
    matrix[i] = NULL;
  }
  free(matrix);
  matrix = NULL;
  
  //#4
  size_t count = 5;
  printf("\n4:\n");
  int * my_array = make_range(count);
  if (my_array == NULL) {
    fprintf(stderr, "not memory\n");
    return 1;
  }
  print_arr_point(my_array, count);
  free(my_array);
  my_array = NULL;
  
  //#5
printf("\n5:\n");

/*5.1 УТЕЧКА
  valgrind: 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
            at  malloc by main (dynamic_memory_practice.c:157)
int *leak = malloc(100 * sizeof *leak);
leak[0] = 1;
*/

/*5.2 DOUBLE FREE
  valgrind: Invalid free() / delete / delete[] / realloc()
            at free by main (dynamic_memory_practice.c:166)
int *df = malloc(10 * sizeof *df);
free(df);
free(df);
*/

/*5.3 USE AFTER FREE
  valgrind: Invalid write of size 4 at  main (dynamic_memory_practice.c:175)
            Address is 0 bytes inside a block of size 40 free'd
            at free by main (dynamic_memory_practice.c:174)
int *uaf = malloc(10 * sizeof *uaf);
free(uaf);
uaf[0] = 42;
*/

/* 5.4 HEAP OVERFLOW
  valgrind: Invalid write of size 4 at main (dynamic_memory_practice.c:183)
            Address is 0 bytes after a block of size 40 alloc'd at
            malloc by main (dynamic_memory_practice.c:182)
int *ovf = malloc(10 * sizeof *ovf);
ovf[10] = 99;
free(ovf);
*/
  
  
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
    v->capacity = new_cap;
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

//#4
/*Владельцем памяти является вызывающий данную функцию, здесь в частности main(),
который обязан вызвать free, что бы освободить память*/ 
int * make_range(size_t n) {
  int *arr = malloc(n * sizeof *arr);
  if(arr == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < n; i++) {
    arr[i] = (int)i;
  }
  return arr;
}
