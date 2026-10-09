#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <signal.h>

static const int global_forbidden = 7;

void break_const(const int *p);
long delay_plain(long n);      // цикл с обычной переменной
long delay_volatile(long n);   // цикл с volatile-переменной

static volatile sig_atomic_t magnet_detected = 0;
static void on_sigint(int sig) { (void)sig; magnet_detected = 1; }

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

        //*p2 = 17; //error: assignment of read-only location ‘*p2’
        printf("*p2 = 17: %d\n", *p2);
        p2 = &b;
        printf("p2 = &b: %d\n", *p2);

        //*p3 = 17; //error: assignment of read-only location ‘*p3’
        printf("*p3 = 17: %d\n", *p3);
        p3 = &b;
        printf("p3 = &b: %d\n", *p3);

        //p4 = &b; //error: assignment of read-only variable ‘p4’
        printf("p4 = &b: %d\n", *p4);
        *p4 = 17;
        printf("*p4 = 17: %d\n", *p4);

        //p5 = &b; //error: assignment of read-only variable ‘p5’
        printf("p5 = &b: %d\n", *p5);
        //*p5 = 10; //error: assignment of read-only location ‘*(const int *)p5’
        printf("*p5 = 10: %d\n", *p5);

      break;
    }
    case 2: {
      printf("Part %ld\n", part);
      int legal = 1;
      printf("Before break_const: %d\n", legal);
      break_const(&legal);
      printf("After break_const: %d\n", legal);
      const int forbidden = 5;
      printf("Before break_const: %d\n", forbidden);
      printf("Print from pointer before : %d\n", *(const int *)&forbidden);
      break_const(&forbidden);
      printf("After break_const: %d\n", forbidden);
      printf("Print from pointer after : %d\n", *(const int *)&forbidden);

      printf("global_forbidden before break_const: %d\n", global_forbidden);
      printf("global_forbidden print from pointer before : %d\n", *(const int *)&global_forbidden);
      break_const(&global_forbidden);
      printf("global_forbidden after break_const: %d\n", global_forbidden);
      printf("global_forbidden print from pointer after : %d\n", *(const int *)&global_forbidden);
      break;
    }
    case 3: {
      printf("Part %ld\n", part);
      int choise = 5;                 /* = ESIZE, чтобы ветка реально сработала */
      const int SIZE = 8;
      enum { ESIZE = 5 };
      printf("Const int SIZE = %d\n", SIZE);
      /*static int a1[SIZE];
       error: storage size of ‘a1’ isn’t constant*/
      /*struct S { int buf[SIZE]; };
       warning: a member of a structure or union cannot have a variably modified type*/
      //int vla[SIZE]; //warning: ISO C90 forbids variable length array ‘vla’ [-Wvla]
      /* статический массив a1[SIZE] не проходит так как требует реальной
      константной переменной в качестве значения которое должно быть известно ещё на
      этапе компиляции, а vla этого не требует */
      //printf("%zu\n", sizeof vla);
      switch (choise) {
      /* case SIZE:
       -O0: error: case label does not reduce to an integer constant
       -O2: error: duplicate case value (SIZE свёрнут в литерал) */
      case ESIZE: {
        int a2[ESIZE];
        printf("sizeof(a2) = %zu\n", sizeof a2);
        break;
      }
      default:
        printf("default\n");
        break;
    }
      break;
    }
    case 4: {
      printf("Part %ld\n", part);
      clock_t start, end;
      double elapsed;
      long n = 500000000;
      start = clock();
      long r = delay_plain(n);
      /*delay_plain:
      .LFB31:
	      .cfi_startproc
	      endbr64
	      xorl	%eax, %eax
	      testq	%rdi, %rdi
	      cmovns	%rdi, %rax
	      ret
	      .cfi_endproc
      .LFE31:
	      .size	delay_plain, .-delay_plain
	      .p2align 4
	      .globl	delay_volatile
	      .type	delay_volatile, @function*/
      end = clock();
      elapsed = (double)(end - start) / CLOCKS_PER_SEC;
      printf("delay_plain: %.6f s (result = %ld)\n", elapsed, r);
      start = clock();
      r = delay_volatile(n);
      /*delay_volatile:
      .LFB32:
	      .cfi_startproc
	      endbr64
	      movq	$0, -8(%rsp)
	      movq	-8(%rsp), %rax
	      cmpq	%rax, %rdi
	      jle	.L25
	      .p2align 4,,10
	      .p2align 3
      .L26:
	      movq	-8(%rsp), %rax
	      addq	$1, %rax
	      movq	%rax, -8(%rsp)
	      movq	-8(%rsp), %rax
	      cmpq	%rdi, %rax
	      jl	.L26
      .L25:
	      movq	-8(%rsp), %rax
	      ret
	      .cfi_endproc
      .LFE32:
	      .size	delay_volatile, .-delay_volatile
	      .section	.rodata.cst8,"aM",@progbits,8
	      .align 8*/
      end = clock();
      elapsed = (double)(end - start) / CLOCKS_PER_SEC;
      printf("delay_volatile: %.6f s (result = %ld)\n", elapsed, r);
      break;
    }
    case 5: {
      printf("Part %ld\n", part);
      signal(SIGINT, on_sigint);
      puts("Жду магнит (Ctrl+C)...");
      while (!magnet_detected) { }
      puts("Магнит обнаружен!");
      break;
    }
    case 6: {
      printf("Part %ld\n", part);

      break;
    }
    default: {
        fprintf(stderr, "Unknown part: %ld\n", part);
        break;
    }
  }



    return 0;
}

void break_const(const int *p) {
  int *q = (int *)p; // cast away constness
  *q = 999;           // modify the value through the non-const pointer
}

long delay_plain(long n) {
  long i;
  for(i = 0; i < n; i++) { }
  return i;
}
long delay_volatile(long n) {
  volatile long i;
  for(i = 0; i < n; i++) { }
  return i;
}