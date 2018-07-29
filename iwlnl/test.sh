#!/bin/bash
echo "==============================="

sudo make reset                  # 00s - 10s
sleep 10

sudo make last && echo "last"    # 10s - 20s
sleep 10

sudo make prior && echo "prior"  # 20s - 30s
sleep 10

sudo make reset && echo "reset"  # 30s - 40s
sleep 10

sudo make last && echo "last"    # 40s - 50s
sleep 10

sudo make reset && echo "reset"  # 50s - 60s
sleep 10

echo "==============================="
