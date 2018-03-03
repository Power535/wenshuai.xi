////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

#include <linux/pfn.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>          /* seems do not need this */
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <asm/string.h>

#include <linux/cdev.h>
#include <linux/interrupt.h>
#include <linux/poll.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/blkdev.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/wait.h>

#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>

#include <linux/clk.h>
#include <linux/clk-provider.h>
#include "ms_msys.h"
#include "MsCommon.h"
#include "MsTypes.h"
#include "MsOS.h"
#include "ms_platform.h"
#include "mdrv_scldma_io_i3_st.h"
#include "mdrv_scldma_io_i3.h"
#include "mdrv_scl_dbg.h"
#include "mdrv_scldma.h"
#include "mdrv_multiinst.h"
#include "mdrv_verchk.h"
//-------------------------------------------------------------------------------------------------

#define MDRV_MS_SCLDMA_DEVICE_COUNT    1
#define MDRV_MS_SCLDMA_NAME            "mscldma2"
#define MAX_FILE_HANDLE_SUPPRT         64
#define MDRV_NAME_SCLDMA               "mscldma2"
#define MDRV_MAJOR_SCLDMA              0xea
#define MDRV_MINOR_SCLDMA              0x05

#define CMD_PARSING(x)  (x==IOCTL_SCLDMA_SET_IN_BUFFER_CONFIG         ?  "IOCTL_SCLDMA_SET_IN_BUFFER_CONFIG" :  \
                         x==IOCTL_SCLDMA_SET_IN_TRIGGER_CONFIG        ?  "IOCTL_SCLDMA_SET_IN_TRIGGER_CONFIG" : \
                         x==IOCTL_SCLDMA_SET_OUT_BUFFER_CONFIG        ?  "IOCTL_SCLDMA_SET_OUT_BUFFER_CONFIG" :  \
                         x==IOCTL_SCLDMA_SET_OUT_TRIGGER_CONFIG       ?  "IOCTL_SCLDMA_SET_OUT_TRIGGER_CONFIG" : \
                         x==IOCTL_SCLDMA_GET_IN_ACTIVE_BUFFER_CONFIG  ?  "IOCTL_SCLDMA_GET_IN_ACTIVE_BUFFER_CONFIG" :\
                         x==IOCTL_SCLDMA_GET_OUT_ACTIVE_BUFFER_CONFIG ?  "IOCTL_SCLDMA_GET_OUT_ACTIVE_BUFFER_CONFIG" :\
                         x==IOCTL_SCLDMA_GET_PRIVATE_ID_CONFIG        ?  "IOCTL_SCLDMA_GET_PRIVATE_ID_CONFIG" :\
                         x==IOCTL_SCLDMA_SET_LOCK_CONFIG              ?  "IOCTL_SCLDMA_SET_LOCK_CONFIG" :\
                         x==IOCTL_SCLDMA_SET_UNLOCK_CONFIG            ?  "IOCTL_SCLDMA_SET_UNLOCK_CONFIG" :\
                                                                         "UNKNOWN")

int mdrv_ms_scldma2_open(struct inode *inode, struct file *filp);
int mdrv_ms_scldma2_release(struct inode *inode, struct file *filp);
long mdrv_ms_scldma2_ioctl(struct file *filp, unsigned int u32Cmd, unsigned long u32Arg);
static int mdrv_ms_scldma2_probe(struct platform_device *pdev);
static int mdrv_ms_scldma2_remove(struct platform_device *pdev);
static int mdrv_ms_scldma2_suspend(struct platform_device *dev, pm_message_t state);
static int mdrv_ms_scldma2_resume(struct platform_device *dev);
static unsigned int mdrv_ms_scldma2_poll(struct file *filp, struct poll_table_struct *wait);



//extern atomic_t SC1W_intr_count;

//-------------------------------------------------------------------------------------------------

typedef struct
{
    int s32Major;
    int s32Minor;
    int refCnt;
    struct cdev cdev;
    struct file_operations fops;
    ST_MDRV_SCLDMA_CLK_CONFIG stclk;
	struct device *devicenode;
}ST_DEV_SCLDMA;

static ST_DEV_SCLDMA _dev_ms_scldma2 =
{
    .s32Major = MDRV_MAJOR_SCLDMA,
    .s32Minor = MDRV_MINOR_SCLDMA,
    .refCnt = 0,
    .cdev =
    {
        .kobj = {.name= MDRV_NAME_SCLDMA, },
        .owner = THIS_MODULE,
    },
    .fops =
    {
        .open = mdrv_ms_scldma2_open,
        .release = mdrv_ms_scldma2_release,
        .unlocked_ioctl = mdrv_ms_scldma2_ioctl,
        .poll = mdrv_ms_scldma2_poll,
    }
};

static struct class * m_scldma2_class = NULL;
static char * scldma2_classname = "m_scldma2_class";


static const struct of_device_id ms_scldma2_of_match_table[] =
{
    { .compatible = "mstar,scldma2" },
    {}
};

static struct platform_driver st_ms_scldma2_driver =
{
	.probe 		= mdrv_ms_scldma2_probe,
	.remove 	= mdrv_ms_scldma2_remove,
    .suspend    = mdrv_ms_scldma2_suspend,
    .resume     = mdrv_ms_scldma2_resume,
	.driver =
	{
		.name	= MDRV_NAME_SCLDMA,
        .owner  = THIS_MODULE,
        .of_match_table = of_match_ptr(ms_scldma2_of_match_table),
	},
};

static u64 ms_scldma2_dma_mask = 0xffffffffUL;

static struct platform_device st_ms_scldma2_device =
{
    .name = "mscldma2",
    .id = 0,
    .dev =
    {
        .dma_mask = &ms_scldma2_dma_mask,
        .coherent_dma_mask = 0xffffffffUL
    }
};
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// IOCtrl Driver interface functions
//-------------------------------------------------------------------------------------------------
static ssize_t check_frm_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return MDrv_SCLDMA_ProcShow(buf,E_MDRV_SCLDMA_ID_2, E_MDRV_SCLDMA_MEM_FRM,0);
}
static ssize_t check_frm_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
	if(NULL != buf)
	{
		const char *str = buf;
        if((int)*str == 48)  //input 0  echo 0 >ptgen_call
        {
            SCL_ERR( "dma count reset %d\n",(int)*str);
            MDrv_SCLDMA_ResetTrigCountByClient(E_MDRV_SCLDMA_ID_2,E_MDRV_SCLDMA_MEM_FRM,0);
        }
        else if((int)*str == 50) //input 2
        {
            SCL_ERR( "dma count FORCE CLOSE OPEN %d\n",(int)*str);
            MDrv_SCLDMA_SetForceCloseDMAClient(E_MDRV_SCLDMA_ID_2,E_MDRV_SCLDMA_MEM_FRM,0,1);
        }
        else if((int)*str == 51) //input 3
        {
            SCL_ERR( "dma count FORCE CLOSE OVER %d\n",(int)*str);
            MDrv_SCLDMA_SetForceCloseDMAClient(E_MDRV_SCLDMA_ID_2,E_MDRV_SCLDMA_MEM_FRM,0,0);
        }
        return n;
    }

    return 0;
}

