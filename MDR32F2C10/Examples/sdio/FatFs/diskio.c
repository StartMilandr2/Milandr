/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "sdio_sd.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = RES_OK;
#if 0
	int result;
	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_status();

		// translate the reslut code here

		return stat;
	return STA_NOINIT;
	}
#else
	if (SD_Detect() != SD_PRESENT)
		stat |= STA_NODISK;
	return stat;
#endif
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
#if 0
	int result;
	switch (pdrv) {
	case DEV_RAM :
		result = RAM_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
		result = MMC_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_initialize();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
#else
 	/* Supports only single drive */
	if (pdrv)
		{
		return STA_NOINIT;
		}
	/*-------------------------- SD Init ----------------------------- */
	stat = SD_Init();
	if (stat==SD_OK )
		{

		return RES_OK;
		}
//					puts("Initialization Fail");
return STA_NOINIT;		
#endif
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res  = RES_OK;
#if 0
	int result;
	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
	}
	return RES_PARERR;
#else
  SDTransferState state;
//  DRESULT res = RES_OK;
	SD_Error volatile errorstatus;

  if ( SD_Detect( ) != SD_PRESENT)
    return RES_NOTRDY;

  if ( count == 0)
    return RES_PARERR;

  //SD_ReadMultiBlocks ( buff, sector, 512, 1 );
  errorstatus = SD_ReadMultiBlocksFIXED ( buff, sector*512ULL, 512, count );
	if (errorstatus != SD_OK)
		return RES_ERROR;
  errorstatus = SD_WaitReadOperation ( );
	if (errorstatus != SD_OK)
		return RES_ERROR;

  while ( 1 )
  {
    state = SD_GetStatus ( );
    if ( state == SD_TRANSFER_OK )
      break;
  } // while
	return res;
#endif
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
#if 0
	DRESULT res;
	int result;
	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
	}
	return RES_PARERR;
#else
  SDTransferState state;
//  DRESULT res = RES_OK;
	volatile SD_Error errorstatus;

  if ( SD_Detect( ) != SD_PRESENT )
    return RES_NOTRDY;

  if ( count == 0)
    return RES_PARERR;


  //SD_WriteMultiBlocks ( (uint8_t *)buff, sector, 512, count );
  errorstatus = SD_WriteMultiBlocksFIXED ( (uint8_t *)buff, sector*512ULL, 512, count );
	if (errorstatus != SD_OK)
		return RES_ERROR;
  errorstatus = SD_WaitWriteOperation ( );
	if (errorstatus != SD_OK)
		return RES_ERROR;

  while ( 1 )
  {
    state = SD_GetStatus ( );
    if ( state == SD_TRANSFER_OK )
      break;
  } // while

  return RES_OK;
	
#endif
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
}

