#!/bin/bash
sudo ./iwlnl_cmd --aifs 255 --cw_min 2047 --cw_max 8191 -i 0
sudo ./iwlnl_cmd --aifs 255 --cw_min 2047 --cw_max 8191 -i 1
sudo ./iwlnl_cmd --aifs 255 --cw_min 2047 --cw_max 8191 -i 2
sudo ./iwlnl_cmd --aifs 255 --cw_min 2047 --cw_max 8191 -i 3
echo "Slowest."
