#ifndef GUARD_AGB_SRAM_H
#define GUARD_AGB_SRAM_H

#include "types.h"
#include "io_reg.h"

void WriteSram(const u8 *src, u8 *dest, u32 size);
void ReadSram(const u8 *src, u8 *dest, u32 size);
u32 VerifySram(const u8 *src, u8 *dest, u32 size);
u32 WriteAndVerifySram(const u8 *src, u8 *dest, u32 size);

#endif  // GUARD_AGB_SRAM_H
