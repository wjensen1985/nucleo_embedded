#include "common-defines.h"
#include <libopencm3/stm32/memorymap.h>
#include <libopencm3/cm3/vector.h>

// flash program memory 512KiB: 0x0800_0000 -> 0x0887_FFFF
// bootloader (32KiB): 0x0800_0000 -> 0x0800_7FFF
// main (480KiB): 0x0800_8000 -> 0x0887_FFFF

#define BOOTLOADER_SIZE     (0x8000U)
#define MAIN_START_ADDRESS  (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_firmware_main(void){
  // first entry after stack pointer is main + 4U (step size of uint32 ptr/array)
  vector_table_t* main_vector_table = (vector_table_t*)MAIN_START_ADDRESS;
  // start executing (as func.) at this new location
  main_vector_table->reset();
}

// test of file to big compilation error
// const uint8_t data[0x8000] = {0};

int main(void){

// test of file to big compilation error
  // volatile uint8_t x = 0;
  // for(uint32_t i=0; i<0x8000; i++){
  //   x += data[i];
  // }

  jump_to_firmware_main();

  // never return
  return 0;
}