static DEVICE_ATTR(ckfrm,0600, check_frm_show, check_frm_store);
static ssize_t check_frm2_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return MDrv_SCLDMA_ProcShow(buf,E_MDRV_SCLDMA_ID_2, E_MDRV_SCLDMA_MEM_FRM2,0);
}
static ssize_t check_frm2_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t n)
{
	if(NULL != buf)
	{
		const char *str = buf;
        if((int)*str == 48)  //input 0  echo 0 >ptgen_call
        {
            SCL_ERR( "dma count reset %d\n",(int)*str);
            MDrv_SCLDMA_ResetTrigCountByClient(E_MDRV_SCLDMA_ID_2,E_MDRV_SCLDMA_MEM_FRM2,0);
        }
        else if((int)*str == 50) //input 2
        {
            SCL_ERR( "dma count FORCE CLOSE OPEN %d\n",(int)*str);
            MDrv_SCLDMA_SetForceCloseDMAClient(E_MDRV_SCLDMA_ID_2,E_MDRV_SCLDMA_MEM_FRM2,0,1);
        }
        else if((int)*str == 51) //input 3
        {
            SCL_ERR( "dma count FORCE CLOSE OVER %d\n",(int)*str);
            MDrv_SCLDMA_SetForceCloseDMAClient(E_MDRV_SCLDMA_ID_2,E_MDRV_SCLDMA_MEM_FRM2,0,0);
        }
        return n;
    }

    return 0;
}

static DEVICE_ATTR(ckfrm2,0600, check_frm2_show, check_frm2_store);

ST_MDRV_SCLDMA_VERSIONCHK_CONFIG _mdrv_ms_scldma2_io_fill_versionchkstruct
(unsigned int u32StructSize,unsigned int u32VersionSize,unsigned int *pVersion)
{
    ST_MDRV_SCLDMA_VERSIONCHK_CONFIG stVersion;
    stVersion.u32StructSize  = (unsigned int)u32StructSize;
    stVersion.u32VersionSize = (unsigned int)u32VersionSize;
    stVersion.pVersion      = (unsigned int *)pVersion;
    return stVersion;
}
int _mdrv_ms_scldma2_io_version_check(ST_MDRV_SCLDMA_VERSIONCHK_CONFIG stVersion)
{
    if ( CHK_VERCHK_HEADER(stVersion.pVersion) )
    {
        if( CHK_VERCHK_MAJORVERSION_LESS( stVersion.pVersion, IOCTL_SCLDMA_VERSION) )
        {

            VERCHK_ERR("[SCLDMA2] Version(%04x) < %04x!!! \n",
                *(stVersion.pVersion) & VERCHK_VERSION_MASK,
                IOCTL_SCLDMA_VERSION);

            return -EINVAL;
        }
        else
        {
            if( CHK_VERCHK_SIZE( &stVersion.u32VersionSize, stVersion.u32StructSize) == 0 )
            {
                VERCHK_ERR("[SCLDMA2] Size(%04x) != %04x!!! \n",
                    stVersion.u32StructSize,
                    stVersion.u32VersionSize);

                return -EINVAL;
            }
            else
            {
                return VersionCheckSuccess;
            }
        }
    }
    else
    {
        VERCHK_ERR("[SCLDMA2] No Header !!! \n");
        SCL_ERR( "[SCLDMA2]   %s  \n", __FUNCTION__);
        return -EFAULT;
    }
}
static int _ms_scldma2_multiinstSet(EN_MDRV_MULTI_INST_CMD_TYPE enType, void *stCfg ,void *privatedata)
{
    EN_MDRV_MULTI_INST_STATUS_TYPE enMultiInstRet;
    int ret = 0;
    enMultiInstRet = MDrv_MultiInst_Entry_FlashData(E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA2,privatedata ,enType,stCfg);

    if(enMultiInstRet == E_MDRV_MULTI_INST_STATUS_LOCKED)
    {
        ret = -EINVAL;
    }
    else if (enMultiInstRet == E_MDRV_MULTI_INST_STATUS_FAIL)
    {
        ret = -EFAULT;
    }
    else
    {
        ret = 0;
    }
    return ret;
}
ST_MDRV_SCLDMA_BUFFER_CONFIG _mdrv_ms_scldma2_io_fillbufferconfig(ST_IOCTL_SCLDMA_BUFFER_CONFIG stIODMABufferCfg)
{
    ST_MDRV_SCLDMA_BUFFER_CONFIG stDMABufferCfg;
    stDMABufferCfg.u8Flag = stIODMABufferCfg.u8Flag;
    stDMABufferCfg.enBufMDType = stIODMABufferCfg.enBufMDType;
    stDMABufferCfg.enColorType = stIODMABufferCfg.enColorType;
    stDMABufferCfg.enMemType = stIODMABufferCfg.enMemType;
    stDMABufferCfg.u16BufNum = stIODMABufferCfg.u16BufNum;
    stDMABufferCfg.u16Height = stIODMABufferCfg.u16Height;
    stDMABufferCfg.u16Width = stIODMABufferCfg.u16Width;
    memcpy(stDMABufferCfg.u32Base_Y,stIODMABufferCfg.u32Base_Y,sizeof(unsigned long)*BUFFER_BE_ALLOCATED_MAX);
    memcpy(stDMABufferCfg.u32Base_C,stIODMABufferCfg.u32Base_C,sizeof(unsigned long)*BUFFER_BE_ALLOCATED_MAX);
    memcpy(stDMABufferCfg.u32Base_V,stIODMABufferCfg.u32Base_V,sizeof(unsigned long)*BUFFER_BE_ALLOCATED_MAX);

    return stDMABufferCfg;
}

int _mdrv_ms_scldma2_io_set_in_buffer_config(struct file *filp, unsigned long arg)
{
    SCL_ERR( "[SCLDMA2] not support IOCTL_SCLDMA_SET_IN_BUFFER_CONFIGn");

    return -EFAULT;

}

