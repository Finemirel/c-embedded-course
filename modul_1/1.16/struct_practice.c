/*
1. Объяви структуру SensorRaw с полями строго в этом порядке: char id; int value; char status; double voltage;. Прежде чем запускать программу — посчитай на бумаге, какой будет sizeof и смещение каждого поля. Потом выведи реальные значения через sizeof и offsetof и сравни со своим расчётом. Расхождение — это и есть то, что нужно понять.

2. Объяви структуру SensorOptimized с теми же четырьмя полями тех же типов, но переставь их порядок так, чтобы sizeof получился минимально возможным. Выведи оба размера рядом.

3. Вложенность. Объяви Timestamp с полями uint8_t hour, minute, second и структуру Measurement, содержащую поле типа Timestamp, поле float value и поле uint16_t sensor_id. Заполни экземпляр значениями и выведи всё через цепочку точек. Для uint8_t и прочих нужен #include <stdint.h>.

4. Напиши две функции:

void shift_hour(Measurement *m, int delta) — прибавляет delta к часу через ->;
void shift_hour_broken(Measurement m, int delta) — то же самое, но параметр по значению.

Вызови обе на одном и том же экземпляре и выведи час после каждого вызова. Ты должен увидеть, что вторая функция ничего не изменила. Уточнение: shift_hour_broken компилируется и работает без ошибок — она просто меняет копию, которая умирает при выходе из функции.

5. Объяви MeasurementPacked — точную копию Measurement, но с __attribute__((packed)) после слова struct. Выведи sizeof обеих и объясни в комментарии в коде, откуда взялась разница.
*/
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct SensorRaw {
  char id;
  int value;
  char status;
  double voltage;
} SensorRaw;

typedef struct SensorOptimized {
  double voltage;
  int value;
  char id;
  char status;
} SensorOptimized;

typedef struct Timestamp {
  uint8_t hour;
  uint16_t minute;
  uint8_t second;
} Timestamp;

typedef struct __attribute__((packed)) TimestampPacked {
  uint8_t hour;
  uint16_t minute;
  uint8_t second;
} TimestampPacked;

typedef struct Measurement {
  Timestamp time;
  float value;
  uint16_t sensor_id;
} Measurement;

typedef struct __attribute__((packed)) MeasurementPacked {
  Timestamp time;
  float value;
  uint16_t sensor_id;
} MeasurementPacked;

typedef struct __attribute__((packed)) MeasurementPackedPacked {
  TimestampPacked time;
  float value;
  uint16_t sensor_id;
} MeasurementPackedPacked;

void shift_hour(Measurement *m, int delta);
void shift_hour_broken(Measurement m, int delta);
void measurement_print(Measurement *m);
void sep(void);

int main(void) {
  //#1
  printf("SensorRaw:\n");
  printf("  id      =   %zu\n", offsetof(SensorRaw, id));
  printf("  value   =   %zu\n", offsetof(SensorRaw, value));
  printf("  status  =   %zu\n", offsetof(SensorRaw, status));
  printf("  voltage =   %zu\n", offsetof(SensorRaw, voltage));
  printf("  sizeof  =   %zu\n", sizeof(SensorRaw));
  sep();
  
  //#2
  printf("SensorOptimized:\n");
  printf("  voltage =   %zu\n", offsetof(SensorOptimized, voltage));
  printf("  value   =   %zu\n", offsetof(SensorOptimized, value));
  printf("  id      =   %zu\n", offsetof(SensorOptimized, id));
  printf("  status  =   %zu\n", offsetof(SensorOptimized, status));
  printf("  sizeof  =   %zu\n", sizeof(SensorOptimized));  
  sep();
  
  //#3
  printf("Measurement:\n");
  sep();
  Measurement check_up;
    check_up.time.hour = 11;
    check_up.time.minute = 39;
    check_up.time.second = 15;
    check_up.value = 26.5;
    check_up.sensor_id = 12763;
    
  measurement_print(&check_up);
  sep();
  //#4
  shift_hour(&check_up, 2);
  measurement_print(&check_up);
  sep();
 
  shift_hour_broken(check_up, 2);
  measurement_print(&check_up);
  sep();
  
  printf("Sizeof Measurement =   %zu\n", sizeof(Measurement));
  sep();
  
  printf("Sizeof MeasurementPacked =   %zu\n", sizeof(MeasurementPacked));
  sep();
  
  printf("Sizeof MeasurementPackedPacked =   %zu\n", sizeof(MeasurementPackedPacked));
  sep();
  
  /* __attribute__((packed)) removes padding inside this struct only.
   Nested structs keep their own layout: MeasurementPacked is 12 bytes
   because Timestamp still holds 6, while MeasurementPackedPacked is 10.
   Cost: on Cortex-M0/M3 reading a misaligned float or uint32_t
   raises a HardFault. Use it for wire formats, not for working data. */
  
  return 0;
}

void shift_hour(Measurement * m, int delta) {
  m->time.hour += delta;
  printf("Time (hour) in shift_hour : %u\n", m->time.hour);
}

void shift_hour_broken(Measurement m, int delta) {
  m.time.hour += delta;
  printf("Time (hour) in shift_hour_broken : %u\n", m.time.hour);
}

void measurement_print(Measurement *m) {
  printf("In time checking next sensor we get next values:\n");
  printf("  time hh/mm/ss:  %u:%u:%u\n", m->time.hour, m->time.minute, m->time.second);
  printf("  from sensor id: %u\n", m->sensor_id);
  printf("  value is:       %.2f\n", m->value);
}

void sep(void) {
  printf("\n");
}
