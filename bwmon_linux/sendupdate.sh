#!/bin/sh

outbound=`cat bwbar/outbound.txt |cut -c30-37|awk '{print int($1+0.5)}'`
inbound=`cat bwbar/inbound.txt |cut -c30-37|awk '{print int($1+0.5)}'` 

#outbound=10.5
#inbound=120.5

if [ -z "$outbound" ] || [ -z "$inbound" ]; then
 echo "No valid data found, exiting..."
 exit 1;
fi

echo "Outbound:  $outbound - Inbound: $inbound"

outbound_prc=`echo "($outbound/1123)*100"|bc -l|awk '{print int($1+0.5)}'`
inbound_prc=`echo "($inbound/1123)*100"|bc -l|awk '{print int($1+0.5)}'`

echo "Outbound percent:  $outbound - Inbound percent: $inbound"

url="http://192.168.100.177/?up=$outbound_prc&dn=$inbound_prc"
echo "Getting url $url";
wget -O resp.txt $url
cat resp.txt