int _mdrv_ms_scldma2_io_set_in_trigger_config(struct file *filp, unsigned long arg)
{

    SCL_ERR( "[SCLDMA2]  not support IOCTL_SCLDMA_SET_IN_TRIGGER_CONFIG");
    return -EFAULT;
}

int _mdrv_ms_scldma2_io_get_information_config(struct file *filp, unsigned long arg)
{
    ST_MDRV_SCLDMA_ATTR_TYPE stDmaInfo;
    ST_IOCTL_SCLDMA_GET_INFORMATION_CONFIG stIOGetCfg;
    int u32Bufferidx;
    ST_MDRV_SCLDMA_VERSIONCHK_CONFIG stVersion;
    stVersion = _mdrv_ms_scldma2_io_fill_versionchkstruct(sizeof(ST_IOCTL_SCLDMA_GET_INFORMATION_CONFIG),
        (((ST_IOCTL_SCLDMA_GET_INFORMATION_CONFIG __user *)arg)->VerChk_Size),
        &(((ST_IOCTL_SCLDMA_GET_INFORMATION_CONFIG __user *)arg)->VerChk_Version));
    if(_mdrv_ms_scldma2_io_version_check(stVersion))
    {
        SCL_ERR( "[SCLDMA2]   %s  \n", __FUNCTION__);
        return -EINVAL;
    }
    else
    {
        if(copy_from_user(&stIOGetCfg,
            (ST_IOCTL_SCLDMA_GET_INFORMATION_CONFIG __user *)arg, sizeof(ST_IOCTL_SCLDMA_GET_INFORMATION_CONFIG)))
        {
            return -EFAULT;
        }
    }
    if(stIOGetCfg.enMemType == E_IOCTL_SCLDMA_MEM_FRM)
    {
        stDmaInfo = MDrv_SCLDMA_GetDMAInformationByClient(E_MDRV_SCLDMA_ID_2, E_MDRV_SCLDMA_MEM_FRM,0);
    }
    else if(stIOGetCfg.enMemType == E_IOCTL_SCLDMA_MEM_FRM2)
    {
        stDmaInfo = MDrv_SCLDMA_GetDMAInformationByClient(E_MDRV_SCLDMA_ID_2, E_MDRV_SCLDMA_MEM_FRM2,0);
    }
    else if(stIOGetCfg.enMemType == E_IOCTL_SCLDMA_MEM_IMI)
    {
        stDmaInfo = MDrv_SCLDMA_GetDMAInformationByClient(E_MDRV_SCLDMA_ID_2, E_MDRV_SCLDMA_MEM_IMI,0);
    }
    else
    {
        SCL_ERR( "[SCLDMA2] not support\n");
    }
    stIOGetCfg.enBufMDType = stDmaInfo.enBufMDType;
    stIOGetCfg.enColorType = stDmaInfo.enColorType;
    stIOGetCfg.u16BufNum = stDmaInfo.u16BufNum;
    stIOGetCfg.u16DMAH = stDmaInfo.u16DMAH;
    stIOGetCfg.u16DMAV = stDmaInfo.u16DMAV;
    for(u32Bufferidx=0;u32Bufferidx<BUFFER_BE_ALLOCATED_MAX;u32Bufferidx++)
    {
        stIOGetCfg.u32Base_V[u32Bufferidx] = stDmaInfo.u32Base_V[u32Bufferidx];
        stIOGetCfg.u32Base_C[u32Bufferidx] = stDmaInfo.u32Base_C[u32Bufferidx];
        stIOGetCfg.u32Base_Y[u32Bufferidx] = stDmaInfo.u32Base_Y[u32Bufferidx];
    }
    if(copy_to_user((ST_IOCTL_SCLDMA_GET_INFORMATION_CONFIG __user *)arg,
        &stIOGetCfg, sizeof(ST_IOCTL_SCLDMA_GET_INFORMATION_CONFIG)))
    {
        return -EFAULT;
    }

    return 0;

}


int _mdrv_ms_scldma2_io_set_out_buffer_config(struct file *filp, unsigned long arg)
{
    ST_IOCTL_SCLDMA_BUFFER_CONFIG stIODMABufferCfg;
    ST_MDRV_SCLDMA_BUFFER_CONFIG stDMABufferCfg;
    int ret = 0;
    ST_MDRV_SCLDMA_VERSIONCHK_CONFIG stVersion;

    stVersion = _mdrv_ms_scldma2_io_fill_versionchkstruct(sizeof(ST_IOCTL_SCLDMA_BUFFER_CONFIG),
        (((ST_IOCTL_SCLDMA_BUFFER_CONFIG __user *)arg)->VerChk_Size),
        &(((ST_IOCTL_SCLDMA_BUFFER_CONFIG __user *)arg)->VerChk_Version));
    if(_mdrv_ms_scldma2_io_version_check(stVersion))
    {
        SCL_ERR( "[SCLDMA2]   %s  \n", __FUNCTION__);
        return -EINVAL;
    }
    else
    {
        if(copy_from_user(&stIODMABufferCfg,
            (ST_IOCTL_SCLDMA_BUFFER_CONFIG __user *)arg, sizeof(ST_IOCTL_SCLDMA_BUFFER_CONFIG)))
        {
            return -EFAULT;
        }
        else
        {
            stDMABufferCfg = _mdrv_ms_scldma2_io_fillbufferconfig(stIODMABufferCfg);
        }
    }
    if(_ms_scldma2_multiinstSet(E_MDRV_MULTI_INST_CMD_SCLDMA_OUT_BUFFER_CONFIG, (void *)&stDMABufferCfg, filp->private_data))
    {
        ret = -EFAULT;
    }
    else
    {
        if(!MDrv_SCLDMA_SetDMAWriteClientConfig(E_MDRV_SCLDMA_ID_2,  &stDMABufferCfg))
        {
            ret = -EFAULT;
        }
        else
        {
            ret = 0;
        }
    }

    return ret;
}

