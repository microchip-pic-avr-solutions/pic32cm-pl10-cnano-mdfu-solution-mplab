#include <stdint.h>

extern volatile const uint32_t crcStart;

volatile const uint32_t __attribute__((used, section("crc_foot_start_address"), space(prog), address(0xC00FFFC))) crcStart = 0xFFFFFFFF;