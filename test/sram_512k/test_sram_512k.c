#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gba_sram.h"

extern const u8 gAgbSramLibVer[];

const u8 mask[] = "E008000h is mirrored to E000000h";

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

    iprintf("GBA SRAM 512K Test\nhttps://github.com/laqieer/libgbabackup\n\n");

    u32 errorAdr = WriteSramEx(gAgbSramLibVer, (u8*)(SRAM+0x8000), 20);

    if (errorAdr) {
        iprintf("Error when writing to address: 0x%lx\nTest failed!", errorAdr);
    } else {
        errorAdr = WriteSramEx(mask, (u8*)SRAM, 20);
        if (errorAdr) {
            iprintf("Error when writing to address: 0x%lx\nTest failed!", errorAdr);
        } else {
            u8 s[20];
            ReadSram((const u8*)(SRAM+0x8000), s, 20);
            if (strcmp((char*)s, (char*)gAgbSramLibVer) == 0) {
                iprintf("%s\nTest passed!", s);
            } else {
                iprintf("%s\nTest failed!", s);
            }
        }
    }

	while (1) {
		VBlankIntrWait();
	}
}
