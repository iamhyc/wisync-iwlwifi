#!/bin/bash
sudo ./iwlnl_cmd --aifs 2 --cw_min 3 --cw_max 7 -i 0
sudo ./iwlnl_cmd --aifs 2 --cw_min 7 --cw_max 15 -i 1
sudo ./iwlnl_cmd --aifs 3 --cw_min 15 --cw_max 1023 -i 2
sudo ./iwlnl_cmd --aifs 7 --cw_min 15 --cw_max 1023 -i 3
echo "Reset done."