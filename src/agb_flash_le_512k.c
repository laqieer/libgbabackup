#include "flash_internal.h"
#include "io_reg.h"

const u16 le512kMaxTime[] =
{
      10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
      10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
      40, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
     200, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK,
};

const struct FlashSetupInfo DefaultFlash512K =
{
    ProgramFlashByte_LE,
    ProgramFlashSector_LE,
    EraseFlashChip_MX,
    EraseFlashSector_LE,
    WaitForFlashWrite512K_Common,
    le512kMaxTime,
    {
        65536, // ROM size
        {
            4096, // sector size
              12, // bit shift to multiply by sector size (4096 == 1 << 12)
              16, // number of sectors
               0  // appears to be unused
        },
        { 3, 3 }, // wait state setup data
        { { 0, 0 } } // ID
    }
};

const struct FlashSetupInfo LE39FW512 =
{
    ProgramFlashByte_LE,
    ProgramFlashSector_LE,
    EraseFlashChip_MX,
    EraseFlashSector_LE,
    WaitForFlashWrite512K_Common,
    le512kMaxTime,
    {
        65536, // ROM size
        {
            4096, // sector size
              12, // bit shift to multiply by sector size (4096 == 1 << 12)
              16, // number of sectors
               0  // appears to be unused
        },
        { 1, 2 }, // wait state setup data
        { { 0xBF, 0xD4 } } // ID
    }
};

u16 EraseFlashSector_LE(u16 sectorNum)
{
    u16 result;
    u8 *addr;
    u16 readFlash1Buffer[0x20];

    if (sectorNum >= gFlash->sector.count)
        return 0x80FF;

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | gFlash->wait[0];

    addr = FLASH_BASE + (sectorNum << gFlash->sector.shift);

    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0x80);
    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    *addr = 0x30;

    SetReadFlash1(readFlash1Buffer);

    result = WaitForFlashWrite(2, addr, 0xFF);

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | WAITCNT_SRAM_8;

    return result;
}

u16 ProgramFlashByte_LE(u16 sectorNum, u32 offset, u8 data)
{
    u8 *addr;
    u16 readFlash1Buffer[0x20];

    if (offset >= gFlash->sector.size)
        return 0x8000;

    addr = FLASH_BASE + (sectorNum << gFlash->sector.shift) + offset;

    SetReadFlash1(readFlash1Buffer);

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | gFlash->wait[0];

    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0xA0);
    *addr = data;

    return WaitForFlashWrite(1, addr, data);
}

u16 ProgramFlashSector_LE(u16 sectorNum, void *src)
{
    u16 result;
    u8 *dest;
    u16 readFlash1Buffer[0x20];

    if (sectorNum >= gFlash->sector.count)
        return 0x80FF;

    //TODO: erase verify routine transmit

    result = EraseFlashSector_LE(sectorNum);

    //TODO: erase retry

    if (result != 0)
        return result;

    SetReadFlash1(readFlash1Buffer);

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | gFlash->wait[0];

    gFlashNumRemainingBytes = gFlash->sector.size;
    dest = FLASH_BASE + (sectorNum << gFlash->sector.shift);

    while (gFlashNumRemainingBytes > 0)
    {
        result = ProgramByte(src, dest);

        if (result != 0)
            break;

        gFlashNumRemainingBytes--;
        src++;
        dest++;
    }

    return result;
}

