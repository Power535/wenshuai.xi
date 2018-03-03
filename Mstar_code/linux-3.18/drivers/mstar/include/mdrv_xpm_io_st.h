#ifndef _MDRV_XPM_IO_ST_H_
#define _MDRV_XPM_IO_ST_H_


typedef enum
{
	XPM_STATE_SUSPENDING		=0x01,
	XPM_STATE_SUSPENDED			=0x02,
	XPM_STATE_SUSPEND_ABORT		=0x04,
	XPM_STATE_WAKEUPED			=0x08,
	XPM_STATE_END			=0xFFFFFFFF
}EN_XPM_STATE;


typedef enum
{
	XPM_SOURCE_ACTIVE		=0x10,
	XPM_SOURCE_STANDBY		=0x20,
	XPM_SOURCE_STATUS_END=0xFFFFFFFF,
}EN_XPM_SOURCE_STATUS;

#endif