#include "common-defines.h"
#include <libopencm3/stm32/memorymap.h>

// flash program memory 512KiB: 0x0800_0000 -> 0x0887_FFFF
// bootloader (32KiB): 0x0800_0000 -> 0x0800_7FFF
// main (480KiB): 0x0800_8000 -> 0x0887_FFFF

#define BOOTLOADER_SIZE     (0x8000U)
#define MAIN_START_ADDRESS  (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_main(void){
  typedef void (*void_fn)(void);

  // first entry after stack pointer is main + 4U
  uint32_t* reset_vector_entry = (uint32_t*)(MAIN_START_ADDRESS + 4U);
  uint32_t* reset_vector = (uint32_t*)(*reset_vector_entry);

  // start executing (as func.) at this new location
  void_fn jump_fn = (void_fn)reset_vector;
  jump_fn();
}

// test of file to big compilation error
// const uint8_t data[0x8000] = {0};

int main(void){

// test of file to big compilation error
  // volatile uint8_t x = 0;
  // for(uint32_t i=0; i<0x8000; i++){
  //   x += data[i];
  // }

  jump_to_main();

  // never return
  return 0;
}