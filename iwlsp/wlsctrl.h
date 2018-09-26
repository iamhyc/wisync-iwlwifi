#ifndef __WLSCTRL_H__
#define __WLSCTRL_H__

#include <inttypes.h>

#define DBGFS_FILE  "wlsctrl"
#define PAGE_SIZE   4096

typedef union
{
    uint8_t byte_ptr[16];
    uint16_t word_ptr[8];
    uint32_t uint_ptr[4];
    uint64_t long_ptr[2];
}info_blk;

int w_init(void);
int w_setTxPrior(void);
int w_setTxNormal(void);
int w_setTxLast(void);

#endif