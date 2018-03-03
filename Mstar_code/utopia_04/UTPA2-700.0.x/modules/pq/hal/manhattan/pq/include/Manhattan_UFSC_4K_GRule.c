
#if PQ_GRULE_UFSC_MPEG_NR_ENABLE
code U8 MST_GRule_4K_MPEG_NR_UFSC[PQ_GRULE_MPEG_NR_LVL_NUM_UFSC]=
{
    PQ_GRule_MPEG_NR_Off_UFSC,
    PQ_GRule_MPEG_NR_Low_UFSC,
    PQ_GRule_MPEG_NR_Middle_UFSC,
    PQ_GRule_MPEG_NR_High_UFSC,
};
#endif


#if PQ_GRULE_UFSC_DYNAMIC_CONTRAST_ENABLE
code U8 MST_GRule_4K_DYNAMIC_CONTRAST_UFSC[PQ_GRULE_DYNAMIC_CONTRAST_LVL_NUM_UFSC]=
{
    PQ_GRule_DYNAMIC_CONTRAST_Off_UFSC,
    PQ_GRule_DYNAMIC_CONTRAST_On_UFSC,
};
#endif


#if PQ_GRULE_UFSC_SR_CONTROL_ENABLE
code U8 MST_GRule_4K_SR_CONTROL_UFSC[PQ_GRULE_SR_CONTROL_LVL_NUM_UFSC]=
{
    PQ_GRule_SR_CONTROL_Off_UFSC,
    PQ_GRule_SR_CONTROL_Low_UFSC,
    PQ_GRule_SR_CONTROL_Middle_UFSC,
    PQ_GRule_SR_CONTROL_On_High_UFSC,
};
#endif
