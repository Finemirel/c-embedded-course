#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define PINT int *

typedef int * TINT;
typedef unsigned char byte_t;
typedef unsigned int u32_t;
typedef struct {
  uint8_t id;
  float value;
} Sensor;
typedef struct Node {
  int value;
  struct Node *next;
} Node;
typedef int (*MathOp)(int, int);

void print_sensor(const Sensor *s);
void print_list(const Node *head);
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);

int main(void) {
  //#1
  byte_t bt = 'A';
  u32_t ut = 487391;
  size_t size_bt = sizeof(bt);
  printf("byte_t = %c and occupies %zu bytes!\n", bt, size_bt);
  printf("u32_t = %u and occupies %zu bytes!\n", ut, sizeof(ut));
  
  //#2
  Sensor sensors[3] = {{182, 34.16}, {14, 9.3}, {167, 17.0}};
  for(int i = 0; i < 3; i++) {
    print_sensor(&sensors[i]);
  }
  
  //#3
  Node n1, n2, n3;
  n1.value = 21;
  n2.value = 37;
  n3.value = 17;
  n1.next = &n2;
  n2.next = &n3;
  n3.next = NULL;
  print_list(&n1);
  
  //#4
  MathOp ops[3] = {add, sub, mul};
  const char * names[3] = {"add", "sub", "mul"};
  for(int i = 0; i < 3; i++) {
    printf("%d %s %d = %d\n", 12, names[i], 4, ops[i](12, 4));
  }
  
  //#5
  int x = 10;
  PINT p1, p2;
  TINT t1, t2;
  
  p1 = &x;
  t1 = &x;
  t2 = &x;
  /*warning: assignment to ‘int’ from ‘int *’ makes integer 
  from pointer without a cast [-Wint-conversion]
  p2 is not pointer. p2 is variable type int.
  */
  //p2 = &x;
  p2 = 0;
  printf("*p1 = %d, *t1 = %d, *t2 = %d, p2 = %d\n", *p1, *t1, *t2, p2);
  
  return 0;
}

// %" PRIu8 " -> uint8_t from <inttypes.h>
void print_sensor(const Sensor *s) {
  printf("Sensor id = %" PRIu8 " has value = %.2f\n", s->id, s->value);
}

void print_list(const Node *head) {
  int count = 1;
  while(head != NULL) {
    printf("Value from element №%d = %d\n",count, head->value);
    head = head->next;
    count += 1;
  }
}

int add(int a, int b) {
  return a+b;
}

int sub(int a, int b) {
  return a-b;
}

int mul(int a, int b) {
  return a*b;
}
