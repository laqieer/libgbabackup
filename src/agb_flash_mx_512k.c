#include "flash_internal.h"
#include "io_reg.h"

const u16 mx512kMaxTime[] =
{
      10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
      10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
    2000, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
    2000, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
};

const u16 paMaxTime[] =
{
      10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
      10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
     500, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
     500, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
};

const struct FlashSetupInfo MX29L512 =
{
    ProgramFlashByte_LE,
    ProgramFlashSector_LE,
    EraseFlashChip_MX,
    EraseFlashSector_LE,
    WaitForFlashWrite512K_Common,
    mx512kMaxTime,
    {
        65536, // ROM size
        {
            4096, // sector size
              12, // bit shift to multiply by sector size (4096 == 1 << 12)
              16, // number of sectors
               0  // appears to be unused
        },
        { 3, 1 }, // wait state setup data
        { { 0xC2, 0x1C } } // ID
    }
};

const struct FlashSetupInfo MN63F805MNP =
{
    ProgramFlashByte_LE,
    ProgramFlashSector_LE,
    EraseFlashChip_MX,
    EraseFlashSector_LE,
    WaitForFlashWrite512K_Common,
    mx512kMaxTime,
    {
        65536, // ROM size
        {
            4096, // sector size
              12, // bit shift to multiply by sector size (4096 == 1 << 12)
              16, // number of sectors
               0  // appears to be unused
        },
        { 0, 2 }, // wait state setup data
        { { 0x32, 0x1B } } // ID
    }
};

