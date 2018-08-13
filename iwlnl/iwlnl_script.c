#include <sys/time.h>
#include <stdio.h>
#include "iwlnl.h"

int main(int argc, char const *argv[])
{
    int req;
    struct timeval t0, t1, res;

    gettimeofday(&t0, NULL);

    if(argc!=2)
    {
        printf("Invalid Argument, (-1, 0, 1) supported.\n");
        return -1;
    }

    req = atoi(argv[1]);
    switch(req)
    {
        case 1:
            nlsock_init(MSG_PRIOR);
            nlsock_set_prior();
            break;
        case 0:
            nlsock_init(MSG_RESET);
            nlsock_reset_prior();
            break;
        case -1:
            nlsock_init(MSG_LAST);
            nlsock_set_last();
            break;
        default:
            break;
    }
    
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &res);

    printf("%ld.%06ld, %ld.%06ld, %ld.%06ld\n", \
        t0.tv_sec, t0.tv_usec,
        t1.tv_sec, t1.tv_usec,
        res.tv_sec, res.tv_usec);

    return 0;
}
