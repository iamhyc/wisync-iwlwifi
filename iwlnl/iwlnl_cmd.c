#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include "iwlnl.h"

int main(int argc, char *argv[])
{
    int ret;

    int queue, aifs=0, cw_min=1, cw_max=1;
    // uint16_t txop = 0x00;
    struct nl_msg *msg = NULL;

    while (1)
    {
        int option_index = 0;
        static struct option long_options[] =
        {
            {"queue", required_argument,    0, 'i'},
            {"cw_min", required_argument,   0, '<'},
            {"cw_max", required_argument,   0, '>'},
            {"aifs", required_argument,     0, 't'},
            {0, 0, 0, 0}, //padding by design
        };
        
        ret = getopt_long(argc, argv, "i:t:<:>:", long_options, &option_index);
        if (ret == -1)
            break;
        
        switch(ret)
        {
            case 0:
                if (long_options[option_index].flag != 0)
                    break;
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;
            case 'i': //queue
                queue = atoi(optarg);
                break;
            case 't': //nAIFS
                aifs = atoi(optarg);
                break;
            case '<':
                cw_min = atoi(optarg);
                break;
            case '>':
                cw_max = atoi(optarg);
                break;
            case '?':
                //print the helper message
                fprintf(stderr, "iwlnl -i <queue> -t <nAIFS>\n");
                fprintf(stderr, "      --cw_min <CW_min> --cw_max <CW_max>\n");
                exit(1);
            default:
                abort();
        }
    }

    nlsock_init();
    
    genTxMsg(&msg, queue, aifs, cw_min, cw_max);
    
    ret = sendTxMsg(msg);
    return 0;
}