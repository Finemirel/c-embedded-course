#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

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
        printf("Part %ld\n", part);
        int a = 10, b = 20;
        int *p1 = &a;               // обычный указатель: меняем всё
        const int *p2 = &a;         // указатель на const int
        int const *p3 = &a;         // то же самое, что p2 (порядок не важен)
        int * const p4 = &a;        // const-указатель на int
        const int * const p5 = &a;  // const-указатель на const int

        *p1 = 12;
        p1 = &b;
        printf("%d\n", a);
        printf("%d\n", *p1);

        // *p2 = 17; //error: assignment of read-only location ‘*p2’
        printf("%d\n", *p2);
        p2 = &b;
        printf("%d\n", *p2);

        //*p3 = 17; //printf("%d\n", *p2);
        printf("%d\n", *p3);
        p3 = &b;
        printf("%d\n", *p3);

        //p4 = &b; //error: assignment of read-only variable ‘p4’
        printf("%d\n", *p4);
        *p4 = 17;
        printf("%d\n", *p4);

        //p5 = &b; //error: assignment of read-only variable ‘p5’
        printf("%d\n", *p5);
        //*p5 = 10; //error: assignment of read-only location ‘*(const int *)p5’
        printf("%d\n", *p5);

      break;
    }
    case 2: {
      printf("Part %ld\n", part);

      break;
    }
    case 3: {
      printf("Part %ld\n", part);

      break;
    }
    case 4: {
      printf("Part %ld\n", part);

      break;
    }
    case 5: {
      printf("Part %ld\n", part);

      break;
    }
    case 6: {
      printf("Part %ld\n", part);

      break;
    }
    default:
        fprintf(stderr, "Unknown part: %ld\n", part);
        return 1;
    }




    return 0;
}