int _mdrv_ms_scldma2_io_set_out_trigger_config(struct file *filp, unsigned long arg)
{
    ST_MDRV_SCLDMA_TRIGGER_CONFIG stDrvTrigCfg;
    ST_IOCTL_SCLDMA_TRIGGER_CONFIG stIOTrigCfg;
    int ret = 0;
    ST_MDRV_SCLDMA_VERSIONCHK_CONFIG stVersion;

    stVersion = _mdrv_ms_scldma2_io_fill_versionchkstruct(sizeof(ST_IOCTL_SCLDMA_TRIGGER_CONFIG),
        (((ST_IOCTL_SCLDMA_TRIGGER_CONFIG __user *)arg)->VerChk_Size),
        &(((ST_IOCTL_SCLDMA_TRIGGER_CONFIG __user *)arg)->VerChk_Version));
    if(_mdrv_ms_scldma2_io_version_check(stVersion))
    {
        SCL_ERR( "[SCLDMA2]   %s  \n", __FUNCTION__);
        return -EINVAL;
    }
    else
    {
        if(copy_from_user(&stIOTrigCfg,
            (ST_IOCTL_SCLDMA_TRIGGER_CONFIG __user *)arg, sizeof(ST_IOCTL_SCLDMA_TRIGGER_CONFIG)))
        {
            return -EFAULT;
        }
        else
        {
            stDrvTrigCfg.bEn = stIOTrigCfg.bEn;
            stDrvTrigCfg.enMemType = stIOTrigCfg.enMemType;
        }
    }
    stDrvTrigCfg.stclk=&(_dev_ms_scldma2.stclk);
    if(_ms_scldma2_multiinstSet(E_MDRV_MULTI_INST_CMD_SCLDMA_OUT_TRIGGER_CONFIG, (void *)&stDrvTrigCfg, filp->private_data))
    {
        ret = -EFAULT;
    }
    else
    {
        if(!MDrv_SCLDMA_SetDMAWriteClientTrigger(E_MDRV_SCLDMA_ID_2,  &stDrvTrigCfg))
        {
            ret = -EFAULT;
        }
        else
        {
            ret = 0;
        }
    }

    return ret;
}

int _mdrv_ms_scldma2_io_get_in_active_buffer_config(struct file *filp, unsigned long arg)
{
    SCL_ERR( "[SCLDMA2] not support IOCTL_SCLDMA_GET_ACTIVE_BUFFER_CONFIG");

    return -EFAULT;

}

int _mdrv_ms_scldma2_io_get_out_active_buffer_config(struct file *filp, unsigned long arg)
{
    ST_MDRV_SCLDMA_ACTIVE_BUFFER_CONFIG stActiveCfg;
    ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG stIOActiveCfg;
    EN_MDRV_MULTI_INST_STATUS_TYPE enMultiInstRet;
    int ret = 0;
    ST_MDRV_SCLDMA_VERSIONCHK_CONFIG stVersion;

    stVersion = _mdrv_ms_scldma2_io_fill_versionchkstruct(sizeof(ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG),
        (((ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG __user *)arg)->VerChk_Size),
        &(((ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG __user *)arg)->VerChk_Version));
    if(_mdrv_ms_scldma2_io_version_check(stVersion))
    {
        SCL_ERR( "[SCLDMA2]   %s  \n", __FUNCTION__);
        return -EINVAL;
    }
    else
    {
        if(copy_from_user(&stIOActiveCfg,
            (ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG __user *)arg, sizeof(ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG)))
        {
            ret = -EFAULT;
        }
        else
        {
            stActiveCfg.enMemType = stIOActiveCfg.enMemType;
            stActiveCfg.u8ActiveBuffer = stIOActiveCfg.u8ActiveBuffer;
            enMultiInstRet = MDrv_MultiInst_Etnry_IsFree(E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA2, filp->private_data);
            stActiveCfg.stOnOff.stclk=&(_dev_ms_scldma2.stclk);
            if(enMultiInstRet == E_MDRV_MULTI_INST_STATUS_LOCKED)
            {
                stActiveCfg.u8ActiveBuffer = 0xFF;
                if(copy_to_user((ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG __user *)arg,
                    &stActiveCfg, sizeof(ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG)))
                {
                    ret = -EFAULT;
                }
                else
                {
                    ret = -EINVAL;
                }

            }
            else if(enMultiInstRet == E_MDRV_MULTI_INST_STATUS_FAIL)
            {
                ret = -EFAULT;
            }
            else
            {
                if(!MDrv_SCLDMA_GetDMAWriteBufferAcitveIdx(E_MDRV_SCLDMA_ID_2,  &stActiveCfg))
                {
                    ret = -EFAULT;
                }
                else
                {
                    stIOActiveCfg.u8ActiveBuffer  = stActiveCfg.u8ActiveBuffer;
                    stIOActiveCfg.enMemType       = stActiveCfg.enMemType;
                    stIOActiveCfg.u8ISPcount      = stActiveCfg.u8ISPcount;
                    stIOActiveCfg.u64FRMDoneTime  = stActiveCfg.u64FRMDoneTime;
                    if(copy_to_user((ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG __user *)arg,
                        &stIOActiveCfg, sizeof(ST_IOCTL_SCLDMA_ACTIVE_BUFFER_CONFIG)))
                    {
                        ret = -EFAULT;
                    }
                    else
                    {
                        ret = 0;
                    }
                }
            }
        }
    }
    return ret;
}
int _mdrv_ms_scldma2_io_get_private_id_config(struct file *filp, unsigned long arg)
{
    ST_IOCTL_SCLDMA_PRIVATE_ID_CONFIG stCfg;

    if(!MDrv_MultiInst_Entry_GetPirvateId(E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA2, filp->private_data, &stCfg.s32Id))
    {
        SCL_ERR( "[SCLDMA2]   %s  \n", __FUNCTION__);
        return -EFAULT;
    }

    if(copy_to_user((ST_IOCTL_SCLDMA_PRIVATE_ID_CONFIG __user *)arg, &stCfg, sizeof(ST_IOCTL_SCLDMA_PRIVATE_ID_CONFIG)))
    {
       return -EFAULT;
    }

    return 0;

}

