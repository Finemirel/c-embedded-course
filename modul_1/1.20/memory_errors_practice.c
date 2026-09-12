#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static size_t g_alloc_count = 0;
static size_t g_free_count  = 0;

/*макрос, подставляющий параметр больше одного раза, 
вызывают только с простыми именами переменных*/
#define SAFE_FREE(p) do { free(p); (p) = NULL; } while (0)

void demo_leak(void);
int * make_broken(void);
void demo_uaf(void);
void demo_double_free(void);

/*If the returned value is non-zero, 
errors occurred during allocation.*/
int build_three(size_t n);

void *tracked_malloc(size_t size);
void tracked_free(void *p);
void memory_report(void);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <part 1-5>\n", argv[0]);
        return 1;
    }
    char *end;
    long part = strtol(argv[1], &end, 10);
    if (*end != '\0') {
        fprintf(stderr, "First argument not a number: %s\n", argv[1]);
        return 1;
    }

    switch (part) {
    case 1:
      demo_leak();
      break;
    case 2:
      demo_uaf();
      break;
    case 3:
      demo_double_free();
      printf("Program not dead\n");
      break;
    case 4: {
      if (argc < 3) {
        fprintf(stderr, "Usage: %s <part 1-5> and <size>\n", argv[0]);
        return 1;
      }
      size_t size = 0;
      long input = strtol(argv[2], &end, 10);
      if (*end != '\0') {
        fprintf(stderr, "Second argument not a number: %s\n", argv[2]);
        return 1;
      }
      if(input >= 0) {
        size = input;
      } else {
        printf("Second argument is not correct\n");     
      }
      int status = build_three(size);
      if(status != 0) {
        printf("fell under an exception\n");
      }
      break;
    }
    case 5: {
      int *ap = tracked_malloc(10);
      int *bp = tracked_malloc(10);
      int *cp = tracked_malloc(10);
      printf("Adres cp = %p\n", (void *)cp);
      tracked_free(ap);
      tracked_free(bp);
      memory_report();
      break;
    }
    default:
        fprintf(stderr, "Unknown part: %ld\n", part);
        return 1;
    }
  
  return 0;
}

void demo_leak(void) {
  uint8_t * number[10];
  for(int i = 0; i < 10; i++) {
    number[i] = malloc(64 * sizeof *number[i]);
    number[i][0] = 17;
  }
  printf("The end\n");
}

int * make_broken(void) {
  int *p = malloc(sizeof *p);
  if(p==NULL) {
    fprintf(stderr, "malloc failed\n");
    return NULL;
  }
  *p = 42;
  //free(p);
  return p;
}

void demo_uaf(void) {
  int *p = make_broken();
  int *q = p;
  printf("p = %p, q = %p\n", (void *)p, (void *)q);
  printf("*p = %d\n", *p);
  printf("*q = %d\n", *q);
}

void demo_double_free(void) {
  int *blok = malloc(sizeof *blok);
  *blok = 77;
  printf("My blok = %d\n", *blok);
  SAFE_FREE(blok);
  free(blok);
 // free(blok);
}

int build_three(size_t n) {
  int status = 0;
  char *a = NULL;
  char *b = NULL;
  char *c = NULL;
 
  a = malloc(n * sizeof *a);
  if (a == NULL) {
    status = -1;
    goto cleanup;
  }
  if (n == 0) {
    status = -1;
    goto cleanup;
  }
  b = malloc(n * sizeof *b);
  if (b == NULL) {
    status = -1;
    goto cleanup;
  }
  c = malloc(n * sizeof *c);
  if (c == NULL) {
    status = -1;
    goto cleanup;
  }
  printf("All allocations succeeded\n");

  cleanup:
    free(c);
    free(b);
    free(a);

  return status;
}

void * tracked_malloc(size_t size) {
  void * a = malloc(size);
  if(a == NULL) {
    return NULL;
  }
  g_alloc_count += 1;
  return a;
}

void tracked_free(void *p) {
  if(p != NULL) {
    g_free_count += 1;
    free(p);
  }
}

void memory_report(void) {
  printf("g_alloc_count = %zu\n", g_alloc_count);
  printf("g_free_count = %zu\n", g_free_count);
  printf("g_alloc_count - g_free_count = %zu\n", g_alloc_count - g_free_count);
}










