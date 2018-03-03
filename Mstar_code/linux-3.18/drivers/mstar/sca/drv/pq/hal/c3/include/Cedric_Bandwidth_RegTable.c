////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (; MStar; Confidential; Information; ) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//


//****************************************************
// DDR1300MHz
//****************************************************
code U8 BWTABLE_COM[][REG_ADDR_SIZE+REG_BANK_SIZE+REG_MASK_SIZE+1] =
{//Reg          Bank  Mask  Value
 { REG(0x1F33), 0x00, 0x07, 0x07 },
 { REG(0x1F33), 0x00, 0xC0, 0xC0 },
 { REG(0x1F32), 0x00, 0xFF, 0xF0 },
 { REG(0x1F33), 0x03, 0x07, 0x04 },
 { REG(0x1F33), 0x03, 0xC0, 0xC0 },
 { REG(0x1F32), 0x03, 0xFF, 0xF0 },
 { REG(0x1F33), 0x07, 0x07, 0x07 },
 { REG(0x1F33), 0x07, 0xC0, 0xC0 },
 { REG(0x1F32), 0x07, 0xFF, 0xF0 },
 { REG(0x1F33), 0x0A, 0x07, 0x04 },
 { REG(0x1F33), 0x0A, 0xC0, 0xC0 },
 { REG(0x1F32), 0x0A, 0xFF, 0xF0 },
 { REG(0x1429), 0xFF, 0x7F, 0x24 },//Same mark
 { REG(0x1428), 0xFF, 0x1F, 0x10 },
 { REG(0x1240), 0xFF, 0xFF, 0x14 },
 { REG(0x1241), 0xFF, 0xFF, 0x80 },
 { REG(0x1243), 0xFF, 0xFF, 0x00 },
 { REG(0x1244), 0xFF, 0xFF, 0x00 },
 { REG(0x1245), 0xFF, 0xFF, 0x04 },
 { REG(0x1248), 0xFF, 0xFF, 0xFF },
 { REG(0x1249), 0xFF, 0xFF, 0xCF },
 { REG(0x124A), 0xFF, 0xFF, 0x10 },//Same mark
 { REG(0x124B), 0xFF, 0xFF, 0x32 },//Same mark
 { REG(0x124C), 0xFF, 0xFF, 0x54 },//Same mark
 { REG(0x124D), 0xFF, 0xFF, 0x76 },//Same mark
 { REG(0x124F), 0xFF, 0xFF, 0xBA },//Same mark
 { REG(0x1251), 0xFF, 0xFF, 0xFE },//Same mark
 { REG(0x1260), 0xFF, 0xFF, 0x15 },
 { REG(0x1261), 0xFF, 0xFF, 0x80 },
 { REG(0x1263), 0xFF, 0xFF, 0x00 },
 { REG(0x1264), 0xFF, 0xFF, 0x00 },
 { REG(0x1265), 0xFF, 0xFF, 0x40 },
 { REG(0x126A), 0xFF, 0xFF, 0xA9 },//Same mark
 { REG(0x126B), 0xFF, 0xFF, 0xCB },//Same mark
 { REG(0x126C), 0xFF, 0xFF, 0x65 },//Same mark
 { REG(0x126D), 0xFF, 0xFF, 0x87 },//Same mark
 { REG(0x126E), 0xFF, 0xFF, 0x21 },//Same mark
 { REG(0x126F), 0xFF, 0xFF, 0x43 },//Same mark
 { REG(0x1270), 0xFF, 0xFF, 0xED },//Same mark
 { REG(0x1271), 0xFF, 0xFF, 0x0F },//Same mark
 { REG(0x1280), 0xFF, 0xFF, 0x0C },
 { REG(0x1282), 0xFF, 0xFF, 0x04 },
 { REG(0x1283), 0xFF, 0xFF, 0x00 },
 { REG(0x1284), 0xFF, 0xFF, 0x00 },
 { REG(0x1285), 0xFF, 0xFF, 0x00 },
 { REG(0x1288), 0xFF, 0xFF, 0xFF },
 { REG(0x1289), 0xFF, 0xFF, 0xFF },
 { REG(0x128A), 0xFF, 0xFF, 0x10 },//Same mark
 { REG(0x128B), 0xFF, 0xFF, 0x32 },//Same mark
 { REG(0x128C), 0xFF, 0xFF, 0x54 },//Same mark
 { REG(0x128D), 0xFF, 0xFF, 0x76 },//Same mark
 { REG(0x128E), 0xFF, 0xFF, 0x98 },//Same mark
 { REG(0x128F), 0xFF, 0xFF, 0xBA },//Same mark
 { REG(0x1290), 0xFF, 0xFF, 0xDC },//Same mark
 { REG(0x1291), 0xFF, 0xFF, 0xFE },//Same mark
 { REG(REG_TABLE_END), 0x00, 0x00 }
};

