#!/bin/sh

cd /home/tero/bin/bwmon
killall bwbar

bwbar -k -t 1 -d bwbar/ -f inbound.txt -p inbound.png --output eth0 1000 &
bwbar -k -t 1 -d bwbar/ -f outbound.txt -p outbound.png --output eth0 1000 &

