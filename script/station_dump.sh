#!/bin/bash

while [ 1 ]
do
clear && sudo iw dev $1 station dump
sleep 0.1
done