int _mdrv_ms_scldma2_io_buffer_queue_handle_config(struct file *filp, unsigned long arg)
{
    ST_IOCTL_SCLDMA_BUFFER_QUEUE_CONFIG stIOBufferQCfg;
    ST_MDRV_SCLDMA_BUFFER_QUEUE_CONFIG stBufferQCfg;
    int ret = 0;
    ST_MDRV_SCLDMA_VERSIONCHK_CONFIG stVersion;
    EN_MDRV_MULTI_INST_STATUS_TYPE enMultiInstRet;
    stVersion = _mdrv_ms_scldma2_io_fill_versionchkstruct(sizeof(ST_IOCTL_SCLDMA_BUFFER_QUEUE_CONFIG),
        (((ST_IOCTL_SCLDMA_BUFFER_QUEUE_CONFIG __user *)arg)->VerChk_Size),
        &(((ST_IOCTL_SCLDMA_BUFFER_QUEUE_CONFIG __user *)arg)->VerChk_Version));
    if(_mdrv_ms_scldma2_io_version_check(stVersion))
    {
        SCL_ERR( "[SCLDMA2]   %s  \n", __FUNCTION__);
        return -EINVAL;
    }
    else
    {
        if(copy_from_user(&stIOBufferQCfg,
            (ST_IOCTL_SCLDMA_BUFFER_QUEUE_CONFIG __user *)arg, sizeof(ST_IOCTL_SCLDMA_BUFFER_QUEUE_CONFIG)))
        {
            return -EFAULT;
        }
        else
        {
            stBufferQCfg.enMemType = stIOBufferQCfg.enMemType;
            stBufferQCfg.enUsedType = stIOBufferQCfg.enUsedType;
            stBufferQCfg.u8EnqueueIdx = stIOBufferQCfg.u8EnqueueIdx;
        }
    }
    enMultiInstRet = MDrv_MultiInst_Etnry_IsFree(E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA1, filp->private_data);
    if(enMultiInstRet == E_MDRV_MULTI_INST_STATUS_LOCKED)
    {
        ret = -EINVAL;
    }
    else if(enMultiInstRet == E_MDRV_MULTI_INST_STATUS_FAIL)
    {
        ret = -EFAULT;
    }
    else
    {
        if(!MDrv_SCLDMA_BufferQueueHandle(E_MDRV_SCLDMA_ID_2,  &stBufferQCfg))
        {
            ret = 0;
        }
        else
        {
            memcpy(&stIOBufferQCfg.stRead,&stBufferQCfg.stRead,MDRV_SCLDMA_BUFFER_QUEUE_OFFSET);
            stIOBufferQCfg.u8InQueueCount = stBufferQCfg.u8InQueueCount;
            stIOBufferQCfg.u8EnqueueIdx   = stBufferQCfg.u8EnqueueIdx;
            if(copy_to_user((ST_IOCTL_SCLDMA_BUFFER_QUEUE_CONFIG __user *)arg,
                &stIOBufferQCfg, sizeof(ST_IOCTL_SCLDMA_BUFFER_QUEUE_CONFIG)))
            {
                ret = -EFAULT;
            }
            else
            {
                ret = 0;
            }
        }
    }
    return ret;
}

int _mdrv_ms_scldma2_io_get_version(struct file *filp, unsigned long arg)
{
    int ret = 0;

    if (CHK_VERCHK_HEADER( &(((ST_IOCTL_SCLDMA_VERSION_CONFIG __user *)arg)->VerChk_Version)) )
    {
        if( CHK_VERCHK_MAJORVERSION_LESS( &(((ST_IOCTL_SCLDMA_VERSION_CONFIG __user *)arg)->VerChk_Version),
            IOCTL_SCLDMA_VERSION) )
        {

            VERCHK_ERR("[SCLDMA] Version(%04x) < %04x!!! \n",
                ((ST_IOCTL_SCLDMA_VERSION_CONFIG __user *)arg)->VerChk_Version & VERCHK_VERSION_MASK,
                IOCTL_SCLDMA_VERSION);

            ret = -EINVAL;
        }
        else
        {
            if( CHK_VERCHK_SIZE( &(((ST_IOCTL_SCLDMA_VERSION_CONFIG __user *)arg)->VerChk_Size),
                sizeof(ST_IOCTL_SCLDMA_VERSION_CONFIG)) == 0 )
            {
                VERCHK_ERR("[SCLDMA] Size(%04x) != %04x!!! \n",
                    sizeof(ST_IOCTL_SCLDMA_VERSION_CONFIG),
                    (((ST_IOCTL_SCLDMA_VERSION_CONFIG __user *)arg)->VerChk_Size));

                ret = -EINVAL;
            }
            else
            {
                ST_IOCTL_SCLDMA_VERSION_CONFIG stCfg;

                stCfg = FILL_VERCHK_TYPE(stCfg, stCfg.VerChk_Version, stCfg.VerChk_Size, IOCTL_SCLDMA_VERSION);
                stCfg.u32Version = IOCTL_SCLDMA_VERSION;

                if(copy_to_user((ST_IOCTL_SCLDMA_VERSION_CONFIG __user *)arg, &stCfg,
                    sizeof(ST_IOCTL_SCLDMA_VERSION_CONFIG)))
                {
                    ret = -EFAULT;
                }
                else
                {
                    ret = 0;
                }
            }
        }
    }
    else
    {
        VERCHK_ERR("[SCLDMA] No Header !!! \n");
        SCL_ERR( "[SCLDMA]%s  \n", __FUNCTION__);
        ret = -EINVAL;
    }

    return ret;
}

//----------------------------------------------------------------------------------------------


