#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

#include "gba_eeprom.h"

extern u8 EEPROM_V124[];

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

    iprintf("GBA EEPROM 64K Test\nhttps://github.com/laqieer/libgbabackup\n\n");

    if (EEPROMConfigure(64)) {
        iprintf("Error: invalid eeprom size!\nTest failed!");
    } else {
        u32 err = EEPROMWrite0_8k_Check(64, (u16*)EEPROM_V124);
        u8 s[9];
        switch (err) {
            case 0:
                EEPROMRead(64, (u16*)s);
                s[8] = '\0';
                iprintf("%s124\nTest passed!", s);
                break;

            case EEPROM_OUT_OF_RANGE:
                iprintf("Error: invalid eeprom address!\nTest failed!");
                break;

            case EEPROM_COMPARE_FAILED:
                iprintf("Error: verify error!\nTest failed!");
                break;

            case EEPROM_WRITE_TIMEOUT:
                iprintf("Error: writing timeout!\nTest failed!");
                break;

            case EEPROM_UNSUPPORTED_TYPE:
                iprintf("Error: unsupported 4K device!\nTest failed!");
                break;

            default:
                iprintf("Error code: 0x%lx!\nTest failed!", err);
                break;
        }
    }

	while (1) {
		VBlankIntrWait();
	}
}
