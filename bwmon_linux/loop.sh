#!/bin/sh
# start in a 'screen' session

cd /home/tero/bin/bwmon

while [ true ]
do
 ./sendupdate.sh
 sleep 1
done
