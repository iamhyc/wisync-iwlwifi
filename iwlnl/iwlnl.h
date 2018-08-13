
#ifndef __IWLNL_H__
#define __IWLNL_H__

#include <stdlib.h>
#include <stdint.h>

#define CTRL_PORT   13333
#define CTRL_MARGIN 50//us

#define MSG_LAST    0x01
#define MSG_RESET   0x02
#define MSG_PRIOR   0x04

typedef struct CtrlPak
{
    uint32_t period;
    uint32_t offset;
    uint32_t duration;
}ctrlpak_t; //16 byte

typedef struct Param
{
    int updated;
    struct timeval ti;
    ctrlpak_t ctrlpak;
}param_t;

extern struct nl_msg *z_msg[4];
extern struct nl_msg *g_msg[4];

int sendTxMsg(struct nl_msg* msg);
void genTxMsg(struct nl_msg** msg, \
              int queue, int aifs, int cw_min, int cw_max);

int nlsock_init(int);
int nlsock_set_last(void);
int nlsock_set_prior(void);
int nlsock_reset_prior(void);

#endif //__IWLNL_H__
