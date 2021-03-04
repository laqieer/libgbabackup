#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

#include "gba_sram_fast.h"

extern const u8 AgbLibSramFastVersion[];

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

    iprintf("GBA SRAM Fast Test\nhttps://github.com/laqieer/libgbabackup\n\n");

    SetSramFastFunc();

    u32 errorAdr = WriteAndVerifySramFast(AgbLibSramFastVersion, (u8*)SRAM, 20);

    if (errorAdr) {
        iprintf("Error when writing to address: 0x%lx\nTest failed!", errorAdr);
    } else {
        u8 s[20];
        (*ReadSramFast)((const u8*)SRAM, s, 20);
        iprintf("%s\nTest passed!", s);
    }

	while (1) {
		VBlankIntrWait();
	}
}
