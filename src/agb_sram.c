#include "agb_sram.h"

static const char AgbLibSramVersion[] = "SRAM_V113";

void ReadSram_Core(const u8 *src, u8 *dest, u32 size)
{
    while (--size != -1)
        *dest++ = *src++;
}

void ReadSram(const u8 *src,u8 *dest,u32 size)
{
    u16 i,readSram_Core_Work[0x40],*pSrc,*pDest;
    void (*readSram_p)(const u8 *,u8 *,u32);

    REG_WAITCNT = (REG_WAITCNT & ~3) | 3;
    pSrc=(u16 *)ReadSram_Core;
    pSrc=(u16 *)((u32)pSrc & 0xFFFFFFFE);
    pDest=readSram_Core_Work;
    for(i=((u32)ReadSram-(u32)ReadSram_Core)>>1;i>0;i--)
        *pDest++=*pSrc++;
    readSram_p=(void (*)(const u8 *,u8 *,u32))((u8 *)readSram_Core_Work+1);

    readSram_p(src,dest,size);
}

void WriteSram(const u8 *src, u8 *dest, u32 size)
{
    REG_WAITCNT = (REG_WAITCNT & ~3) | 3;
    while (--size != -1)
        *dest++ = *src++;
}

u32 VerifySram_Core(const u8 *src, u8 *dest, u32 size)
{
    while (--size != -1)
    {
        if (*dest++ != *src++)
            return (u32)(dest - 1);
    }
    return 0;
}

u32 VerifySram(const u8 *src,u8 *dest,u32 size)
{
    u16 i,verifySram_Core_Work[0x60],*pSrc,*pDest;
    u32 (*verifySram_p)(const u8 *,u8 *,u32);

    REG_WAITCNT = (REG_WAITCNT & ~3) | 3;
    pSrc=(u16 *)VerifySram_Core;
    pSrc=(u16 *)((u32)pSrc & 0xFFFFFFFE);
    pDest=verifySram_Core_Work;
    for(i=((u32)VerifySram-(u32)VerifySram_Core)>>1;i>0;i--)
        *pDest++=*pSrc++;
    verifySram_p=(u32 (*)(const u8 *,u8 *,u32))((u8 *)verifySram_Core_Work+1);

    return verifySram_p(src,dest,size);
}

u32 WriteAndVerifySram(const u8 *src, u8 *dest, u32 size)
{
    u8 i;
    u32 errorAddr;

    // try writing and verifying the data 3 times
    for (i = 0; i < 3; i++)
    {
        WriteSram(src, dest, size);
        errorAddr = VerifySram(src, dest, size);
        if (errorAddr == 0)
            break;
    }

    return errorAddr;
}
