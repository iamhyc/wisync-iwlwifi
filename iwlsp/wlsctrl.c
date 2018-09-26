#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "wlsctrl.h"
#define MAX_TIMEOUT 1000

static info_blk *w_blk;
//<little-edian> ac-16, cwMin-16, cwMax-16, txop-16, aifs-8
static const char tx_prior[9]  = {0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00}; //0,1,1,0,0
static const char tx_normal[9] = {0x00, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x00, 0x02}; //0,3,7,0,2
static const char tx_last[9]   = {0x00, 0x00, 0xFF, 0x03, 0xFF, 0x07, 0x00, 0x00, 0x0F}; //0,1023,2047,0,15

static inline int isNotReading()
{
    return (w_blk->byte_ptr[15]&0xFF) == 0x00;
}

static inline void setReadable()
{
    w_blk->byte_ptr[15] |= 0x80;
}

int w_setTxPrior()
{
    int cnt = 0;
    while(cnt<MAX_TIMEOUT)
    {
        ++cnt;
        if(isNotReading())
        {
            memcpy(w_blk, tx_prior, sizeof(tx_prior));
            setReadable();
            return 0;
        }
    }
    return -1;
}

int w_setTxNormal()
{
    int cnt = 0;
    while(cnt<MAX_TIMEOUT)
    {
        ++cnt;
        if(isNotReading())
        {
            memcpy(w_blk, tx_normal, sizeof(tx_normal));
            setReadable();
            return 0;
        }
    }
    return -1;
}

int w_setTxLast()
{
    int cnt = 0;
    while(cnt<MAX_TIMEOUT)
    {
        ++cnt;
        if(isNotReading())
        {
            memcpy(w_blk, tx_last, sizeof(tx_last));
            setReadable();
            return 0;
        }
    }
    return -1;
}

int w_init()
{
    int fd;

    fd = open("/proc/" DBGFS_FILE, O_RDWR|O_SYNC);
    if(fd < 0)
    {
        perror("Open call failed");
        return -1;
    }

    w_blk = (info_blk *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (w_blk == MAP_FAILED)
    {
        perror("mmap operation failed");
        return -1;
    }

    return fd;
}
