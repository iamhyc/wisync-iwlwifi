#!/bin/bash
./iwlnl_cmd --aifs 15 --cw_min 1023 --cw_max 2047 -i 0
./iwlnl_cmd --aifs 15 --cw_min 1023 --cw_max 2047 -i 1
./iwlnl_cmd --aifs 15 --cw_min 1023 --cw_max 2047 -i 2
./iwlnl_cmd --aifs 15 --cw_min 1023 --cw_max 2047 -i 3
echo "Slowest."