//==============================================================================
long mdrv_ms_scldma2_ioctl(struct file *filp, unsigned int u32Cmd, unsigned long u32Arg)
{
    int err = 0;
    int retval = 0;

    if(_dev_ms_scldma2.refCnt <= 0)
    {
        SCL_ERR( "[SCLDMA2] SCLDMA2IO_IOCTL refCnt =%d!!! \n", _dev_ms_scldma2.refCnt);
        return -EFAULT;
    }
    /* check u32Cmd valid */
    if(IOCTL_SCLDMA_MAGIC == _IOC_TYPE(u32Cmd))
    {
        if(_IOC_NR(u32Cmd) >= IOCTL_SCLDMA_MAX_NR)
        {
            SCL_ERR( "[SCLDMA2] IOCtl NR Error!!! (Cmd=%x)\n",u32Cmd);
            return -ENOTTY;
        }
    }
    else
    {
        SCL_ERR( "[SCLDMA2] IOCtl MAGIC Error!!! (Cmd=%x)\n",u32Cmd);
        return -ENOTTY;
    }

    /* verify Access */
    if (_IOC_DIR(u32Cmd) & _IOC_READ)
    {
        err = !access_ok(VERIFY_WRITE, (void __user *)u32Arg, _IOC_SIZE(u32Cmd));
    }
    else if (_IOC_DIR(u32Cmd) & _IOC_WRITE)
    {
        err =  !access_ok(VERIFY_READ, (void __user *)u32Arg, _IOC_SIZE(u32Cmd));
    }
    if (err)
    {
        return -EFAULT;
    }
	/* not allow query or command once driver suspend */

    if(u32Cmd == IOCTL_SCLDMA_GET_PRIVATE_ID_CONFIG || u32Cmd == IOCTL_SCLDMA_SET_OUT_BUFFER_CONFIG
        || u32Cmd == IOCTL_SCLDMA_GET_VERSION_CONFIG || u32Cmd == IOCTL_SCLDMA_SET_IN_BUFFER_CONFIG)
    {
        SCL_DBG(SCL_DBG_LV_IOCTL()&EN_DBGMG_IOCTLEVEL_SC2, "[SCLDMA2] IOCTL_NUM:: == %s == \n", (CMD_PARSING(u32Cmd)));
    }
    else
    {
        SCL_DBG(SCL_DBG_LV_IOCTL()&EN_DBGMG_IOCTLEVEL_SC2HLEVEL, "[SCLDMA2] IOCTL_NUM:: == %s == \n", (CMD_PARSING(u32Cmd)));
    }

    switch(u32Cmd)
    {
    case IOCTL_SCLDMA_SET_IN_BUFFER_CONFIG:
        retval = _mdrv_ms_scldma2_io_set_in_buffer_config(filp, u32Arg);
        break;

    case IOCTL_SCLDMA_SET_IN_TRIGGER_CONFIG:
        retval = _mdrv_ms_scldma2_io_set_in_trigger_config(filp, u32Arg);
        break;

    case IOCTL_SCLDMA_SET_OUT_BUFFER_CONFIG:
        retval = _mdrv_ms_scldma2_io_set_out_buffer_config(filp, u32Arg);
        break;

    case IOCTL_SCLDMA_SET_OUT_TRIGGER_CONFIG:
        retval = _mdrv_ms_scldma2_io_set_out_trigger_config(filp, u32Arg);
        break;

    case IOCTL_SCLDMA_GET_IN_ACTIVE_BUFFER_CONFIG:
        retval = _mdrv_ms_scldma2_io_get_in_active_buffer_config(filp, u32Arg);
        break;

    case IOCTL_SCLDMA_GET_OUT_ACTIVE_BUFFER_CONFIG:
        retval = _mdrv_ms_scldma2_io_get_out_active_buffer_config(filp, u32Arg);
        break;

    case IOCTL_SCLDMA_GET_PRIVATE_ID_CONFIG:
        retval = _mdrv_ms_scldma2_io_get_private_id_config(filp, u32Arg);
        break;

    case IOCTL_SCLDMA_BUFFER_QUEUE_HANDLE_CONFIG:
        retval = _mdrv_ms_scldma2_io_buffer_queue_handle_config(filp, u32Arg);
        break;

    case IOCTL_SCLDMA_GET_INFORMATION_CONFIG:
        retval = _mdrv_ms_scldma2_io_get_information_config(filp, u32Arg);
        break;


    case IOCTL_SCLDMA_SET_LOCK_CONFIG:
    case IOCTL_SCLDMA_SET_UNLOCK_CONFIG:
        SCL_ERR( "[SCLDMA2] Not Support IOCTL %x\n ",u32Cmd);
        retval = -EINVAL;
        break;

    case IOCTL_SCLDMA_GET_VERSION_CONFIG:
        retval = _mdrv_ms_scldma2_io_get_version(filp, u32Arg);
        break;

    default:  /* redundant, as cmd was checked against MAXNR */
        SCL_ERR( "[SCLDMA2] ERROR IOCtl number %x\n ",u32Cmd);
        retval = -ENOTTY;
        break;
    }

    return retval;
}


