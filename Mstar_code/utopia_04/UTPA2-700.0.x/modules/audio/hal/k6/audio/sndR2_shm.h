#ifndef _AUDIO_SND_R2_SHM_H_
#define  _AUDIO_SND_R2_SHM_H_

/**************************************************************************************************************************
*
*       SHARE MEMORY of DEC - R2
*
**************************************************************************************************************************/
#define MBOX_SND_R2_CTRL        0x2E88
    #define MBOX_SND_R2_CTRL_LOCK_SHM_BIT                   0x0001          //[0]: lock "share memory" update
    
#define MBOX_SND_R2_STATUS      0x2EA8
    #define MBOX_SND_R2_STATUS_UPDATING_SHM_BIT             0x0001          //[0]: R2 is updating "share memory" now.    

#define SND_R2_SHM_DDR_OFFSET                               0xA000
#define SND_R2_SHM_DDR_SIZE                                 0x600

#define MAX_ADEC_IN_SND_R2                                                        0

typedef struct
{
    AUR2_AENC_PARAM     commEncParam;
    AUR2_AASE_DV258_PARAM   dv258_param_shm;
    AUR2_MP3E_PARAM mp3e_param_shm[2];
    AUR2_MP3E_INFO mp3e_info_shm[2];
} SND_R2_SHARE_MEM;

#endif