code U8 BWTABLE[][REG_ADDR_SIZE+REG_BANK_SIZE+REG_MASK_SIZE+BWTABLE_NUMS]=
{//Reg          Bank  Mask  Value
 { REG(0x2F40), 0x12, 0xFF, 0x20 /*Normal_mode*/, 0x20/*1080p_mode*/, 0x20/*HD_H264_mode*/, },
 { REG(0x2F41), 0x12, 0xFF, 0x20 /*Normal_mode*/, 0x20/*1080p_mode*/, 0x20/*HD_H264_mode*/, },
 { REG(0x2F42), 0x12, 0xFF, 0x18 /*Normal_mode*/, 0x18/*1080p_mode*/, 0x18/*HD_H264_mode*/, },
 { REG(0x2F43), 0x12, 0xFF, 0x18 /*Normal_mode*/, 0x18/*1080p_mode*/, 0x18/*HD_H264_mode*/, },
 { REG(0x2F44), 0x12, 0xFF, 0x30 /*Normal_mode*/, 0x30/*1080p_mode*/, 0x30/*HD_H264_mode*/, },
 { REG(0x2F45), 0x12, 0xFF, 0xFF /*Normal_mode*/, 0x30/*1080p_mode*/, 0x30/*HD_H264_mode*/, },
 { REG(0x2F46), 0x12, 0xFF, 0x30 /*Normal_mode*/, 0x30/*1080p_mode*/, 0x30/*HD_H264_mode*/, },
 { REG(0x2F47), 0x12, 0xFF, 0x30 /*Normal_mode*/, 0x30/*1080p_mode*/, 0x30/*HD_H264_mode*/, },
 { REG(0x2F48), 0x12, 0xFF, 0x60 /*Normal_mode*/, 0x60/*1080p_mode*/, 0x60/*HD_H264_mode*/, },
 { REG(0x2F40), 0x92, 0xFF, 0x10 /*Normal_mode*/, 0x10/*1080p_mode*/, 0x10/*HD_H264_mode*/, },
 { REG(0x2F41), 0x92, 0xFF, 0x10 /*Normal_mode*/, 0x10/*1080p_mode*/, 0x10/*HD_H264_mode*/, },
 { REG(0x2F42), 0x92, 0xFF, 0x10 /*Normal_mode*/, 0x10/*1080p_mode*/, 0x10/*HD_H264_mode*/, },
 { REG(0x2F43), 0x92, 0xFF, 0x10 /*Normal_mode*/, 0x10/*1080p_mode*/, 0x10/*HD_H264_mode*/, },
 { REG(0x2F44), 0x92, 0xFF, 0x18 /*Normal_mode*/, 0x18/*1080p_mode*/, 0x18/*HD_H264_mode*/, },
 { REG(0x2F45), 0x92, 0xFF, 0x18 /*Normal_mode*/, 0x18/*1080p_mode*/, 0x18/*HD_H264_mode*/, },
 { REG(0x2F46), 0x92, 0xFF, 0x10 /*Normal_mode*/, 0x10/*1080p_mode*/, 0x10/*HD_H264_mode*/, },
 { REG(0x2F47), 0x92, 0xFF, 0x10 /*Normal_mode*/, 0x10/*1080p_mode*/, 0x10/*HD_H264_mode*/, },
 { REG(0x2F48), 0x92, 0xFF, 0x20 /*Normal_mode*/, 0x20/*1080p_mode*/, 0x20/*HD_H264_mode*/, },
 { REG(0x1242), 0xFF, 0xFF, 0x08 /*Normal_mode*/, 0x04/*1080p_mode*/, 0x04/*HD_H264_mode*/, },
 { REG(0x124E), 0xFF, 0xFF, 0x98 /*$Normal_mode*/, 0xC8/*$1080p_mode*/, 0xC8/*$HD_H264_mode*/, },
 { REG(0x1250), 0xFF, 0xFF, 0xDC /*$Normal_mode*/, 0xD9/*$1080p_mode*/, 0xD9/*$HD_H264_mode*/, },
 { REG(0x1262), 0xFF, 0xFF, 0x18 /*Normal_mode*/, 0x00/*1080p_mode*/, 0x00/*HD_H264_mode*/, },
 { REG(0x1268), 0xFF, 0xFF, 0xDF /*Normal_mode*/, 0xD8/*1080p_mode*/, 0xD8/*HD_H264_mode*/, },
 { REG(0x1269), 0xFF, 0xFF, 0x38 /*Normal_mode*/, 0xF1/*1080p_mode*/, 0xF1/*HD_H264_mode*/, },
 { REG(0x1281), 0xFF, 0xFF, 0x80 /*Normal_mode*/, 0x80/*1080p_mode*/, 0x80/*HD_H264_mode*/, },
 { REG(0x12DD), 0xFF, 0xFF, 0x81 /*Normal_mode*/, 0x80/*1080p_mode*/, 0x80/*HD_H264_mode*/, },
 { REG(0x1240), 0xFF, 0x02, 0x02 /*Normal_mode*/, 0x02/*1080p_mode*/, 0x02/*HD_H264_mode*/, },
 { REG(0x1240), 0xFF, 0x02, 0x00 /*Normal_mode*/, 0x00/*1080p_mode*/, 0x00/*HD_H264_mode*/, },
 { REG(0x1260), 0xFF, 0x02, 0x02 /*Normal_mode*/, 0x02/*1080p_mode*/, 0x02/*HD_H264_mode*/, },
 { REG(0x1260), 0xFF, 0x02, 0x00 /*Normal_mode*/, 0x00/*1080p_mode*/, 0x00/*HD_H264_mode*/, },
 { REG(0x1280), 0xFF, 0x02, 0x02 /*Normal_mode*/, 0x02/*1080p_mode*/, 0x02/*HD_H264_mode*/, },
 { REG(0x1280), 0xFF, 0x02, 0x00 /*Normal_mode*/, 0x00/*1080p_mode*/, 0x00/*HD_H264_mode*/, },
 { REG(0x668), 0xFF, 0x38, 0xD7 /*Normal_mode*/, 0xD7/*1080p_mode*/, 0xD7/*HD_H264_mode*/, },
 { REG(0x669), 0xFF, 0xFF, 0xFF /*Normal_mode*/, 0xFF/*1080p_mode*/, 0xFF/*HD_H264_mode*/, },
 { REG(REG_TABLE_END), 0x00, 0x00 }
};

