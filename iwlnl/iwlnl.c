
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <net/if.h>
#include <linux/nl80211.h>
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>
#include "iwlnl.h"
#include "../iwlnf/IWLINC.h"

#define TXQ_MASK_AC		0x00000003 //2-bit
#define TXQ_MASK_AIFS	0x0000003C //4-bit, <<2
#define TXQ_MASK_CWMIN	0x0007FFC0 //13-bit, <<6
#define TXQ_MASK_CWMAX	0xFFF80000 //13-bit, <<19

struct nl_msg *z_msg[4];
struct nl_msg *g_msg[4];
struct nl_sock *sock;
int dev_idx, driver_id;

int sendTxMsg(struct nl_msg* msg)
{
    return nl_send_auto_complete(sock, msg);
}

void genTxMsg(struct nl_msg** msg, \
              int queue, int aifs, int cw_min, int cw_max)
{
    uint32_t data = 0;
    *msg = nlmsg_alloc();
    
    genlmsg_put(*msg, NL_AUTO_PORT, NL_AUTO_SEQ, driver_id, 0, 0, NL80211_CMD_SET_WIPHY, 0);
    
    NLA_PUT_U32(*msg, NL80211_ATTR_IFINDEX, dev_idx);
    
    data |= (queue<<0) & TXQ_MASK_AC;
    data |= (aifs<<2) & TXQ_MASK_AIFS;
    data |= (cw_min<<6) & TXQ_MASK_CWMIN;
    data |= (cw_max<<19) & TXQ_MASK_CWMAX;
    NLA_PUT_U32(*msg, NL80211_ATTR_WIPHY_TXQ_PARAMS, data);
    return;
    
nla_put_failure:
	printf("nla_put_failure\n");
	exit(1);
}

int nlsock_init()
{
    sock = nl_socket_alloc();
    genl_connect(sock);
    driver_id = genl_ctrl_resolve(sock, NL80211_GENL_NAME);
    dev_idx = if_nametoindex(IF_TARGET);
    // zero message (queue, qifs, cw_min, cw_max)
    genTxMsg(&z_msg[0], 0, 0, 1, 1);
    genTxMsg(&z_msg[1], 1, 0, 1, 1);
    genTxMsg(&z_msg[2], 2, 0, 1, 1);
    genTxMsg(&z_msg[3], 3, 0, 1, 1);
    // reset message (queue, qifs, cw_min, cw_max)
    genTxMsg(&g_msg[0], 0, 2, 3,  7);
    genTxMsg(&g_msg[1], 1, 2, 7,  15);
    genTxMsg(&g_msg[2], 2, 3, 15, 1023);
    genTxMsg(&g_msg[3], 3, 7, 15, 1023);
    return 0;
}

int nlsock_set_prior()
{
    int ret;
    ret = nl_send_auto_complete(sock, z_msg[0]);
    ret = nl_send_auto_complete(sock, z_msg[1]);
    ret = nl_send_auto_complete(sock, z_msg[2]);
    ret = nl_send_auto_complete(sock, z_msg[3]);
    return ret;
}

int nlsock_reset_prior()
{
    int ret;
    ret = nl_send_auto_complete(sock, g_msg[0]);
    ret = nl_send_auto_complete(sock, g_msg[1]);
    ret = nl_send_auto_complete(sock, g_msg[2]);
    ret = nl_send_auto_complete(sock, g_msg[3]);
    return ret;
}
