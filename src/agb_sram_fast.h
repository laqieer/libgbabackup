#ifndef GUARD_AGB_SRAM_FAST_H
#define GUARD_AGB_SRAM_FAST_H

#include "types.h"
#include "io_reg.h"

void SetSramFastFunc(void);
void WriteSramFast(const u8 *src, u8 *dest, u32 size);
extern void (*ReadSramFast)(const u8 *src, u8 *dest, u32 size);
extern u32 (*VerifySramFast)(const u8 *src, u8 *dest, u32 size);
u32 WriteAndVerifySramFast(const u8 *src, u8 *dest, u32 size);

#endif  // GUARD_AGB_SRAM_FAST_H
