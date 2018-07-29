#ifndef __IWLNF_H__
#define __IWLNF_H__

//Network Reference
#include <linux/inetdevice.h>
#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/inet.h>
#include <net/ip.h>
#include <net/tcp.h>
//#include <asm-generic/checksum.h>

#define KEYWORD "[iwlnf]"
#define KERN_LOG KERN_NOTICE KEYWORD
#define printh(x) printk(KERN_LOG x)
#define printf    printk

#define IPV4A(x)   ((u8 *)x)[0]
#define IPV4B(x)   ((u8 *)x)[1]
#define IPV4C(x)   ((u8 *)x)[2]
#define IPV4D(x)   ((u8 *)x)[3]

#define IPHDR_CHK(x)    (x!=NULL && (void *)ip_hdr(x)>(void *)x)
#define IPHDR_GET(x)    (IPHDR_CHK(x)?ip_hdr(x):NULL)
#define TCPHDR_CHK(x)   (IPHDR_CHK(x) && (void *)tcp_hdr(x)>(void *)x)
#define TCPHDR_GET(x)   (TCPHDR_CHK(x)?tcp_hdr(x):NULL)

#define GET_PPDST(iph)  (__be16 *)((char *)iph + iph->ihl*4 + 2)
#define GET_PDST(iph)   ntohs(*GET_PPDST(iph))
#define GET_PPSRC(iph)  (__be16 *)((char *)iph + iph->ihl*4 + 4)
#define GET_PSRC(iph)   ntohs(*GET_PPSRC(iph))

#define MAX_MAP_NUM     15
#define MAP_FORWARD     0
#define MAP_BACKWARD    1

typedef struct
{
    u32 SrcAddr;
    u32 DstAddr;
}VRMap_t;

u32 IP2NUM(const char *addr)
{
    u8 num[4];
    int a,b,c,d;
    sscanf(addr, "%d.%d.%d.%d", &a,&b,&c,&d);
    num[0]=a; num[1]=b; num[2]=c; num[3]=d;
    return *(u32 *)num;
}

inline void NUM2IP(u32 addr, char *str)
{
    snprintf(str, 16, "%pI4", &addr);
}

u32 getIfAddr(const char *if_name)
{
    u32 ipv4 = 0;
    struct net_device* dev;
    struct in_device* pdev;

    dev = dev_get_by_name(&init_net, if_name);
    if(dev && netif_running(dev) && (dev->ip_ptr!=NULL))
    {
        pdev = (struct in_device *)dev->ip_ptr;
        if(pdev->ifa_list)
        {
            ipv4 = pdev->ifa_list->ifa_address;
        }
    }

    return ipv4;
}

void dumpTCP(const char* key, struct iphdr *iph)
{
    char saddr[16], daddr[16];
    struct tcphdr *tcph = (struct tcphdr *)((u8 *)iph + iph->ihl*4);
    NUM2IP(iph->saddr, saddr);
    NUM2IP(iph->daddr, daddr);
    printk("[%s]\
            \n\tSeq: 0x%08x; ACK: 0x%08x\
            \n\tSrc: %s, Dst:%s, %d -> %d\
            \n\tSYN %d; ACK %d; FIN %d; RST %d; PSH %d\n", \
            key,
            ntohs(tcph->seq), ntohs(tcph->ack_seq), \
            saddr, daddr, ntohs(tcph->source), ntohs(tcph->dest), \
            tcph->syn, tcph->ack, tcph->fin, tcph->rst, tcph->psh);
}

unsigned int nf_hookfn_in(void *, struct sk_buff *, const struct nf_hook_state *);
unsigned int nf_hookfn_out(void *, struct sk_buff *, const struct nf_hook_state *);

#endif //__IWLNF_H__
