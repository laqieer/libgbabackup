#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

#include "gba_flash_1m.h"

extern u8 AgbLibFlash1MVersion[];

void (**gFlashTimerIntrFunc)(void) = NULL;

void InitFlashTimer(void)
{
    SetFlashTimerIntr(2, gFlashTimerIntrFunc);
}

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------


	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);

	consoleDemoInit();

    iprintf("GBA FLASH 1M Test\nhttps://github.com/laqieer/libgbabackup\n\n");

    if (IdentifyFlash()) {
        iprintf("Error: unsupported device!\nTest failed!");
    } else {
        InitFlashTimer();
        u32 err = ProgramFlashSectorAndVerifyNBytes(16, AgbLibFlash1MVersion, 20);
        u8 s[20];
        switch (err) {
            case 0:
                ReadFlash(16, 0, s, 20);
                iprintf("%s\nTest passed!", s);
                break;

            case 0x80ff:
                iprintf("Error: invalid sectorNum!\nTest failed!");
                break;

            case 0x8004:
                iprintf("Error: sector erase verify error with Sanyo's device!\nTest failed!");
                break;

            case 0xc002:
                iprintf("Error: sector erase timeout!\nTest failed!");
                break;

            case 0xc001:
                iprintf("Error: writing timeout!\nTest failed!");
                break;

            default:
                iprintf("Error when writing to address: 0x%lx!\nTest failed!", err);
                break;
        }
    }

	while (1) {
		VBlankIntrWait();
	}
}
