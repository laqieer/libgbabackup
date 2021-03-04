//---------------------------------------------------------------------------------
#ifndef _gba_eeprom_h_
#define _gba_eeprom_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// error codes
#define EEPROM_OUT_OF_RANGE 0x80ff
#define EEPROM_COMPARE_FAILED 0x8000
#define EEPROM_UNSUPPORTED_TYPE 0x8080
#define EEPROM_WRITE_TIMEOUT 0xc001

/**
 * selects EEPROM type
 * selects 512byte on invalid argument
 *
 * @param sizeInKbit 4 for 512 byte, 0x40 for 8k
 * @return 1 on invalid argument, 0 otherwise
 */
u16 EEPROMConfigure(u16 sizeInKbit);

u16 EEPROMRead(u16 address, u16* data);
u16 EEPROMCompare(u16 address, const u16* data);

u16 EEPROMWrite1(u16 address, const u16* data);
u16 EEPROMWrite1_check(u16 address, const u16* data);

// 8KB EEPROM only!
u16 EEPROMWrite0_8k(u16 address, const u16* data);
u16 EEPROMWrite0_8k_Check(u16 address, const u16* data);

//---------------------------------------------------------------------------------
#ifdef __cplusplus
}      // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_eeprom_h_
//---------------------------------------------------------------------------------
