#!/bin/bash
PWD=`dirname $0`

WLAN=`cat /proc/net/dev | grep 'wl' | awk -F":" '{print $1}'`
# CHAN=1 #default over channel 1
SSID='VirtualWiFi-1112'
PASS='11121112'

sudo create_ap --config $PWD/create_ap.conf $WLAN $WLAN $SSID $PASS 1>/dev/null