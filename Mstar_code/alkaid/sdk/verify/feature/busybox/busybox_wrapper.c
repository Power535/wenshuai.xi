#include <stdlib.h>
#include <string.h>
#include "busybox_wrapper.h"

static int cmd_comp(const void *l, const void *r){
    const busybox_cmd_t *lc = l, *rc = r;
    return strcmp(lc->name, rc->name);
}

static busybox_cmd_t *cmds;
static int cmdcount;
int run_customer_applet(int argc, const char *argv[]){
    const busybox_cmd_t key = {*argv, NULL};
    const busybox_cmd_t *cmd = bsearch(&key, cmds,
                     cmdcount, sizeof(busybox_cmd_t), cmd_comp);
    if(cmd){
        return cmd->func(argv, argc);
    }
    return -1;
}

int lbb_main(const char *argv[]);
void busybox_loop(busybox_cmd_t *cmdlist, int count){
    const char *argv[] = {"busybox", "ash", NULL};

    qsort(cmdlist, count, sizeof(busybox_cmd_t), cmd_comp);
    cmds = cmdlist;
    cmdcount = count;
    lbb_main(argv);
}
