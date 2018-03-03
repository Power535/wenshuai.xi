#if (PQ_GRULE_NR_ENABLE) || (PQ_GRULE_MPEG_NR_ENABLE) || (PQ_GRULE_FILM_MODE_ENABLE)
typedef enum
{
#if PQ_GRULE_NR_ENABLE
    PQ_GRule_NR_Main,
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
    PQ_GRule_STB_PQ_Main,
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
    PQ_GRule_FILM_MODE_Main,
#endif

}
MST_GRule_Index_Main;
#endif

#if PQ_GRULE_NR_ENABLE
typedef enum
{
    PQ_GRule_NR_Off_Main,
    PQ_GRule_NR_Low_Main,
    PQ_GRule_NR_Middle_Main,
    PQ_GRule_NR_High_Main,
    PQ_GRule_NR_RF_NOMEM_Main,
    PQ_GRule_NR_Auto_Main,
}
MST_GRule_NR_Index_Main;
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
typedef enum
{
    PQ_GRule_STB_PQ_Off_Main,
    PQ_GRule_STB_PQ_Level1_Main,
    PQ_GRule_STB_PQ_Level2_Main,
}
MST_GRule_STB_PQ_Index_Main;
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
typedef enum
{
    PQ_GRule_FILM_MODE_Off_Main,
    PQ_GRule_FILM_MODE_On_Main,
}
MST_GRule_FILM_MODE_Index_Main;
#endif

#if PQ_GRULE_NR_ENABLE
typedef enum
{
    PQ_GRule_Lvl_NR_Off_Main,
    PQ_GRule_Lvl_NR_Auto_Main,
    PQ_GRule_Lvl_NR_Low_Main,
    PQ_GRule_Lvl_NR_Middle_Main,
    PQ_GRule_Lvl_NR_High_Main,
    PQ_GRule_Lvl_NR_RF_NOMEM_Main,
}
MST_GRule_NR_LvL_Index_Main;
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
typedef enum
{
    PQ_GRule_Lvl_STB_PQ_Off_Main,
    PQ_GRule_Lvl_STB_PQ_Level1_Main,
    PQ_GRule_Lvl_STB_PQ_Level2_Main,
}
MST_GRule_STB_PQ_LvL_Index_Main;
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
typedef enum
{
    PQ_GRule_Lvl_FILM_MODE_Off_Main,
    PQ_GRule_Lvl_FILM_MODE_On_Main,
}
MST_GRule_FILM_MODE_LvL_Index_Main;
#endif


#define PQ_GRULE_RULE_NUM_Main 3

#if PQ_GRULE_NR_ENABLE
#define PQ_GRULE_NR_IP_NUM_Main 4
#define PQ_GRULE_NR_NUM_Main 6
#define PQ_GRULE_NR_LVL_NUM_Main 6
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
#define PQ_GRULE_STB_PQ_IP_NUM_Main 18
#define PQ_GRULE_STB_PQ_NUM_Main 3
#define PQ_GRULE_STB_PQ_LVL_NUM_Main 3
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
#define PQ_GRULE_FILM_MODE_IP_NUM_Main 4
#define PQ_GRULE_FILM_MODE_NUM_Main 2
#define PQ_GRULE_FILM_MODE_LVL_NUM_Main 2
#endif

#if PQ_GRULE_NR_ENABLE
extern U8 MST_GRule_NR_IP_Index_Main[PQ_GRULE_NR_IP_NUM_Main];
extern U8 MST_GRule_NR_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_NR_NUM_Main][PQ_GRULE_NR_IP_NUM_Main];
#endif

#if PQ_GRULE_MPEG_NR_ENABLE
extern U8 MST_GRule_STB_PQ_IP_Index_Main[PQ_GRULE_STB_PQ_IP_NUM_Main];
extern U8 MST_GRule_STB_PQ_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_STB_PQ_NUM_Main][PQ_GRULE_STB_PQ_IP_NUM_Main];
#endif

#if PQ_GRULE_FILM_MODE_ENABLE
extern U8 MST_GRule_FILM_MODE_IP_Index_Main[PQ_GRULE_FILM_MODE_IP_NUM_Main];
extern U8 MST_GRule_FILM_MODE_Main[QM_INPUTTYPE_NUM_Main][PQ_GRULE_FILM_MODE_NUM_Main][PQ_GRULE_FILM_MODE_IP_NUM_Main];
#endif

#if PQ_GRULE_NR_ENABLE
extern U8 MST_GRule_1920_NR_Main[PQ_GRULE_NR_LVL_NUM_Main];
#endif
#if PQ_GRULE_MPEG_NR_ENABLE
extern U8 MST_GRule_1920_STB_PQ_Main[PQ_GRULE_STB_PQ_LVL_NUM_Main];
#endif
#if PQ_GRULE_FILM_MODE_ENABLE
extern U8 MST_GRule_1920_FILM_MODE_Main[PQ_GRULE_FILM_MODE_LVL_NUM_Main];
#endif

#if PQ_GRULE_NR_ENABLE
extern U8 MST_GRule_1366_NR_Main[PQ_GRULE_NR_LVL_NUM_Main];
#endif
#if PQ_GRULE_MPEG_NR_ENABLE
extern U8 MST_GRule_1366_STB_PQ_Main[PQ_GRULE_STB_PQ_LVL_NUM_Main];
#endif
#if PQ_GRULE_FILM_MODE_ENABLE
extern U8 MST_GRule_1366_FILM_MODE_Main[PQ_GRULE_FILM_MODE_LVL_NUM_Main];
#endif

#if PQ_GRULE_NR_ENABLE
extern U8 MST_GRule_4K2K_NR_Main[PQ_GRULE_NR_LVL_NUM_Main];
#endif
#if PQ_GRULE_MPEG_NR_ENABLE
extern U8 MST_GRule_4K2K_STB_PQ_Main[PQ_GRULE_STB_PQ_LVL_NUM_Main];
#endif
#if PQ_GRULE_FILM_MODE_ENABLE
extern U8 MST_GRule_4K2K_FILM_MODE_Main[PQ_GRULE_FILM_MODE_LVL_NUM_Main];
#endif
