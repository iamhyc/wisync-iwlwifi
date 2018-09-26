
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

static struct nf_hook_ops iwlnf_inbound = {
    .hook = nf_hookfn_in,
    .pf = PF_INET,
    .hooknum = NF_INET_PRE_ROUTING,
    .priority = NF_IP_PRI_FIRST
};

unsigned int nf_hookfn_in(void *priv,
			       struct sk_buff *skb,
			       const struct nf_hook_state *state)
{
    // struct iphdr *iph = NULL;
    // if ( (iph=IPHDR_GET(skb)) && (GET_PSRC(iph)==5201) )
    // {
    //     dumpTCP("INBOUND", iph);
    // }
    // return NF_ACCEPT;
    u8 *psd = NULL;
    struct iphdr *iph = NULL;
    struct tcphdr *tcph = NULL;
    const int prev_len = sizeof(struct iphdr) + sizeof(struct udphdr);

    if (unlikely(skb_linearize(skb) != 0))
        return NF_ACCEPT;

    if ( (iph=ip_hdr(skb)) && (GET_PDST(iph)==INBOUND_PORT) )//NOTE: this is UDP
    {
        psd = (u8 *)iph + prev_len;
        memmove(iph, psd, (skb->head + skb->tail - psd));
        skb_trim(skb, skb->len - prev_len);

        iph->daddr = RealAddr;
        tcph = (struct tcphdr *)((u8 *)iph + iph->ihl*4);
        tcph->check = 0;
        iph->check = 0; //set to ZERO to force re-calculation
        tcph->check = ~csum_tcpudp_magic(
                        iph->saddr, iph->daddr,
                        skb->len - iph->ihl*4,
                        iph->protocol, 0);
        iph->check = ip_fast_csum(iph, iph->ihl);
        // dumpTCP("INBOUND", iph);
    }
    return NF_ACCEPT;
}

static int __init iwlnf_init(void)
{
    unsigned int ret;

    printh("iwlnf injection init ...\n");

    MaskAddr = IP2NUM(FIXED_MASKADDR);
    if ((RealAddr = getWlsAddr("wls")) == 0)
    {
        printh("wlsif not exist.\n");
        return 0;
    }

    ret = nf_register_net_hook(&init_net, &iwlnf_inbound);
	if (ret < 0) {
        printh("Pre-routing Hook Failed\n");
        return ret;
    }

    return 0;
}

static void __exit iwlnf_fini(void)
{
	nf_unregister_net_hook(&init_net, &iwlnf_inbound);
	printh("iwlnf injection exit ...\n");
}

module_init(iwlnf_init);
module_exit(iwlnf_fini);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lab1112-VLC");