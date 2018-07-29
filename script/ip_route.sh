#!/bin/bash
# WLSDEV=`ip link|grep -i wlp| awk -F: '{print $2}'`

#sudo route add default gw 192.168.0.1 dev $WLSDEV metric 50
#sudo route del default metric 600 $WLSDEV

sudo route del default enp0s31f6
