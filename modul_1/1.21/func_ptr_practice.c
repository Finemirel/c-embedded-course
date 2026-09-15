#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int add(int, int);
int sub(int, int);
int mul(int, int);

//typedef int (*op)(int, int);
typedef int (*BinaryOp)(int, int);
static const BinaryOp ops[] = {add, sub, mul};
static const char * const namesBop[] = {"+", "-", "*"};
int calc(int a, int b, BinaryOp op);
void for_each(const int *arr, size_t n, void (*action)(int));
void print_number(int);
void print_square(int);
typedef struct {
  char name[16];
  int value;
} Sensor;
int cmp_by_value(const void *a, const void *b);
int cmp_by_name(const void *a, const void *b);
typedef struct {
    int threshold;
    int count;
} CountCtx;
typedef void (*Visitor)(int value, void *ctx);
void for_each_ctx(const int *arr, size_t n, Visitor visit, void *ctx);
static void count_above(int value, void *ctx);
typedef enum {
  EVENT_BUTTON,
  EVENT_TIMER,
  EVENT_SENSOR,
  EVENT_COUNT
} EventType;
static const char *event_names[EVENT_COUNT] = {
    [EVENT_BUTTON] = "EVENT_BUTTON",
    [EVENT_TIMER]  = "EVENT_TIMER",
    [EVENT_SENSOR] = "EVENT_SENSOR"
};
static void (*handlers[EVENT_COUNT])(void);
int register_handler(EventType type, void (*h)(void));
void dispatch(EventType type);
static void on_button_short(void);
static void on_button_long(void);
static void on_timer(void);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <part 1-6>\n", argv[0]);
    return 1;
  }
  char *end;
  long part = strtol(argv[1], &end, 10);
  if (*end != '\0') {
    fprintf(stderr, "First argument not a number: %s\n", argv[1]);
    return 1;
  }
  
  switch (part) {
    case 1: {
      //op opp = add;
      BinaryOp bop = add;
      int a = 17, b = 4;
      printf("Part %ld\n", part);
      printf("a + b = %d\n", bop(a, b));
      printf("a + b = %d\n", (*bop)(a, b));
      printf("(void *)add = %p\n", (void *)add);
      printf("(void *)&add = %p\n", (void *)&add);
      printf("Comparison result = %d\n", (void *)add == (void *)&add);
      /*
      int *f(int) это функция принимающая int и возвращющая int, 
      а int (*f)(int) это указатель на функцию которая принимает int 
      и возвращает int;
      */
      break;
    }
    case 2: {
      printf("Part %ld\n", part);
      int paramOne = 0, paramTwo = 0;
      printf("Enter first number: ");
      if(1 != scanf("%d", &paramOne)) {
        fprintf(stderr, "Incorrect input\n");
        return 1;
      }
      printf("\33[1A");
      printf("\33[2K");
      printf("First number is %d, enter second number: ", paramOne);
      if(1 != scanf("%d", &paramTwo)) {
        fprintf(stderr, "Incorrect input\n");
        return 1;
      }
      printf("\33[1A");
      printf("\33[2K");
      for (size_t i = 0; i < sizeof(namesBop) / sizeof(namesBop[0]); i++) {
        printf("%d %s %d = %d\n", paramOne, namesBop[i], paramTwo, ops[i](paramOne, paramTwo));
      }
      BinaryOp biop = NULL;
      int myNumber = calc(paramOne, paramTwo, biop);
      printf("My number = %d\n", myNumber);
      break;
    }
    case 3: {
      printf("Part %ld\n", part);
      const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
      for_each(arr, sizeof(arr)/sizeof(arr[0]), print_number);
      for_each(arr, sizeof(arr)/sizeof(arr[0]), print_square);
      break;
    }
    case 4: {
      printf("Part %ld\n", part);
      Sensor sensors[5] = {0};
      const size_t count = sizeof sensors / sizeof sensors[0];
      char arrName[5][16] = {"Temperat", "Temp", "Temp", "Temperature", "Temperatu"};
      int arrValue[5] = {12, 452, 67, 22, 5643};
      for(size_t i = 0; i < count; i++) {
        strcpy(sensors[i].name, arrName[i]);
        sensors[i].value = arrValue[i];
      }
      printf("Original:\n");
      for(size_t i = 0; i < count; i++) {
        printf("Name is %s - value: %d\n", sensors[i].name, sensors[i].value);
      }
      qsort(sensors, count, sizeof(sensors[0]), cmp_by_value);
      printf("After cmp_by_value:\n");
      for(size_t i = 0; i < count; i++) {
        printf("Name is %s - value: %d\n", sensors[i].name, sensors[i].value);
      }
      qsort(sensors, count, sizeof(sensors[0]), cmp_by_name);
      printf("After cmp_by_name:\n");
      for(size_t i = 0; i < count; i++) {
        printf("Name is %s - value: %d\n", sensors[i].name, sensors[i].value);
      }
      /*
      return sa->value - sb->value; — плохая идея, так как при значениях 
      приближенных от половины максимального значения int до его максимума 
      можем выйти за пределы int и результат может быть неверный. 
      Например -1296674271 и 1330004021.
      */
      break;
    }
    case 5: {
      printf("Part %ld\n", part);
      int arr[] = { 46, 11, 6, 79, 31, 5, 64, 33 };
      size_t n = sizeof arr / sizeof arr[0];
      CountCtx ctx_one = { .threshold = 47, .count = 0 };
      CountCtx ctx_two = { .threshold = 12, .count = 0 };
      for_each_ctx(arr, n, count_above, &ctx_one);
      //for_each_ctx(arr, n, count_above, &ctx_one); 
      //счётчик не обнулён, продолжает прибавлять.
      printf("%d\n", ctx_one.count);
      for_each_ctx(arr, n, count_above, &ctx_two);
      printf("%d\n", ctx_two.count);
      break;
    }
    case 6: {
      printf("Part %ld\n", part);
      register_handler(EVENT_BUTTON, on_button_short);
      register_handler(EVENT_TIMER, on_timer);
      dispatch(EVENT_BUTTON);
      dispatch(EVENT_TIMER);
      dispatch(EVENT_SENSOR);
      register_handler(EVENT_BUTTON, on_button_long);
      dispatch(EVENT_BUTTON);
      printf("register_handler(99) вернул %d\n", register_handler((EventType)99, on_timer));
      break;
    }
    default:
        fprintf(stderr, "Unknown part: %ld\n", part);
        return 1;
    }
  
  
  return 0;
}

