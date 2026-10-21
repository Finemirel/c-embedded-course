#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static uint32_t GPIOC_ODR = 0x00A5;
static const int8_t LED_PIN = 13;
static uint32_t GPIOC_CRH = 0x44444444;

void print_bin(uint32_t v, int8_t bits);

void pin_set(uint32_t * reg, int8_t pin);
void pin_reset(uint32_t * reg, int8_t pin);
void pin_toggle(uint32_t * reg, int8_t pin);
int8_t pin_read(uint32_t * reg, int8_t pin);
void led_on(uint32_t * reg);
void led_off(uint32_t * reg);
void led_blink(uint32_t * reg, uint32_t times);
void print_status_led();

void field_write(uint32_t *reg, unsigned shift, unsigned width, uint32_t value);
uint32_t field_read(uint32_t reg, unsigned shift, unsigned width);

int main(int argc, char * argv[]) {
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
      print_bin(0x00A5, 16);
      print_bin(0x2000, 16);
      break;
    }
    case 2: {
      printf("Part %ld\n", part);
      print_bin(GPIOC_ODR, 16);
      print_status_led();
      pin_set(&GPIOC_ODR, LED_PIN);
      print_bin(GPIOC_ODR, 16);
      pin_reset(&GPIOC_ODR, LED_PIN);
      print_bin(GPIOC_ODR, 16);
      pin_toggle(&GPIOC_ODR, LED_PIN);
      print_bin(GPIOC_ODR, 16);
      print_status_led();
      print_bin(GPIOC_ODR, 16);
      led_blink(&GPIOC_ODR, 6);
      print_bin(GPIOC_ODR, 16);
      break;
    }
    case 3: {
      printf("Part %ld\n", part);
      print_bin(GPIOC_CRH, 32);
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
    default: {
      fprintf(stderr, "Unknown part: %ld\n", part);
      break;
    }
  }

    return 0;
}

void print_bin(uint32_t v, int8_t bits) {
  if(bits > 32 || bits < 1) {
    printf("Size not correct\n");
    return;
  }
  int8_t count = bits%4;
  for (int8_t i = bits - 1; i >= 0; i--) {
    printf("%b", (v >> i)&0x1u);
    count++;
    if(count == 4) {
      printf(" ");
      count = 0;
    }
  }
  printf("\n");
}

void pin_set(uint32_t * reg, int8_t pin) {
  *reg = *reg | (1u << pin);
}

void pin_reset(uint32_t * reg, int8_t pin) {
  *reg &= ~(1u << pin);
}

void pin_toggle(uint32_t * reg, int8_t pin) {
  *reg = *reg ^ (1u << pin);
}

int8_t pin_read(uint32_t * reg, int8_t pin) {
  int8_t result = 0;
  if((*reg & (1u << pin)) > 0) {
    result = 1;
  }
  return result;
}

void led_on(uint32_t * reg) {
  pin_reset(reg, LED_PIN);
  puts("Led is on!");
}

void led_off(uint32_t * reg) {
  pin_set(reg, LED_PIN);
  puts("Led is off!");
}

void led_blink(uint32_t * reg, uint32_t times) {
  for(uint32_t i = 0; i < times; i++) {
    led_on(reg);
    print_bin(GPIOC_ODR, 16);
    led_off(reg);
    print_bin(GPIOC_ODR, 16);
  }
}

void print_status_led() {
  int8_t result = pin_read(&GPIOC_ODR, LED_PIN);
  if(result == 1) {
    puts("LED IS OFF");
  } else {
    puts("LED IS ON");
  }
}