static unsigned int mdrv_ms_scldma2_poll(struct file *filp, struct poll_table_struct *pstPollQueue)
{
    ST_MDRV_SCLDMA_BUFFER_DONE_CONFIG stDoneCfg;
    unsigned char bFRMDone, bIMIDone,bFRM2Done;
    unsigned int ret = 0;
    EN_MDRV_MULTI_INST_STATUS_TYPE enMultiInstRet;
    wait_queue_head_t *pWaitQueueHead = NULL;
    enMultiInstRet = MDrv_MultiInst_Etnry_IsFree(E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA2, filp->private_data);
    SCL_DBG(SCL_DBG_LV_IOCTL()&EN_DBGMG_IOCTLEVEL_SC2HLEVEL, "[SCLDMA2] %s ret=%x\n",__FUNCTION__,ret);
    if(enMultiInstRet == E_MDRV_MULTI_INST_STATUS_SUCCESS)
    {
        pWaitQueueHead = (wait_queue_head_t *)MDrv_SCLDMA_GetWaitQueueHead(E_MDRV_SCLDMA_ID_2);
        MDrv_SCLDMA_SetPollWait(filp, pWaitQueueHead, pstPollQueue);
        bFRMDone = 2;
        bFRM2Done = 2;
        bIMIDone = 2;
        if(MDrv_SCLDMA_GetOutBufferDoneEvent(E_MDRV_SCLDMA_ID_2, E_MDRV_SCLDMA_MEM_FRM, &stDoneCfg))
        {
            bFRMDone = (stDoneCfg.bDone == 0x1 )? 0x1 :
                       (stDoneCfg.bDone == 0x2 )? 0x2 :
                       (stDoneCfg.bDone == 0x3 )? 0x3 :
                       (stDoneCfg.bDone == 0xF ) ? 0xF : 0;
        }
        else
        {
            bFRMDone = 0;
        }
        if(bFRMDone &&bFRMDone!=0xF)
        {
            if(bFRMDone& 0x1)
            {
                ret |= POLLIN; /* read */
            }
            if(bFRMDone& 0x2)
            {
                ret |= POLLPRI;
            }
        }
        else if(bFRMDone ==0)
        {
            ret = 0;
        }
        else
        {
            ret = POLLERR;
        }
    }
    else
    {
        ret = 0;
    }
    return ret;
}
#if CONFIG_OF
static int mdrv_ms_scldma2_probe(struct platform_device *pdev)
{
    ST_MDRV_SCLDMA_INIT_CONFIG stSCLDMAInitCfg;
    int s32Ret;
    dev_t  dev;
    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);
    //module
    if(_dev_ms_scldma2.s32Major)
    {
        dev = MKDEV(_dev_ms_scldma2.s32Major, _dev_ms_scldma2.s32Minor);
        s32Ret = register_chrdev_region(dev, MDRV_MS_SCLDMA_DEVICE_COUNT, MDRV_MS_SCLDMA_NAME);
    }
    else
    {
        s32Ret = alloc_chrdev_region(&dev, _dev_ms_scldma2.s32Minor, MDRV_MS_SCLDMA_DEVICE_COUNT, MDRV_MS_SCLDMA_NAME);
        _dev_ms_scldma2.s32Major = MAJOR(dev);
    }

    if (0 > s32Ret)
    {
        SCL_ERR( "[SCLDMA2] Unable to get major %d\n", _dev_ms_scldma2.s32Major);
        return s32Ret;
    }

    cdev_init(&_dev_ms_scldma2.cdev, &_dev_ms_scldma2.fops);
    if (0 != (s32Ret= cdev_add(&_dev_ms_scldma2.cdev, dev, MDRV_MS_SCLDMA_DEVICE_COUNT)))
    {
        SCL_ERR( "[SCLDMA2] Unable add a character device\n");
        unregister_chrdev_region(dev, MDRV_MS_SCLDMA_DEVICE_COUNT);
        return s32Ret;
    }

    m_scldma2_class = msys_get_sysfs_class();
    if(!m_scldma2_class)
    {
        m_scldma2_class = class_create(THIS_MODULE, scldma2_classname);
    }
    if(IS_ERR(m_scldma2_class))
    {
        printk(KERN_WARNING"Failed at class_create().Please exec [mknod] before operate the device/n");
    }
    else
    {
        _dev_ms_scldma2.devicenode = device_create(m_scldma2_class, NULL, dev,NULL, "mscldma2");
        _dev_ms_scldma2.devicenode->dma_mask=&ms_scldma2_dma_mask;
        _dev_ms_scldma2.devicenode->coherent_dma_mask=ms_scldma2_dma_mask;
    }

    stSCLDMAInitCfg.u32Riubase = 0x1F000000; //ToDo
    MsOS_SetSclIrqIDFormSys(pdev,0,E_SCLIRQ_SC0);
    MsOS_SetCmdqIrqIDFormSys(pdev,1,E_CMDQIRQ_CMDQ0);
    stSCLDMAInitCfg.u32IRQNUM     = MsOS_GetIrqIDSCL(E_SCLIRQ_SC0);
    stSCLDMAInitCfg.u32CMDQIRQNUM = MsOS_GetIrqIDCMDQ(E_CMDQIRQ_CMDQ0);
    if( MDrv_SCLDMA_Init(E_MDRV_SCLDMA_ID_2, &stSCLDMAInitCfg) == 0)
    {
        return -EFAULT;
    }
    st_ms_scldma2_device.dev.of_node = pdev->dev.of_node;
    _dev_ms_scldma2.stclk.idclk = of_clk_get(st_ms_scldma2_device.dev.of_node,0);
    _dev_ms_scldma2.stclk.fclk1 = of_clk_get(st_ms_scldma2_device.dev.of_node,1);
    _dev_ms_scldma2.stclk.fclk2 = of_clk_get(st_ms_scldma2_device.dev.of_node,2);
    _dev_ms_scldma2.stclk.odclk = of_clk_get(st_ms_scldma2_device.dev.of_node,3);
    if (device_create_file(_dev_ms_scldma2.devicenode, &dev_attr_ckfrm)!= 0)
    {
      dev_err(_dev_ms_scldma2.devicenode,
       "Failed to create ckfrm sysfs files\n");
    }
    if (device_create_file(_dev_ms_scldma2.devicenode, &dev_attr_ckfrm2)!= 0)
    {
      dev_err(_dev_ms_scldma2.devicenode,
       "Failed to create ckfrm2 sysfs files\n");
    }
    MDrv_MultiInst_Entry_Init_Variable(E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA2);
    gbProbeAlready |= EN_DBG_SCLDMA2_CONFIG;
    return 0;
}

static int mdrv_ms_scldma2_remove(struct platform_device *pdev)
{
    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);
    MDrv_SCLDMA_ClkClose(&(_dev_ms_scldma2.stclk));
    gbProbeAlready = (gbProbeAlready&(~EN_DBG_SCLDMA2_CONFIG));
    if(gbProbeAlready == 0)
    {
        MDrv_SCLDMA_Exit(1);
    }
    else if(!(gbProbeAlready& (EN_DBG_SCLDMA1_CONFIG|EN_DBG_SCLDMA2_CONFIG|EN_DBG_SCLDMA3_CONFIG|EN_DBG_SCLDMA4_CONFIG)))
    {
        MDrv_SCLDMA_Exit(0);
    }
    cdev_del(&_dev_ms_scldma2.cdev);
    device_destroy(m_scldma2_class, MKDEV(_dev_ms_scldma2.s32Major, _dev_ms_scldma2.s32Minor));
    class_destroy(m_scldma2_class);
    unregister_chrdev_region(MKDEV(_dev_ms_scldma2.s32Major, _dev_ms_scldma2.s32Minor), MDRV_MS_SCLDMA_DEVICE_COUNT);
    return 0;
}
#else
static int mdrv_ms_scldma2_probe(struct platform_device *pdev)
{
    ST_MDRV_SCLDMA_INIT_CONFIG stSCLDMAInitCfg;

    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);

    stSCLDMAInitCfg.u32Riubase = 0x1F000000; //ToDo

    if( MDrv_SCLDMA_Init(E_MDRV_SCLDMA_ID_2, &stSCLDMAInitCfg) == 0)
    {
        return -EFAULT;
    }
    if (device_create_file(&pdev->dev, &dev_attr_ckfrm)!= 0)
    {
      dev_err(&pdev->dev,
       "Failed to create ckfrm sysfs files\n");
    }

    MDrv_MultiInst_Entry_Init_Variable(E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA2);
    return 0;
}

static int mdrv_ms_scldma2_remove(struct platform_device *pdev)
{
    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);
    MDrv_SCLDMA_ClkClose(&(_dev_ms_scldma2.stclk));
    cdev_del(&_dev_ms_scldma2.cdev);
    device_destroy(m_scldma2_class, MKDEV(_dev_ms_scldma2.s32Major, _dev_ms_scldma2.s32Minor));
    class_destroy(m_scldma2_class);
    unregister_chrdev_region(MKDEV(_dev_ms_scldma2.s32Major, _dev_ms_scldma2.s32Minor), MDRV_MS_SCLDMA_DEVICE_COUNT);
    return 0;
}
#endif

static int mdrv_ms_scldma2_suspend(struct platform_device *dev, pm_message_t state)
{
    int ret = 0;
    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);

    if(MDrv_SCLDMA_Suspend(E_MDRV_SCLDMA_ID_2))
    {
        MDrv_SCLDMA_ClkClose(&(_dev_ms_scldma2.stclk));
        ret = 0;
    }
    else
    {
        ret = -EFAULT;
    }
    return ret;
}


