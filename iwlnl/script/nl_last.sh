#!/bin/bash
./iwlnl_cmd --aifs 255 --cw_min 2047 --cw_max 8191 -i 0
./iwlnl_cmd --aifs 255 --cw_min 2047 --cw_max 8191 -i 1
./iwlnl_cmd --aifs 255 --cw_min 2047 --cw_max 8191 -i 2
./iwlnl_cmd --aifs 255 --cw_min 2047 --cw_max 8191 -i 3
echo "Slowest."