int add(int a, int b) {
  return a + b;
}

int sub(int a, int b) {
  return a - b;
}

int mul(int a, int b) {
  return a * b;
}

int calc(int a, int b, BinaryOp op) {
  if(op == NULL) {
    fprintf(stderr, "op is NULL\n");
    return 0;
  }
  return op(a, b);
}

void for_each(const int *arr, size_t n, void (*action)(int)) {
  for(size_t i = 0; i < n; i++) {
    action(arr[i]);
  }
}

void print_number(int a) {
  printf("Result with %d = number is %d\n", a, a);
}

void print_square(int a) {
  printf("Result with %d = square is %d\n", a, a * a);
}

int cmp_by_value(const void *a, const void *b) {
    const Sensor *sa = a;
    const Sensor *sb = b;
    if (sa->value < sb->value) {
      return -1;
    }
    if (sa->value > sb->value) {
      return  1;
    }
    return 0;
}

int cmp_by_name(const void *a, const void *b) {
    const Sensor *sa = a;
    const Sensor *sb = b;
    return strcmp(sa->name, sb->name);
}

/*
не останавливается на '\0', сравнивает char (знаковый на x86) вместо unsigned char
int cmp_by_name(const void *a, const void *b) {
    const Sensor *sa = a;
    const Sensor *sb = b;
    for(size_t i = 0; i < sizeof(sa->name)/sizeof(sa->name[0]); i++) {
      if (sa->name[i] < sb->name[i]) {        
        return -1;
      }
      if (sa->name[i] > sb->name[i]) {
        return  1;
      }
    }
  return 0;
}
*/

void for_each_ctx(const int *arr, size_t n, Visitor visit, void *ctx) {
    for (size_t i = 0; i < n; i++) {
        visit(arr[i], ctx);
    }
}

static void count_above(int value, void *ctx) {
    CountCtx *c = ctx;
    if (value > c->threshold) c->count++;
}

int register_handler(EventType type, void (*h)(void)) {
  /* После unsigned conversion отрицательные значения становятся
   большими положительными и также попадают под проверку >= EVENT_COUNT. */
  if ((unsigned int) type >= EVENT_COUNT) {
    return -1;
  }
  handlers[type] = h;
  return 0;
}

void dispatch(EventType type) {
  printf("[dispatch] ");
  if ((unsigned int) type >= EVENT_COUNT) {
    printf("incorrect event type\n");
    return;
  }
  printf("%s -> ", event_names[type]);
  if (handlers[type] == NULL) {
    printf("event not registered\n");
    return;
  }
  handlers[type]();
}

static void on_button_short(void) {
  printf("on short button\n");
}
static void on_button_long(void) {
  printf("on long button\n");
}
static void on_timer(void) {
  printf("on timer\n");
}
