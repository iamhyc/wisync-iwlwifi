#!/bin/bash
sudo ./iwlnl_cmd --aifs 0 --cw_min 1 --cw_max 1 -i 0
sudo ./iwlnl_cmd --aifs 0 --cw_min 1 --cw_max 1 -i 1
sudo ./iwlnl_cmd --aifs 0 --cw_min 1 --cw_max 1 -i 2
sudo ./iwlnl_cmd --aifs 0 --cw_min 1 --cw_max 1 -i 3
echo "Priorized."