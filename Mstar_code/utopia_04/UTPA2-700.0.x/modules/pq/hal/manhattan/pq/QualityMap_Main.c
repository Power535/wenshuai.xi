////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define PQTABLE_NAME    MAIN                // table config parameter
#if !defined(MSOS_TYPE_LINUX_KERNEL)
#include <pthread.h>
#endif

#include "MsTypes.h"
#include "drvXC_IOPort.h"
#include "apiXC.h"

#include "color_reg.h"
#include "drvPQ_Define.h"
#include "drvPQ_Declare.h"
#include "drvPQ.h"
#include "hwreg_utility2.h"

#define PQTBL_REGTYPE       PQTBL_NORMAL    // table config parameter

#include "Manhattan_Main.c"                  // table config parameter
#include "Manhattan_Main_1920.c"             // table config parameter
#include "Manhattan_Main_1920_PIP.c"         // table config parameter
#include "Manhattan_Main_1920_POP.c"         // table config parameter
#include "Manhattan_Main_1366.c"             // table config parameter
#include "Manhattan_Main_1366_PIP.c"         // table config parameter
#include "Manhattan_Main_1366_POP.c"         // table config parameter
#include "Manhattan_Main_4K2K.c"             // table config parameter
#include "Manhattan_Main_4K2K_PIP.c"         // table config parameter
#include "Manhattan_Main_4K2K_POP.c"         // table config parameter
#include "Manhattan_Main_HSDRule.c"          // table config parameter
#include "Manhattan_Main_VSDRule.c"          // table config parameter
#include "Manhattan_Main_HSPRule.c"          // table config parameter
#include "Manhattan_Main_VSPRule.c"          // table config parameter
#include "Manhattan_Main_CSCRule.c"          // table config parameter
#include "Manhattan_Main_GRule.c"            // table config parameter
#include "Manhattan_Main_1920_GRule.c"       // table config parameter
#include "Manhattan_Main_1920_PIP_GRule.c"   // table config parameter
#include "Manhattan_Main_1920_POP_GRule.c"   // table config parameter
#include "Manhattan_Main_1366_GRule.c"       // table config parameter
#include "Manhattan_Main_1366_PIP_GRule.c"   // table config parameter
#include "Manhattan_Main_1366_POP_GRule.c"   // table config parameter
#include "Manhattan_Main_4K2K_GRule.c"       // table config parameter
#include "Manhattan_Main_4K2K_PIP_GRule.c"   // table config parameter
#include "Manhattan_Main_4K2K_POP_GRule.c"   // table config parameter

#include "QualityMode.h"
#include "drvPQ_Datatypes.h"
#include "mhal_pq.h"
#include "drvPQ_Template.h"
