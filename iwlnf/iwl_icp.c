
//Moudle Reference
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/version.h>
//User Reference
#include "iwlnf.h"
#include "IWLINC.h"

static u32 RealAddr = 0;
static u32 MaskAddr = 0;
// static struct net_device* tmp_dev;

static struct nf_hook_ops iwlnf_outbound = {
    .hook = nf_hookfn_out,
    .pf = PF_INET,
    .hooknum = NF_INET_POST_ROUTING, //NF_INET_LOCAL_OUT
    .priority = NF_IP_PRI_LAST
};

unsigned int nf_hookfn_out(void *priv,
			       struct sk_buff *skb,
			       const struct nf_hook_state *state)
{
    struct iphdr *iph = NULL;
    struct tcphdr *tcph = NULL;

    if ( (iph=ip_hdr(skb)) && (GET_PDST(iph)==OUTBOUND_PORT) )
    {
        // skb->dev = tmp_dev; //FIXME: does not work properly
        iph->saddr = MaskAddr;
        tcph = (struct tcphdr *)((u8 *)iph + iph->ihl*4);
        tcph->check = 0;
        iph->check = 0; //set to ZERO to force re-calculation
        tcph->check = ~csum_tcpudp_magic(
                        iph->saddr, iph->daddr,
                        skb->len - iph->ihl*4,
                        iph->protocol, 0);
        iph->check = ip_fast_csum(iph, iph->ihl);
        // dumpTCP("OUTBOUND", iph);
    }

    return NF_ACCEPT;
}

static int __init iwlnf_init(void)
{
    unsigned int ret;

    printh("iwlnf intercept init\n");

    // tmp_dev = dev_get_by_name(&init_net, TMP_DEV);
    MaskAddr = IP2NUM(FIXED_MASKADDR);
    if ((RealAddr = getWlsAddr("wls")) == 0)
    {
        printh("wlsif not exist.\n");
        return 0;
    }
    printk("0x%08x, 0x%08x\n", RealAddr, MaskAddr);

    ret = nf_register_net_hook(&init_net, &iwlnf_outbound);
	if (ret < 0) {
        printh("Post-routing Hook Error\n");
        return ret;
    }
    return 0;
}

static void __exit iwlnf_fini(void)
{
	nf_unregister_net_hook(&init_net, &iwlnf_outbound);
	printh("iwlnf intercept exit ...\n");
}

module_init(iwlnf_init);
module_exit(iwlnf_fini);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lab1112-VLC");