static int mdrv_ms_scldma2_resume(struct platform_device *dev)
{
    EN_MDRV_MULTI_INST_STATUS_TYPE enMultiInstRet = E_MDRV_MULTI_INST_STATUS_SUCCESS;
    int ret = 0;

    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);

    if(MDrv_SCLDMA_Resume(E_MDRV_SCLDMA_ID_2))
    {
        enMultiInstRet = MDrv_MultiInst_Entry_FlashData(
                            E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA2,
                            NULL,
                            E_MDRV_MULTI_INST_CMD_FORCE_RELOAD_CONFIG,
                            NULL);


        if(enMultiInstRet != E_MDRV_MULTI_INST_STATUS_SUCCESS)
        {
            ret = -EINVAL;
        }
        else
        {
            ret = 0;
        }
    }
    else
    {
        ret = -EFAULT;
    }

    return ret;
}


int mdrv_ms_scldma2_open(struct inode *inode, struct file *filp)
{
    int ret = 0;
    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);

    SCL_ASSERT(_dev_ms_scldma2.refCnt>=0);

    if(filp->private_data == NULL)
    {
        if(MDrv_MultiInst_Entry_Alloc(E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA2, &filp->private_data) == 0)
        {
            ret =  -EFAULT;
        }
    }

    _dev_ms_scldma2.refCnt++;

    return ret;
}


int mdrv_ms_scldma2_release(struct inode *inode, struct file *filp)
{

    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);

    MDrv_MultiInst_Entry_Free(E_MDRV_MULTI_INST_ENTRY_ID_SCLDMA2, filp->private_data);

    _dev_ms_scldma2.refCnt--;
    SCL_ASSERT(_dev_ms_scldma2.refCnt>=0);

    //free_irq(INT_IRQ_SCLDMA2W, MDrv_SCLDMA2W_isr);
    if(_dev_ms_scldma2.refCnt==0)
    {
        MDrv_SCLDMA_Release(E_MDRV_SCLDMA_ID_2,&(_dev_ms_scldma2.stclk));
    }
    return 0;
}


//-------------------------------------------------------------------------------------------------
// Module functions
//-------------------------------------------------------------------------------------------------
#if CONFIG_OF
int _mdrv_ms_scldma2_init(void)
{
    int ret = 0;
    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s:%d\n",__FUNCTION__,__LINE__);
    ret = platform_driver_register(&st_ms_scldma2_driver);
    if (!ret)
    {
        SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] platform_driver_register success\n");
        if(gbProbeAlready&EN_DBG_SCLDMA2_CONFIG)
        {
            SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] Probe success\n");
        }
        else
        {
            SCL_ERR( "[SCLDMA2] Probe Fail\n");
        }
        if(gbProbeAlready==EN_DBG_SCL_CONFIG)
        {
            SCL_ERR( "[SCL] SCL init success\n");
        }
    }
    else
    {
        SCL_ERR( "[SCLDMA2] platform_driver_register failed\n");
        platform_driver_unregister(&st_ms_scldma2_driver);
    }


    return ret;
}
void _mdrv_ms_scldma2_exit(void)
{
    /*de-initial the who GFLIPDriver */
    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);
    platform_driver_unregister(&st_ms_scldma2_driver);
}

#else
int _mdrv_ms_scldma2_init(void)
{
    int ret = 0;
    int s32Ret;
    dev_t  dev;

    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);

    if(_dev_ms_scldma2.s32Major)
    {
        dev = MKDEV(_dev_ms_scldma2.s32Major, _dev_ms_scldma2.s32Minor);
        s32Ret = register_chrdev_region(dev, MDRV_MS_SCLDMA_DEVICE_COUNT, MDRV_MS_SCLDMA_NAME);
    }
    else
    {
        s32Ret = alloc_chrdev_region(&dev, _dev_ms_scldma2.s32Minor, MDRV_MS_SCLDMA_DEVICE_COUNT, MDRV_MS_SCLDMA_NAME);
        _dev_ms_scldma2.s32Major = MAJOR(dev);
    }

    if (0 > s32Ret)
    {
        SCL_ERR( "[SCLDMA2] Unable to get major %d\n", _dev_ms_scldma2.s32Major);
        return s32Ret;
    }

    cdev_init(&_dev_ms_scldma2.cdev, &_dev_ms_scldma2.fops);
    if (0 != (s32Ret= cdev_add(&_dev_ms_scldma2.cdev, dev, MDRV_MS_SCLDMA_DEVICE_COUNT)))
    {
        SCL_ERR( "[SCLDMA2] Unable add a character device\n");
        unregister_chrdev_region(dev, MDRV_MS_SCLDMA_DEVICE_COUNT);
        return s32Ret;
    }

    m_scldma2_class = class_create(THIS_MODULE, scldma2_classname);
    if(IS_ERR(m_scldma2_class))
    {
        printk(KERN_WARNING"Failed at class_create().Please exec [mknod] before operate the device/n");
    }
    else
    {
        device_create(m_scldma2_class, NULL, dev,NULL, "mscldma2");
    }

    /* initial the whole SCLDMA2 Driver */
    ret = platform_driver_register(&st_ms_scldma2_driver);

    if (!ret)
    {
        ret = platform_device_register(&st_ms_scldma2_device);
        if (ret)    /* if register device fail, then unregister the driver.*/
        {
            platform_driver_unregister(&st_ms_scldma2_driver);
            SCL_ERR( "[SCLDMA2] platform_driver_register failed\n");

        }
        else
        {
            SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] platform_driver_register success\n");
        }
    }


    return ret;
}


void _mdrv_ms_scldma2_exit(void)
{
    /*de-initial the who GFLIPDriver */
    SCL_DBG(SCL_DBG_LV_MDRV_IO(), "[SCLDMA2] %s\n",__FUNCTION__);

    cdev_del(&_dev_ms_scldma2.cdev);
    device_destroy(m_scldma2_class, MKDEV(_dev_ms_scldma2.s32Major, _dev_ms_scldma2.s32Minor));
    class_destroy(m_scldma2_class);
    unregister_chrdev_region(MKDEV(_dev_ms_scldma2.s32Major, _dev_ms_scldma2.s32Minor), MDRV_MS_SCLDMA_DEVICE_COUNT);
    platform_driver_unregister(&st_ms_scldma2_driver);
}
#endif

module_init(_mdrv_ms_scldma2_init);
module_exit(_mdrv_ms_scldma2_exit);

MODULE_AUTHOR("MSTAR");
MODULE_DESCRIPTION("ms scldma2 ioctrl driver");
MODULE_LICENSE("GPL");