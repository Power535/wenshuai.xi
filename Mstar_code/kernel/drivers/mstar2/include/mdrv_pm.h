///////////////////////////////////////////////////////////////////////////////////////////////////
//
// * Copyright (c) 2006 - 2007 MStar Semiconductor, Inc.
// This program is free software.
// You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;
// either version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   Mdrv_mtlb.h
/// @brief  MTLB Driver Interface
/// @author MStar Semiconductor Inc.
///
///////////////////////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Linux Mhal_mtlb.h define start
// -----------------------------------------------------------------------------
#ifndef __DRV_PM_H__
#define __DRV_PM_H__

//-------------------------------------------------------------------------------------------------
//  Structure and Enum
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_PM_FAIL       = 0,      // fail
    E_PM_OK         = 1,      // success
    E_PM_TIMEOUT    = 2,      // timeout

} PM_Result;

typedef struct _MSTAR_PM_DEV{
    unsigned long flag;
}MSTAR_PM_DEV;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

PM_Result MDrv_PM_CopyBin2Sram(void);
PM_Result MDrv_PM_SetSRAMOffsetForMCU(void);
void MDrv_SetDram(u32 u32Addr, u32 u32Size);
void MDrv_SetData(u32 u32Addr, u32 u32Size);

#endif

