//---------------------------------------------------------------------------------
#ifndef _gba_flash_1m_h_
#define _gba_flash_1m_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

#define IdentifyFlash IdentifyFlash1M

// Called once at first.
u16 IdentifyFlash(void);

u16 SetFlashTimerIntr(u8 timerNum, void (**intrFunc)(void));

void ReadFlash(u16 sectorNum, u32 offset, void *dest, u32 size);

u32 VerifyFlashSector(u16 sectorNum, u8 *src);

u32 VerifyFlashSectorNBytes(u16 sectorNum, u8 *src, u32 n);

extern u16 (*EraseFlashChip)(void);

extern u16 (*EraseFlashSector)(u16 sectorNum);

extern u16 (*ProgramFlashSector)(u16 sectorNum, void *src);

u32 ProgramFlashSectorAndVerify(u16 sectorNum, u8 *src);

u32 ProgramFlashSectorAndVerifyNBytes(u16 sectorNum, void *dataSrc, u32 n);

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}      // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_flash_1m_h_
//---------------------------------------------------------------------------------
