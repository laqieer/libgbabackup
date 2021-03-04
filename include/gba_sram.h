//---------------------------------------------------------------------------------
#ifndef _gba_sram_h_
#define _gba_sram_h_
//---------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------*/
/*          Read Data                                               */
/*------------------------------------------------------------------*/

extern void ReadSram(const u8 *src,u8 *dst,u32 size) ;

/*   From the SRAM address specified by the argument, read "size"
     byte of data to area starting from "dst" address in Work.
     <Arguments>
      const u8 *src  : Read source SRAM address (Address on AGB memory map)
      u8 *dst        : Address of work area where read data is stored
                       (Address on AGB memory map)
      u32 size       : Read size in bytes
     <Return Values>
      None
*/


/*------------------------------------------------------------------*/
/*          Write Data                                              */
/*------------------------------------------------------------------*/

extern void WriteSram(const u8 *src,u8 *dst,u32 size) ;

/*   From the work area address specified by the argument, write "size"
     byte data to area starting from 'dst' address in SRAM.
     <Arguments>
      const u8 *src  : Write source work area address
      u8 *dst        : Write destination SRAM address
                       (Address on AGB memory map)
      u32 size       : Write size in bytes
     <Return Values>
      None
*/


/*------------------------------------------------------------------*/
/*          Verify Data                                             */
/*------------------------------------------------------------------*/

extern u32 VerifySram(const u8 *src,u8 *tgt,u32 size) ;

/*   Verify "size" byte of data from "src" address in the work area
     and "tgt" address in SRAM.
     If verify ends normally this function returns 0, if a verify error
     occurs and the address where the error occurred is returned.
     <Arguments>
      const u8 *src  : Pointer to verify source work area address (original data)
      u8 *tgt        : Pointer to verify target SRAM address
                      (write destination data, address on AGB memory map)
      u32 size       : Verify size in bytes
     <Return Values>
      u32 errorAdr   : Normal end => 0
                       Verify error => Error address on device side
*/


/*------------------------------------------------------------------*/
/*          Write data & Verify                                     */
/*------------------------------------------------------------------*/

extern u32 WriteSramEx(const u8 *src, u8 *dst, u32 size) ;

/*  This function writes internally using WriteSram and then verifies using VerifySram.
    In case of an error, it retries a maximum of SRAM_RETRY_MAX times (defined by AgbSram.h).

    <Argument>
     const u8 *src  : Work area address of write source
     u8 *dst        : SRAM address of write destination (address on AGB memory map)
     u32 size       : Write size in number of bytes
    <Return value>
     u32 errorAdr   : Normal end => 0
                      Verify error => Error address on device side
*/


//---------------------------------------------------------------------------------
#ifdef __cplusplus
}      // extern "C"
#endif
//---------------------------------------------------------------------------------
#endif // _gba_sram_h_
//---------------------------------------------------------------------------------
