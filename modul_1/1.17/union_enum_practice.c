#include <stdio.h>
#include <stdint.h>

typedef union FloatBytes {
  float f;
  uint32_t raw;
  uint8_t bytes[4];
} FloatBytes;

typedef union EndianTest {
  uint16_t value;
  uint8_t b[2];
} EndianTest;

typedef enum SensorState {
  SENSOR_IDLE,
  SENSOR_MEASURING,
  SENSOR_READY,
  SENSOR_ERROR
} SensorState;

typedef enum ErrorCode {
  ERR_NONE = 0,
  ERR_TIMEOUT = 10,
  ERR_CRC,
  ERR_OVERFLOW
} ErrorCode;

typedef enum PacketType {
  PKT_TEMPERATURE,
  PKT_HALL,
  PKT_STATUS
} PacketType;

typedef struct Packet {
  PacketType type;
  union {
    float temperature;
    uint16_t hall_raw;
    struct {
      uint8_t state;
      uint8_t errors;
    } status;
  } payload;  
} Packet;

const char *state_name(enum SensorState s);
void print_packet(const struct Packet * p);

int main(void) {
  //#1
  printf("%zu\n", sizeof(FloatBytes));
  FloatBytes fb;
  fb.f = 1.0f;
  printf("%08X\n", fb.raw);
  for(int i = 0; i < (int)(sizeof(fb.bytes)/sizeof(fb.bytes[0])); i++) {
    printf("%02X", fb.bytes[i]);
  }
  printf("\n");
  printf("%p %p %p %p\n",
       (void *)&fb.bytes[0], (void *)&fb.bytes[1],
       (void *)&fb.bytes[2], (void *)&fb.bytes[3]);
  /*The bytes are output in reverse order because I am using a little-endian machine,
  where memory is read starting from the least significant end.*/
    
  //#2
  EndianTest et;
  et.value = 0x1234;
  if(et.b[0] == 0x34) {
    printf("little-endian\n");
  } else if(et.b[0] == 0x12) {
    printf("big-endian\n");
  } else {
    printf("unknown\n");
  }
  
  //#3
  printf("ErrorCode ERR_NONE = %d \n", ERR_NONE);
  printf("ErrorCode ERR_TIMEOUT = %d \n", ERR_TIMEOUT);
  printf("ErrorCode ERR_CRC = %d \n", ERR_CRC);
  printf("ErrorCode ERR_OVERFLOW = %d \n", ERR_OVERFLOW);
  
  for(int i = 0; i < 4; i++) {
    printf("%s\n", state_name((SensorState) i));
  }
  
  //#4
  Packet packet[3];
  packet[0].type = PKT_TEMPERATURE;
  packet[0].payload.temperature = 23.5f;
  
  packet[1].type = PKT_HALL;
  packet[1].payload.hall_raw = 512;
  
  packet[2].type = PKT_STATUS;
  packet[2].payload.status.state = 2;
  packet[2].payload.status.errors = 0;
  
  for(int i = 0; i < 3; i++) {
    print_packet(&packet[i]);
  }
  
  printf("%zu\n", sizeof(Packet));
  /*
  `type` occupies 4 bytes at offset 0. The `union` takes up 4 bytes 
  (based on its largest field, `float`) and requires 4-byte alignment,
  so it is placed at offset 4 without any padding. 
  The alignment of the entire structure is 4; 
  the total size of 8 is a multiple of 4, 
  so no trailing padding is needed.
  */
  
  //#5
  FloatBytes fb_two;
  fb_two.raw = 0x00000001;
  printf("FloatBytes.f = %.20f\n", fb_two.f);
  printf("%e\n", fb_two.f);
  printf("%a\n", fb_two.f);
  /*
    FloatBytes.f = 0.00000000000000000000
    The first significant digit is at the 45th position 
    after the decimal point. %.20f prints only twenty.
    the bits yield a denormalized number 2⁻¹⁴⁹ ≈ 1.4e-45; 
    twenty decimal places are not enough to see it.
  */
  
  return 0;
}

//warning: enumeration value ‘SENSOR_MEASURING’ not handled in switch [-Wswitch]
const char * state_name(enum SensorState s) {
  switch(s) {
    case SENSOR_IDLE:
      return "SENSOR_IDLE";
    case SENSOR_MEASURING:
      return "SENSOR_MEASURING";
    case SENSOR_READY:
      return "SENSOR_READY";
    case SENSOR_ERROR:
      return "SENSOR_ERROR";
  }
  return "UNKNOWN";
}



void print_packet(const struct Packet * p) {
   switch(p -> type) {
    case PKT_TEMPERATURE:
      printf("PKT_TEMPERATURE = %.2f\n", p -> payload.temperature);
      break;
    case PKT_HALL:
      printf("PKT_HALL = %d\n", p -> payload.hall_raw);
      break;
    case PKT_STATUS:
      printf("PKT_STATUS:\n");
      printf("  state   =  %d\n", p -> payload.status.state);
      printf("  errors  =  %d\n", p -> payload.status.errors);
      break;
  }
}
